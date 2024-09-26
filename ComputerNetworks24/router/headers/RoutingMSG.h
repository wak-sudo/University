// Wojciech Kieloch 339952 2024 SK

#pragma once

#include <string>

struct RoutingMSG
{
    unsigned ip;
    unsigned distance;
    unsigned char prefix;
    RoutingMSG() : ip(0), distance(0), prefix(0) {}
    RoutingMSG(unsigned ipArg, unsigned char prefixArg, unsigned distArg) : ip(ipArg), distance(distArg), prefix(prefixArg) {}
    static void MSGentryToBuf(RoutingMSG entry, char *resBuf);
    static RoutingMSG bufToMSGentry(char *bytesForm);
    std::string toString();
};