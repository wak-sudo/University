// Wojciech Kieloch 339952 2024 SK

#include "Tools.h"

#include "panic.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cmath>

std::string Tools::ipToStr(unsigned ip)
{
    char strBuf[20];
    struct in_addr inAdd;
    inAdd.s_addr = htonl(ip);
    const char *ret = inet_ntop(AF_INET, &inAdd, strBuf, INET_ADDRSTRLEN);
    if (ret == NULL)
        panic("Tools::ipToStr");
    return strBuf;
}

unsigned Tools::strToIp(const char *str)
{
    struct in_addr inAdd;
    int ret = inet_pton(AF_INET, str, &inAdd);
    if (ret <= 0)
        panic("Tools::strToIp", false);
    return ntohl(inAdd.s_addr);
}

std::string Tools::charArrayToString(char *arr, unsigned fragStart, unsigned fragEnd)
{
    std::string res;
    for (unsigned i = fragStart; i < fragEnd; i++)
        res += arr[i];
    return res;
}

void Tools::log(std::string msg)
{
#ifdef DEBUG
    std::cout << msg << std::endl;
#endif
    (void)(msg); // to supress warnings.
}

int Tools::getSocket()
{
    int mySocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mySocket == -1)
        panic("Tools::getSocket");
    return mySocket;
}

int Tools::getFileDesc(std::string fileName)
{
    int mySocket = c_open(fileName.c_str());
    return mySocket;
}

void Tools::c_write(int fd, const void *buf, size_t count)
{
    ssize_t ret = write(fd, buf, count);
    if (ret < 0 || (size_t)ret != count)
        panic("Tools::c_write -> fd: " + std::to_string(fd) + " ret: " + std::to_string(ret));
}

void Tools::c_writev(int fd, iovec *iov, int iovcnt)
{
    ssize_t ret = writev(fd, iov, iovcnt);
    ssize_t totalSize = 0;
    for (int i = 0; i < iovcnt; i++)
        totalSize += iov[i].iov_len;
    if (ret != totalSize)
        panic("Tools::c_writev");
}

int Tools::c_open(const char *pathname)
{
    int fd = open(pathname, O_CREAT | O_CLOEXEC | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1)
        panic("Tools::c_open");
    return fd;
}

Tools::ParsedArgs Tools::parseArgs(int argc, char *argv[]) noexcept(false)
{
    if (argc != 5)
        panic("Tools::parseArgs -> Argc:" + std::to_string(argc), false);
    unsigned ip = strToIp(argv[1]);
    unsigned short port = std::stoul(argv[2]);
    std::string fileName = argv[3];
    unsigned fileSize = std::stoul(argv[4]);
    ParsedArgs res(ip, port, fileName, fileSize);
    return res;
}

std::string Tools::toPercent(double val)
{
    val = std::round(val * 10000.0) / 100.0;
    std::string res = std::to_string(val);
    res.erase(res.find_last_not_of('0') + 1, std::string::npos);
    res.erase(res.find_last_not_of('.') + 1, std::string::npos);
    return res + "%";
}