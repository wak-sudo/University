// Wojciech Kieloch 339952 2024 SK

#pragma once

#include <string>
#include <sys/uio.h>

namespace Tools
{
    struct ParsedArgs
    {
        unsigned ip;
        unsigned fileSize;
        unsigned short port;
        std::string fileName;
        ParsedArgs(unsigned ipArg, unsigned short portArg, std::string fileNameArg, unsigned fileSizeArg) :
        ip(ipArg), fileSize(fileSizeArg), port(portArg), fileName(fileNameArg) {}
        ParsedArgs() {}
    };

    int getSocket();
    int getFileDesc(std::string fileName);
    std::string charArrayToString(char* arr, unsigned fragStart, unsigned fragEnd);
    std::string ipToStr(unsigned ip);
    unsigned strToIp(const char *str);
    void log(std::string msg);
    std::string toPercent(double val);

    // Wrappers:
    void c_write(int fd, const void *buf, size_t count);
    void c_writev(int fd, iovec *iov, int iovcnt);
    int c_open(const char *pathname);

    ParsedArgs parseArgs(int argc, char *argv[]) noexcept(false);
}