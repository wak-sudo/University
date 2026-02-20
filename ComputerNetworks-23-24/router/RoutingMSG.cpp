// Wojciech Kieloch 339952 2024 SK

#include "RoutingMSG.h"

#include <cstring>
#include <arpa/inet.h>
#include <cassert>

#include "NetTools.h"

void RoutingMSG::MSGentryToBuf(RoutingMSG entry, char *resBuf)
{
    const unsigned ip_net = htonl(entry.ip);
    const unsigned prefix_net = entry.prefix;
    const unsigned distance_net = htonl(entry.distance);
    std::memcpy(resBuf, &ip_net, sizeof(ip_net));
    std::memcpy(resBuf + 4, &prefix_net, sizeof(prefix_net));
    std::memcpy(resBuf + 5, &distance_net, sizeof(distance_net));
}

RoutingMSG RoutingMSG::bufToMSGentry(char *bytesForm)
{
    const unsigned ip_host = ntohl(((unsigned *)bytesForm)[0]);
    const unsigned char prefix_host = bytesForm[4];
    assert(prefix_host <= 32);
    const unsigned distance_host = ntohl(((unsigned *)(bytesForm + 5))[0]);

    RoutingMSG entry(ip_host, prefix_host, distance_host);

    return entry;
}

std::string RoutingMSG::toString()
{
    return "IP: " + NetTools::ipToStr(this->ip) + "/" + std::to_string(unsigned(this->prefix)) + " D: " + std::to_string(this->distance);
}