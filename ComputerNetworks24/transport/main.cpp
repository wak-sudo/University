// Wojciech Kieloch 339952 2024 SK

#include <iostream>

#include "Client.h"
#include "Tools.h"

int main(int argc, char *argv[])
{
    Tools::ParsedArgs arguments;
    try
    {
        arguments = Tools::parseArgs(argc, argv);
    }
    catch (...)
    {
        std::cout << "Invalid arguments." << std::endl;
        return 0;
    }

    Client myClient(arguments.ip, arguments.port);
    myClient.getFile(arguments.fileName, arguments.fileSize);

    return 0;
}