// Wojciech Kieloch 339952 2024 SK

#pragma once

#include <netinet/ip.h>
#include <poll.h>
#include <chrono>
#include <string>

#include "RoutingMSG.h"
#include "RoutingTable.h"

namespace NetTools
{
    typedef std::chrono::high_resolution_clock myClock;

    int getSocket();
    void bindServer(int socketFD, unsigned short port);
    ssize_t getPacket(int sockFD, sockaddr_in &sender, char *pacBuff, unsigned pacLen = IP_MAXPACKET);
    ssize_t sendPacket(int sockFD, sockaddr_in &recipient, char *pacBuff, unsigned bufLen);
    ssize_t sendRoutingMSG(int sockFD, sockaddr_in &recipient, RoutingMSG msg);
    ssize_t sendAndProcess(int socket, sockaddr_in &recipient, RoutingMSG msg, RoutingAddr networkAddr, RoutingTable &table);
    ssize_t listenRoutingMSG(int sockFD, sockaddr_in &sender, RoutingMSG &msg, pollfd &pfd, int deltaMS);
    void setBroadcastPermission(int socket);

    void spread(int socket, RoutingTable &table);
    void listen(int socket, RoutingTable &table);

    unsigned getNetworkAddr(unsigned ipAddr, unsigned char prefix);
    unsigned getBroadcastAddr(unsigned ipAddr, unsigned char prefix);
    bool isInNetwork(unsigned addr, unsigned network, unsigned char networkPrefixLen);
    unsigned getMask(unsigned char prefixLen);

    int createServer();

    pollfd pollfdCons(int sockfd);
    bool pollGood(pollfd &pollStruct, int res);
    std::string ipToStr(unsigned ip);
    unsigned strToIp(const char *str);

    // Debug:
    void log(std::string msg);
}