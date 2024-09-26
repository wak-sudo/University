// Wojciech Kieloch 339952 2024 SK

#include "RoutingTable.h"

#include <iostream>
#include <arpa/inet.h>
#include <cassert>

#include "panic.h"
#include "NetTools.h"

extern bool glob_debug_active;

void RoutingTable::print()
{
    if (glob_debug_active)
        std::cout << std::endl; // additional new line for the debug mode.

    unsigned counter = 0;

    counter += printReachable();

    counter += printUnreachable();

    if (counter == 0)
        std::cout << "Empty" << std::endl;

    std::cout << std::endl;
}

RoutingAddr::RoutingAddr(std::string cidrAddr)
{
    size_t slashIdx = cidrAddr.find('/');
    if (slashIdx == std::string::npos)
        panic("RoutingAddr::RoutingAddr");
    std::string ipStr = cidrAddr.substr(0, slashIdx);
    std::string prefixStr = cidrAddr.substr(slashIdx + 1);
    unsigned ipInt = NetTools::strToIp(ipStr.c_str());
    unsigned prefixInt = stoul(prefixStr);
    assert(prefixInt <= 32);

    this->ip = ipInt;
    this->prefix = prefixInt;
}

bool operator<(const RoutingAddr &x, const RoutingAddr &y)
{
    return std::tie(x.ip, x.prefix) < std::tie(y.ip, y.prefix);
}

RoutingTable::cReachIter RoutingTable::reachBegin() { return reachable.begin(); }

RoutingTable::cReachIter RoutingTable::reachEnd() { return reachable.end(); }

RoutingTable::cUnrIter RoutingTable::unrBegin() { return unreachable.begin(); }

RoutingTable::cUnrIter RoutingTable::unrEnd() { return unreachable.end(); }

RoutingTable::cInterIter RoutingTable::interBegin() { return interfaces.begin(); }

RoutingTable::cInterIter RoutingTable::interEnd() { return interfaces.end(); }

size_t RoutingTable::reachSize() { return reachable.size(); }

size_t RoutingTable::unreachSize() { return unreachable.size(); }

size_t RoutingTable::interSize() { return interfaces.size(); }

RoutingMSG RoutingTable::entryToMSG(cReachIter iter)
{
    if (iter == this->reachEnd())
        return RoutingMSG(0, 0, 0);
    const unsigned ip = iter->first.ip;
    const unsigned prefix = iter->first.prefix;
    const unsigned distance = iter->second.distance;
    return RoutingMSG(ip, prefix, distance);
}

RoutingMSG RoutingTable::entryToMSG(cUnrIter iter)
{
    if (iter == this->unrEnd())
        return RoutingMSG(0, 0, 0);
    const unsigned ip = iter->first.ip;
    const unsigned prefix = iter->first.prefix;
    const unsigned distance = Constants::UNREACHABLE_DIST;
    return RoutingMSG(ip, prefix, distance);
}

void RoutingTable::addInterface(RoutingAddr interface, unsigned distance)
{
    const unsigned ip = interface.ip;
    const unsigned char prefix = interface.prefix;
    PrefixAndDistance info(distance, prefix);

    NetTools::log("Interface added: Ip: " + NetTools::ipToStr(ip) + "/" + std::to_string(prefix) + " D: " + std::to_string(distance));

    interfaces[ip] = info;
}

RoutingTable::unrIter RoutingTable::rmUnreachable(unrIter it)
{
    if (it != unreachable.end())
        return unreachable.erase(it);
    return it;
}

void RoutingTable::processInfo(RoutingMSG msg, unsigned via)
{
    unrIter iter = unreachable.find(msg);
    bool isInUnreachable = (iter != unreachable.end());
    unsigned newDist = calcDist(msg, via);
    if (isDistReachable(newDist))
    {
        if (isInUnreachable)
            rmUnreachable(iter);
        updateReachable(msg, via, newDist);
    }
    else
        tryRmNetwork(msg, via); // is not reachable
}

void RoutingTable::updateReachable(RoutingMSG msg, unsigned via, unsigned newDistance)
{
    auto it = reachable.find(msg);
    RoutingInfo newInfo;
    newInfo.distance = newDistance;
    newInfo.via = via;

    if (NetTools::isInNetwork(via, msg.ip, msg.prefix)) // checks whether network is adjacent.
        newInfo.via = Constants::CONNECTED_DIRECTLY;

    if (it != reachable.end()) // entry found
    {
        unsigned oldDist = it->second.distance;
        if (newDistance < oldDist)
        {
            NetTools::log(msg.toString() + " updated with distance: " + std::to_string(newDistance));
            reachable[msg] = newInfo;
        }
    }
    else // not found
    {
        reachable[msg] = newInfo;
        NetTools::log(msg.toString() + " added with distance: " + std::to_string(newDistance));
    }
}

bool RoutingTable::isDistReachable(unsigned distance)
{
    if (distance >= Constants::UNREACHABLE_DIST)
        return false;
    return true;
}

void RoutingTable::tryAddUnreachable(RoutingAddr addr, unsigned via)
{
    auto itUn = unreachable.find(addr);
    if (itUn == unreachable.end())
    {
        if (NetTools::isInNetwork(via, addr.ip, addr.prefix))
            unreachable[addr] = CounterAndVia(0, Constants::CONNECTED_DIRECTLY);
        else
            unreachable[addr] = CounterAndVia(0, via);
    }
}

RoutingTable::reachIter RoutingTable::rmReachable(RoutingAddr addr)
{
    auto it = reachable.find(addr);
    if (it != reachable.end())
        return reachable.erase(it);
    return it;
}

unsigned RoutingTable::calcDist(RoutingMSG msg, unsigned via)
{
    if (!isDistReachable(msg.distance))
        return Constants::UNREACHABLE_DIST;

    auto it = findBestFittingInter(via);
    NetTools::log("Looking for: " + NetTools::ipToStr(via));
    if (it != interfaces.end()) // found
    {
        if (NetTools::isInNetwork(via, msg.ip, msg.prefix)) // if it is the adjacent network.
            return msg.distance;
        else
            return it->second.distance + msg.distance;
    }
    else
    {
        NetTools::log("Not found");
        return Constants::UNREACHABLE_DIST;
    }
}

RoutingTable::interIter RoutingTable::findBestFittingInter(unsigned ip)
{
    interIter bestMatch = interfaces.end();
    unsigned bestDistance = Constants::UNREACHABLE_DIST;
    for (interIter it = interfaces.begin(); it != interfaces.end(); it++)
    {
        unsigned prefix = it->second.prefix;
        unsigned distance = it->second.distance;
        unsigned networkIp = NetTools::getNetworkAddr(it->first, prefix);
        if (NetTools::isInNetwork(ip, networkIp, prefix))
        {
            if (distance < bestDistance)
            {
                distance = bestDistance;
                bestMatch = it;
            }
        }
    }
    return bestMatch;
}

bool RoutingTable::interfaceIsReachable(interIter it)
{
    RoutingAddr addr(NetTools::getNetworkAddr(it->first, it->second.prefix), it->second.prefix);
    auto reachIt = reachable.find(addr);
    if (reachIt == reachable.end())
        return false;
    return true;
}

void RoutingTable::updateTimeInUnreachable()
{
    auto it = unreachable.begin();
    while (it != unreachable.end())
    {
        it->second.timesSpread++;
        unsigned counter = it->second.timesSpread;
        if (counter >= Constants::SPREAD_UNR_FOR)
            it->second.timesSpread = Constants::SPREAD_UNR_FOR;

        it++;
    }
}

void RoutingTable::turnEnd()
{
    print();
    updateTimeInUnreachable();
    updateTimeInReachable();
}

void RoutingTable::addInterface(std::string ipAndPrefix, unsigned distance)
{
    RoutingAddr addr(ipAndPrefix);
    addInterface(addr, distance);
}

// this function removes the network if it is accessed through via.
void RoutingTable::tryRmNetwork(RoutingAddr network, unsigned via)
{
    auto it = reachable.find(network);
    if (it != reachable.end() && it->second.via == via)
    {
        NetTools::log("Removing network: " + NetTools::ipToStr(network.ip));

        rmReachable(network);

        tryAddUnreachable(network, via);
    }
}

RoutingTable::reachIter RoutingTable::rmReachable(reachIter it)
{
    if (it != reachable.end())
        return reachable.erase(it);
    return it;
}

size_t RoutingTable::printReachable()
{
    for (const auto &iter : reachable)
    {
        std::string ipAddrStr = NetTools::ipToStr(iter.first.ip);
        const unsigned char prefix = iter.first.prefix;
        const unsigned distance = iter.second.distance;
        const unsigned via = iter.second.via;

        assert(distance < Constants::UNREACHABLE_DIST);

        std::cout << ipAddrStr << "/" << (int)prefix << " distance " << distance;

        printVia(via);
    }
    return reachable.size();
}

size_t RoutingTable::printUnreachable()
{
    unsigned counter = 0;
    for (const auto &iter : unreachable)
    {
        if (iter.second.timesSpread < Constants::SPREAD_UNR_FOR)
        {
            counter++;

            std::string ipAddrStr = NetTools::ipToStr(iter.first.ip);
            const unsigned char prefix = iter.first.prefix;

            std::cout << ipAddrStr << "/" << (int)prefix << " unreachable";

            printVia(iter.second.via);
        }
    }
    return counter;
}

bool RoutingTable::isInterface(unsigned ip)
{
    auto it = interfaces.find(ip);
    if (it == interfaces.end())
        return false;
    return true;
}

void RoutingTable::updateTimeInReachable()
{
    auto it = reachable.begin();
    while (it != reachable.end())
    {
        it->second.lastRecived++;
        if (it->second.lastRecived >= Constants::TIME_LIMIT_FOR_REACH)
        {
            NetTools::log("Network out of time: " + NetTools::ipToStr(it->first.ip));
            tryAddUnreachable(it->first, it->second.via);
            it = rmReachable(it);
        }
        else
            it++;
    }
}

void RoutingTable::printVia(unsigned via)
{
    if (via == Constants::CONNECTED_DIRECTLY)
        std::cout << " connected directly" << std::endl;
    else
    {
        std::string viaAddrStr = NetTools::ipToStr(via);
        std::cout << " via " << viaAddrStr << std::endl;
    }
}