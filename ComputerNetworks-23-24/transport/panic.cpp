// Wojciech Kieloch 339952 2024

#include "panic.h"

#include <iostream>
#include <cstring>

void panic(std::string msg, bool errnoSet)
{
    if (errnoSet)
        std::cerr << "Errno: " << errno << " (" << strerror(errno) << ")" << std::endl;
    throw std::runtime_error(msg);
}