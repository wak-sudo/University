// Wojciech Kieloch 339952 2024 SK

#pragma once

#include "RoutingMSG.h"

#include <map>
#include <string>

#include "constants.h"

struct RoutingAddr
{
    unsigned ip;
    unsigned char prefix;
    RoutingAddr() : ip(0), prefix(0) {}
    RoutingAddr(unsigned ipArg, unsigned char prefixArg) : ip(ipArg), prefix(prefixArg) {}
    RoutingAddr(std::string cidrAddr);
    RoutingAddr(RoutingMSG msg) : ip(msg.ip), prefix(msg.prefix) {}
};

struct RoutingInfo
{
    unsigned distance;
    unsigned via;
    unsigned lastRecived;
    RoutingInfo() : distance(0), via(0), lastRecived(0) {}
    RoutingInfo(unsigned dist, unsigned viaArg) : distance(dist), via(viaArg), lastRecived(0) {}
};

struct PrefixAndDistance
{
    unsigned distance;
    unsigned char prefix;
    PrefixAndDistance(unsigned distArg, unsigned char prefixArg) : distance(distArg), prefix(prefixArg) {}
    PrefixAndDistance() : distance(0), prefix(0) {}
};

struct CounterAndVia
{
    unsigned timesSpread;
    unsigned via;
    CounterAndVia() : timesSpread(0), via(0) {}
    CounterAndVia(unsigned timesSpreadArg, unsigned viaArg) : timesSpread(timesSpreadArg), via(viaArg) {}
};

class RoutingTable
{
    typedef std::map<RoutingAddr, RoutingInfo>::iterator reachIter;
    typedef std::map<RoutingAddr, CounterAndVia>::iterator unrIter;
    typedef std::map<unsigned, PrefixAndDistance>::iterator interIter;

    std::map<RoutingAddr, RoutingInfo> reachable;
    std::map<RoutingAddr, CounterAndVia> unreachable;
    std::map<unsigned, PrefixAndDistance> interfaces;

    bool isDistReachable(unsigned distance);
    unrIter rmUnreachable(unrIter it);
    reachIter rmReachable(RoutingAddr addr);
    reachIter rmReachable(reachIter it);
    void tryAddUnreachable(RoutingAddr addr, unsigned via);
    void updateReachable(RoutingMSG msg, unsigned via, unsigned newDistance);
    void updateTimeInReachable();
    unsigned calcDist(RoutingMSG msg, unsigned via);
    void tryRmNetwork(RoutingAddr network, unsigned via);
    void updateTimeInUnreachable();
    interIter findBestFittingInter(unsigned ip);
    bool interfaceIsReachable(interIter it);

    size_t printReachable();
    size_t printUnreachable();
    void printVia(unsigned via);

public:
    typedef std::map<RoutingAddr, RoutingInfo>::const_iterator cReachIter;
    typedef std::map<RoutingAddr, CounterAndVia>::const_iterator cUnrIter;
    typedef std::map<unsigned, PrefixAndDistance>::const_iterator cInterIter;

    RoutingTable() {}

    void addInterface(RoutingAddr interface, unsigned distance); // also adds info to the reachable map
    void addInterface(std::string ipAndPrefix, unsigned distance);
    bool isInterface(unsigned ip);

    void processInfo(RoutingMSG msg, unsigned via); // other than interfaces.

    void turnEnd();

    cReachIter reachBegin();
    cReachIter reachEnd();
    size_t reachSize();

    cUnrIter unrBegin();
    cUnrIter unrEnd();
    size_t unreachSize();

    cInterIter interBegin();
    cInterIter interEnd();
    size_t interSize();

    void print();
    RoutingMSG entryToMSG(cReachIter iter);
    RoutingMSG entryToMSG(cUnrIter iter);
};