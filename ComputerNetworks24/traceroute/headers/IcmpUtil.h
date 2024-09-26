// Wojciech Kieloch 339952 2024

#pragma once

#include <sys/socket.h>
#include <netinet/ip_icmp.h>

#define ICMP_HEADER_SIZE 8

namespace IcmpUtil
{
    struct IdICMPinfo;

    int createSocketForICMP();
    void sendICMPecho(int sockfd, const icmp &header, const sockaddr_in &recipient);
    icmp createICMPechoHeader(uint16_t seqNo);
    bool icmpPacketMatchSeq(char *packetBuf, unsigned bufLen, int seqNo);
    ssize_t recieveIPpacket(int sockfd, const sockaddr_in &sender, char *packetBuffer);
    sockaddr_in consRecipient();
    char *unpackIp(char *ipPacket);
    void changeTTL(int ttl, int sockfd);
}