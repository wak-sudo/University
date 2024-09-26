// Wojciech Kieloch 339952 2024 SK

#include "Client.h"

#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <cassert>
#include <iostream>

#include "panic.h"
#include "Tools.h"
#include "Constants.h"

Client::Client(unsigned ip, unsigned short port)
{
    socketFD = Tools::getSocket();
    // bindSocket(Constants::RECIEVING_PORT);

    myPoll = pollfdCons(socketFD);

    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    recipient.sin_port = htons(port);
    recipient.sin_addr.s_addr = htonl(ip);

    buffer = nullptr;
}

Client::~Client()
{
    delete buffer;
    close(socketFD);
}

void Client::getFile(std::string fileName, unsigned fileSizeArg, bool showProgress)
{
    unsigned fileDesc = Tools::getFileDesc(fileName);

    if (buffer == nullptr)
        buffer = new BufferHandler(fileSizeArg, fileDesc);
    else
        buffer->reinit(fileSizeArg, fileDesc);

    unsigned numberOfTurns = 0;

    double prevProgres = 0;
    const double numberOfBlocks = buffer->getNumberOfBlocks();

    while (!buffer->allBlocksRecived())
    {
        askForUnrecivedBlocks();
        listen(Constants::TURN_TIME);
        
        double curProgress = (double)buffer->getNumberOfWrittenBlocks() / numberOfBlocks;
        if (showProgress && curProgress != prevProgres && curProgress > 0)
        {
            prevProgres = curProgress;
            std::cout << Tools::toPercent(curProgress) << std::endl;
        }

        numberOfTurns++;

        Tools::log("Turn end");
    }

    Tools::log("Finished in " + std::to_string(numberOfTurns) + " turns.");

    close(fileDesc);
}

ssize_t Client::getPacket(sockaddr_in &sender, char *pacBuff, unsigned pacLen)
{
    socklen_t sender_len = sizeof(sockaddr_in);
    ssize_t packet_len = recvfrom(
        socketFD,
        pacBuff,
        pacLen,
        0,
        (struct sockaddr *)&sender,
        &sender_len);
    if (packet_len == -1)
        panic("Client::getPacket");
    return packet_len;
}

void Client::sendPacket(char *pacBuff, ssize_t pacLen)
{
    ssize_t bytes_sent = sendto(
        socketFD,
        pacBuff,
        pacLen,
        0,
        (struct sockaddr *)&recipient,
        sizeof(recipient));
    if (bytes_sent != pacLen)
        panic("Client::sendPacket -> bytes_sent : " + std::to_string(bytes_sent));
}

void Client::sendDataRequest(unsigned id, unsigned len)
{
    size_t requestLen = 0;
    char *request = consDataRequest(id, len, requestLen);
    sendPacket(request, requestLen);
    Tools::log("Message sent: " + std::to_string(id) + "/" + std::to_string(len));
    delete[] request;
}

char *Client::consDataRequest(unsigned id, unsigned len, size_t &resSize)
{
    const std::string idStr = std::to_string(id);
    const std::string lenStr = std::to_string(len);
    const std::string request = "GET " + idStr + ' ' + lenStr + '\n';
    resSize = request.size();
    char *bytes = new char[resSize];
    std::memcpy(bytes, request.data(), resSize);
    return bytes;
}

ssize_t Client::waitForPacket(sockaddr_in &sender, int deltaMS, char *packetBuff)
{
    const int timeToWait = deltaMS;
    int ready = poll(&myPoll, 1, timeToWait);
    if (!pollGood(ready))
        return -1;
    ssize_t packet_len = getPacket(sender, packetBuff);
    return packet_len;
}

pollfd Client::pollfdCons(int sockfd)
{
    pollfd ps;
    ps.fd = sockfd;
    ps.events = POLLIN;
    ps.revents = 0;
    return ps; // this works in cpp even if the structure is locally alocated.
}

bool Client::pollGood(int res)
{
    if (myPoll.revents != POLLIN && myPoll.revents != 0)
        panic("Client::pollGood: " + std::to_string(myPoll.revents));
    if (res == -1)
        panic("Client::pollGood");
    if (res == 0) // time elapsed.
        return false;
    // reset revents
    myPoll.revents = 0;
    return true;
}

void Client::listen(unsigned listenForMS)
{
    assert(buffer != nullptr);

    char singlePacketBuff[IP_MAXPACKET];

    sockaddr_in sender;
    myClock::time_point listStart;
    myClock::time_point listEnd;
    int timeToWaitMS = listenForMS;
    while (timeToWaitMS > 0) // this isn't active waiting, look at waitForPacket implementation.
    {
        listStart = myClock::now();
        ssize_t recPacketLen = waitForPacket(sender, timeToWaitMS, singlePacketBuff);
        listEnd = myClock::now();
        if (recPacketLen != -1) // message recieved.
        {
            if (sender.sin_addr.s_addr == recipient.sin_addr.s_addr)
            {
                unsigned fragStart = 0;
                unsigned len = 0;
                char *data = getInfoAboutRecivedPacket(singlePacketBuff, recPacketLen, fragStart, len);
                Tools::log("Recived: " + std::to_string(fragStart) + " Size: " + std::to_string(len));
                buffer->recieve(fragStart, data, len);
            }
        }
        timeToWaitMS -= std::chrono::duration_cast<std::chrono::milliseconds>(listEnd - listStart).count();
    }

#ifdef DEBUG
    buffer->printNotYetRecived();
#endif
}

char *Client::getInfoAboutRecivedPacket(char *packet, unsigned packetLen, unsigned &retStart, unsigned &retLen)
{
    const unsigned minimalPacketSize = 4;
    assert(packetLen >= minimalPacketSize);

    std::string magic = std::string() + packet[0] + packet[1] + packet[2] + packet[3];
    assert(magic == "DATA");

    const unsigned idStartIdx = 5;
    unsigned i = idStartIdx;
    while (packet[i] != ' ')
        i++;
    std::string idStr = Tools::charArrayToString(packet, idStartIdx, i);
    retStart = std::stoul(idStr);

    const unsigned lenStartIdx = i + 1;
    unsigned j = lenStartIdx;
    while (packet[j] != '\n')
        j++;
    std::string lenStr = Tools::charArrayToString(packet, lenStartIdx, j);
    retLen = std::stoul(lenStr);

    char *dataStart = packet + j + 1;
    return dataStart;
}

void Client::askForUnrecivedBlocks()
{
    assert(buffer != nullptr);
    for (auto it = buffer->begin(); it != buffer->end(); it++)
    {
        const unsigned offset = (*it) * buffer->getMaxBlockSize();
        sendDataRequest(offset, buffer->getBlockSize(it));
    }
}