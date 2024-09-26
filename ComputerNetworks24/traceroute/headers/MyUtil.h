// Wojciech Kieloch 339952 2024

#pragma once

#include <string>
#include <poll.h>
#include <netinet/ip.h>

namespace MyUtil
{
    uint16_t lowerPIDvalue();
    void translateIpToString(const in_addr &sin_addr, char *resBuf, unsigned resLen);
    std::string calcAvgTime(double *respondTime, unsigned packetsReci);
    pollfd pollfdCons(int sockfd);
    bool pollGood(pollfd &pollStruct, int res);
    std::string customFormatMS(double val);
}