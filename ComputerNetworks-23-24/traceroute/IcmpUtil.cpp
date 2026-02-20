// Wojciech Kieloch 339952 2024

#include "IcmpUtil.h"

#include <string>
#include <cassert>
#include <strings.h>
#include <iostream>

#include "panic.h"
#include "MyUtil.h"

struct IcmpUtil::IdICMPinfo
{
    int id;
    int seqNo;
    IdICMPinfo(int id, int seqNo)
    {
        this->id = id;
        this->seqNo = seqNo;
    }
};

// static functions the cpp way
namespace
{
    u_int16_t compute_icmp_checksum(const void *buff, int length)
    {
        const u_int16_t *ptr = (u_int16_t *)buff;
        u_int32_t sum = 0;
        assert(length % 2 == 0);
        for (; length > 0; length -= 2)
            sum += *ptr++;
        sum = (sum >> 16U) + (sum & 0xffffU);
        return (u_int16_t)(~(sum + (sum >> 16U)));
    }

    inline char *getOriginalDatagram(char *icmpPacket)
    {
        return icmpPacket + ICMP_HEADER_SIZE;
    }

    IcmpUtil::IdICMPinfo getICMPinfo(char *packetBuffer, unsigned bufferLen)
    {
        if (bufferLen < ICMP_HEADER_SIZE)
            panic("getICMPinfo recived an incomplete ICMP packet.");

        icmp *header = (icmp *)packetBuffer;
        int id = -1;
        int seqNo = -1;
        if (header->icmp_type == ICMP_ECHOREPLY)
        {
            id = header->icmp_hun.ih_idseq.icd_id;
            seqNo = header->icmp_hun.ih_idseq.icd_seq;
        }
        else if (header->icmp_type == ICMP_TIMXCEED)
        {
            icmp *orgICMP = (icmp *)IcmpUtil::unpackIp(getOriginalDatagram(packetBuffer));
            id = orgICMP->icmp_hun.ih_idseq.icd_id;
            seqNo = orgICMP->icmp_hun.ih_idseq.icd_seq;
        }
        return IcmpUtil::IdICMPinfo(id, seqNo);
    }
}
// end of static functions

int IcmpUtil::createSocketForICMP()
{
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd == -1)
        panic("Could not assign a socket fd (try run with privileges).");
    return sockfd;
}

void IcmpUtil::sendICMPecho(int sockfd, const icmp &header, const sockaddr_in &recipient)
{
    ssize_t bytes_sent = sendto(
        sockfd,
        &header,
        sizeof(header),
        0,
        (struct sockaddr *)&recipient,
        sizeof(recipient));

    if (bytes_sent < 0 || (long unsigned)bytes_sent < sizeof(header))
        panic("Could not send ICMP.");
}

icmp IcmpUtil::createICMPechoHeader(uint16_t seqNo)
{
    icmp header;
    header.icmp_type = ICMP_ECHO;
    header.icmp_code = 0;
    header.icmp_hun.ih_idseq.icd_id = MyUtil::lowerPIDvalue();
    header.icmp_hun.ih_idseq.icd_seq = seqNo;
    header.icmp_cksum = 0;
    header.icmp_cksum = compute_icmp_checksum((uint16_t *)&header, sizeof(header));
    return header;
}

bool IcmpUtil::icmpPacketMatchSeq(char *packetBuf, unsigned bufLen, int seqNo)
{
    IdICMPinfo packetInfo = getICMPinfo(packetBuf, bufLen);
    if (packetInfo.id == MyUtil::lowerPIDvalue() && packetInfo.seqNo == seqNo)
        return true;
    return false;
}

ssize_t IcmpUtil::recieveIPpacket(int sockfd, const sockaddr_in &sender, char *packetBuffer)
{
    socklen_t ptrLen = sizeof(sockaddr_in);
    ssize_t packet_len = recvfrom(sockfd, packetBuffer, IP_MAXPACKET, 0, (struct sockaddr *)&sender, &ptrLen);

    const int ipMinSize = 20;
    if (packet_len == -1 || packet_len == 0 || packet_len < ipMinSize)
        panic("recieveIPpacket: no messages are available at the socket.");
    struct ip *ipPac = (struct ip *)packetBuffer;
    if (ntohs(ipPac->ip_len) != packet_len)
        panic("recieveIPpacket: recived an incomplete IP packet.");
    return packet_len;
}

char *IcmpUtil::unpackIp(char *ipPacket)
{
    struct ip *ipHeader = (struct ip *)ipPacket;
    const ssize_t ipHeaderLen = 4 * ipHeader->ip_hl;
    return (char *)ipPacket + ipHeaderLen;
}

void IcmpUtil::changeTTL(int ttl, int sockfd)
{
    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == -1)
        panic("setsockopt error.");
}

sockaddr_in IcmpUtil::consRecipient()
{
    sockaddr_in recipient;
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    return recipient;
}
