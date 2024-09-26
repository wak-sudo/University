// Wojciech Kieloch 339952 2024

#include "MyUtil.h"

#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#include "panic.h"

uint16_t MyUtil::lowerPIDvalue()
{
    return getpid() & 0xFFFF;
}

void MyUtil::translateIpToString(const in_addr &sin_addr, char *resBuf, unsigned resLen)
{
    if (resLen < INET_ADDRSTRLEN)
        panic("translateIpToString: res buffer is too small.");
    if (inet_ntop(AF_INET, &sin_addr, resBuf, resLen) == NULL)
        panic("inet_ntop failed.");
}

std::string MyUtil::calcAvgTime(double *respondTime, unsigned packetsReci)
{
    if (packetsReci == 0)
        return "*";
    else if (packetsReci != 3)
        return "???";

    double averageTime = 0;
    for (unsigned i = 0; i < packetsReci; i++)
        averageTime += respondTime[i];
    averageTime /= packetsReci;

    return customFormatMS(averageTime);
}

std::string MyUtil::customFormatMS(double val)
{
    std::ostringstream oss;
    oss << std::setprecision(3) << std::noshowpoint << val;
    return oss.str() + "ms";
}

pollfd MyUtil::pollfdCons(int sockfd)
{
    pollfd ps;
    ps.fd = sockfd;
    ps.events = POLLIN;
    ps.revents = 0;
    return ps; // this works in cpp even if the structure is locally alocated.
}

bool MyUtil::pollGood(pollfd &pollStruct, int res)
{
    if (pollStruct.revents != POLLIN && pollStruct.revents != 0)
        panic("Wrong event at pollfd: " + std::to_string(pollStruct.revents));
    if (res == -1)
        panic("poll returned an error.");
    if (res == 0) // time elapsed.
        return false;
    // reset revents
    pollStruct.revents = 0;
    return true;
}