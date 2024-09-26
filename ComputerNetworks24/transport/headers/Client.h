// Wojciech Kieloch 339952 2024 SK

#pragma once

#include <netinet/ip.h>
#include <poll.h>
#include <chrono>
#include <string>

#include "BufferHandler.h"

class Client
{
    typedef std::chrono::high_resolution_clock myClock;

    BufferHandler *buffer;

    // Network related fields:
    int socketFD;
    sockaddr_in recipient;
    pollfd myPoll;

    // Constructor related:
    pollfd pollfdCons(int sockfd);

    // General network jobs:
    ssize_t getPacket(sockaddr_in &sender, char *pacBuff, unsigned pacLen = IP_MAXPACKET);
    void sendPacket(char *pacBuff, ssize_t pacLen);

    // Specific network jobs:
    void sendDataRequest(unsigned id, unsigned len);
    static char *consDataRequest(unsigned id, unsigned len, size_t &resSize);
    static char *getInfoAboutRecivedPacket(char *packet, unsigned packetLen, unsigned &retId, unsigned &retLen);
    ssize_t waitForPacket(sockaddr_in &sender, int deltaMS, char *packetBuff);

    // Rest:
    bool pollGood(int res);

    // Main logic:
    void listen(unsigned listenForMS);
    void askForUnrecivedBlocks();

public:
    Client(unsigned ip, unsigned short port);
    ~Client();

    void getFile(std::string fileName, unsigned fileSizeArg, bool showProgress = true);
};