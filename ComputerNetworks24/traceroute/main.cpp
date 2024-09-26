// Wojciech Kieloch 339952 2024

#include <iostream>
#include <chrono>
#include <cmath>
#include <set>

#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/time.h>

#include "MyUtil.h"
#include "IcmpUtil.h"

#define NO_OF_PACKETS 3

typedef std::chrono::high_resolution_clock myClock;

using namespace std;

int main(int argc, char *argv[])
{
    const char *invArgs = "Invalid arguments.";
    if (argc != 2)
    {
        cout << invArgs << endl;
        return 0;
    }

    sockaddr_in recipient = IcmpUtil::consRecipient();
    if (inet_pton(AF_INET, argv[1], &recipient.sin_addr) <= 0)
    {
        cout << invArgs << endl;
        return 0;
    }

    myClock::time_point clockStart;
    myClock::time_point clockEnd;
    myClock::time_point packetsSent;
    double respondTime[NO_OF_PACKETS];

    sockaddr_in sender;
    char senderIpBuf[INET_ADDRSTRLEN];
    set<string> sendersNames;
    char packetBuffer[IP_MAXPACKET];
    bool destReached = false;

    int sockfd = IcmpUtil::createSocketForICMP();
    pollfd pollBuf = MyUtil::pollfdCons(sockfd);
    for (unsigned curTTL = 1; curTTL <= 30 && !destReached; curTTL++)
    {
        cout << to_string(curTTL) << ". ";

        icmp myHeader = IcmpUtil::createICMPechoHeader(curTTL);

        IcmpUtil::changeTTL(curTTL, sockfd);
        for (int i = 0; i < NO_OF_PACKETS; i++) // sending it three times
            IcmpUtil::sendICMPecho(sockfd, myHeader, recipient);
        packetsSent = myClock::now();

        int timeToWait = 1000; // ms
        int packetReci = 0;
        while (timeToWait > 0 && packetReci < NO_OF_PACKETS)
        {
            clockStart = myClock::now();
            int ready = poll(&pollBuf, 1, timeToWait);
            clockEnd = myClock::now();

            if (!MyUtil::pollGood(pollBuf, ready))
                break; // time elapsed.

            int64_t msElapsed = chrono::duration_cast<chrono::milliseconds>(clockEnd - clockStart).count();
            timeToWait -= msElapsed;

            ssize_t packet_len = IcmpUtil::recieveIPpacket(sockfd, sender, packetBuffer);
            if (IcmpUtil::icmpPacketMatchSeq(IcmpUtil::unpackIp(packetBuffer), packet_len, curTTL))
            {
                if (sender.sin_addr.s_addr == recipient.sin_addr.s_addr)
                    destReached = true;
                respondTime[packetReci] = (double)chrono::duration_cast<chrono::microseconds>(clockEnd - packetsSent).count() / 1000;

                MyUtil::translateIpToString(sender.sin_addr, senderIpBuf, sizeof(senderIpBuf));
                sendersNames.insert(senderIpBuf);
                packetReci++;
            }
        }

        for (const string &adr : sendersNames)
            cout << adr << " ";
        sendersNames.clear();

        cout << MyUtil::calcAvgTime(respondTime, packetReci) << endl;
    }
    close(sockfd);

    return 0;
}