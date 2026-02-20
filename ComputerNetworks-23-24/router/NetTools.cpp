// Wojciech Kieloch 339952 2024 SK

#include "NetTools.h"

#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include <iostream>

#include "panic.h"
#include "constants.h"

extern bool glob_debug_active;

int NetTools::getSocket()
{
    int mySocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mySocket == -1)
        panic("UDPtools::getSocket");
    return mySocket;
}

int NetTools::createServer()
{
    int socket = getSocket();
    bindServer(socket, Constants::RUNNING_PORT);
    return socket;
}

void NetTools::bindServer(int socketFD, unsigned short port)
{
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(socketFD, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret == -1)
        panic("UDPtools::bindServer");
}

ssize_t NetTools::getPacket(int sockFD, sockaddr_in &sender, char *pacBuff, unsigned pacLen)
{
    socklen_t sender_len = sizeof(sockaddr_in);
    ssize_t packet_len = recvfrom(
        sockFD,
        pacBuff,
        pacLen,
        0,
        (struct sockaddr *)&sender,
        &sender_len);
    if (packet_len == -1)
        panic("UDPtools::getPacket");
    return packet_len;
}

ssize_t NetTools::sendPacket(int sockFD, sockaddr_in &recipient, char *pacBuff, unsigned bufLen)
{
    ssize_t bytes_sent = sendto(
        sockFD,
        pacBuff,
        bufLen,
        0,
        (struct sockaddr *)&recipient,
        sizeof(recipient));
    return bytes_sent;
}

ssize_t NetTools::sendRoutingMSG(int sockFD, sockaddr_in &recipient, RoutingMSG msg)
{
    char *msgBuf = new char[Constants::MSG_SIZE];
    RoutingMSG::MSGentryToBuf(msg, msgBuf);
    ssize_t bytes_sent = sendPacket(sockFD, recipient, msgBuf, Constants::MSG_SIZE);
    delete[] msgBuf;
    return bytes_sent;
}

ssize_t NetTools::listenRoutingMSG(int sockFD, sockaddr_in &sender, RoutingMSG &msg, pollfd &pfd, int deltaMS)
{
    char *msgBuf = new char[Constants::MSG_SIZE];
    const int timeToWait = deltaMS;
    int ready = poll(&pfd, 1, timeToWait);
    if (!pollGood(pfd, ready))
        return -1;
    ssize_t packet_len = getPacket(sockFD, sender, msgBuf, Constants::MSG_SIZE);
    msg = RoutingMSG::bufToMSGentry(msgBuf);
    delete[] msgBuf;
    return packet_len;
}

pollfd NetTools::pollfdCons(int sockfd)
{
    pollfd ps;
    ps.fd = sockfd;
    ps.events = POLLIN;
    ps.revents = 0;
    return ps; // this works in cpp even if the structure is locally alocated.
}

bool NetTools::pollGood(pollfd &pollStruct, int res)
{
    if (pollStruct.revents != POLLIN && pollStruct.revents != 0)
        panic("MyUtil::pollGood: Wrong event at pollfd: " + std::to_string(pollStruct.revents));
    if (res == -1)
        panic("MyUtil::pollGood: poll returned an error.");
    if (res == 0) // time elapsed.
        return false;
    // reset revents
    pollStruct.revents = 0;
    return true;
}

std::string NetTools::ipToStr(unsigned ip)
{
    char strBuf[20];
    struct in_addr inAdd;
    inAdd.s_addr = htonl(ip);
    const char *ret = inet_ntop(AF_INET, &inAdd, strBuf, INET_ADDRSTRLEN);
    if (ret == NULL)
        panic("RoutingTable::ipToStr");
    return strBuf;
}

unsigned NetTools::strToIp(const char *str)
{
    struct in_addr inAdd;
    int ret = inet_pton(AF_INET, str, &inAdd);
    if (ret <= 0)
        panic("RoutingTable::strToIp");
    return ntohl(inAdd.s_addr);
}

void NetTools::spread(int socket, RoutingTable &table)
{
    sockaddr_in recipient;
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    recipient.sin_port = htons(Constants::RUNNING_PORT);

    log("Interfaces size: " + std::to_string(table.interSize()));

    for (auto itInter = table.interBegin(); itInter != table.interEnd(); itInter++)
    {
        const unsigned curInterIp = itInter->first;
        const unsigned char curInterPrefix = itInter->second.prefix;
        const unsigned curDistInter = itInter->second.distance;

        const unsigned networkBroadcastIp = getBroadcastAddr(curInterIp, curInterPrefix);
        const unsigned networkAddrIp = getNetworkAddr(curInterIp, curInterPrefix);

        RoutingAddr networkAddr(networkAddrIp, curInterPrefix);

        recipient.sin_addr.s_addr = htonl(networkBroadcastIp);

        log("Broadcast to: " + ipToStr(networkBroadcastIp));

        // spread interfaces:
        RoutingMSG msgInter(networkAddrIp, curInterPrefix, curDistInter);
        ssize_t bytesSent = sendAndProcess(socket, recipient, msgInter, networkAddr, table);
        log("Bytes sent from interface: " + std::to_string(bytesSent));

        // spread reachable
        for (auto itReach = table.reachBegin(); itReach != table.reachEnd(); itReach++)
        {
            RoutingMSG msg = table.entryToMSG(itReach);
            ssize_t bytesSent = sendAndProcess(socket, recipient, msg, networkAddr, table);
            log("Bytes sent: " + std::to_string(bytesSent));
            if (bytesSent <= 0)
                break;
        }

        // spread unreachable
        for (auto itUnr = table.unrEnd(); itUnr != table.unrEnd(); itUnr++)
        {
            if (itUnr->second.timesSpread < Constants::SPREAD_UNR_FOR)
            {
                RoutingMSG msg = table.entryToMSG(itUnr);
                ssize_t bytes_sent = sendAndProcess(socket, recipient, msg, networkAddr, table);
                if (bytes_sent <= 0)
                    break;
            }
        }
    }
}

ssize_t NetTools::sendAndProcess(int socket, sockaddr_in &recipient, RoutingMSG msg, RoutingAddr networkAddr, RoutingTable &table)
{
    ssize_t bytesSent = NetTools::sendRoutingMSG(socket, recipient, msg);
    if (bytesSent <= 0) // address unreachable
    {
        log("Network " + ipToStr(networkAddr.ip) + " unreachable.");
        RoutingMSG networkMSG(networkAddr.ip, networkAddr.prefix, Constants::UNREACHABLE_DIST);
        table.processInfo(networkMSG, Constants::CONNECTED_DIRECTLY);
    }
    return bytesSent;
}

unsigned NetTools::getNetworkAddr(unsigned ipAddr, unsigned char prefixLen)
{
    unsigned mask = getMask(prefixLen);
    unsigned res = ipAddr & mask;
    return res;
}

unsigned NetTools::getBroadcastAddr(unsigned ipAddr, unsigned char prefix)
{
    unsigned mask = (1 << (32 - prefix)) - 1;
    return getNetworkAddr(ipAddr, prefix) | mask;
}

void NetTools::setBroadcastPermission(int socket)
{
    int broadcastPermission = 1;
    int res = setsockopt(socket, SOL_SOCKET, SO_BROADCAST,
                         (void *)&broadcastPermission,
                         sizeof(broadcastPermission));
    if (res == -1)
        panic("NetTools::setBroadcastPermission");
}

void NetTools::listen(int socket, RoutingTable &table)
{
    pollfd pfd = NetTools::pollfdCons(socket);
    sockaddr_in sender;
    RoutingMSG curRecMsg;
    myClock::time_point listStart;
    myClock::time_point listEnd;
    int timeToWaitMS = Constants::TURN_TIME;
    ssize_t packet_len = 0;
    while (timeToWaitMS > 0) // this isn't active waiting, look at listenRoutingMSG implementation.
    {
        listStart = myClock::now();
        packet_len = NetTools::listenRoutingMSG(socket, sender, curRecMsg, pfd, timeToWaitMS);
        listEnd = myClock::now();
        if (packet_len != -1) // message recieved.
        {
            const unsigned senderIP = ntohl(sender.sin_addr.s_addr);
            if (!table.isInterface(senderIP))
            {
                log("Msg recived from: " + ipToStr(senderIP) + '\n' + curRecMsg.toString());
                table.processInfo(curRecMsg, senderIP);
            }
        }
        timeToWaitMS -= std::chrono::duration_cast<std::chrono::milliseconds>(listEnd - listStart).count();
    }
}

bool NetTools::isInNetwork(unsigned addr, unsigned network, unsigned char networkPrefixLen)
{
    unsigned mask = getMask(networkPrefixLen);
    return (addr & mask) == (network & mask);
}

unsigned NetTools::getMask(unsigned char prefixLen)
{
    if(prefixLen > 32)
    {
        log("Prefix too big: " + std::to_string(prefixLen));
        panic("NetTools::getMask");
    }
    if (prefixLen == 32)
        return 0xFFFFFFFF;
    unsigned binMask = ((1 << prefixLen) - 1) << (32 - prefixLen);
    return binMask;
}

void NetTools::log(std::string msg)
{
#ifdef DEBUG
    if (glob_debug_active)
        std::cout << msg << std::endl;
#endif
    (void)(msg); // to supress warnings.
}