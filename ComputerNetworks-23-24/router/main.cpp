// Wojciech Kieloch 339952 2024 SK

#include <iostream>
#include <cassert>
#include <unistd.h>
#include <cstring>

#include "NetTools.h"
#include "RoutingTable.h"
#include "RoutingMSG.h"

using namespace std;

bool glob_debug_active = false;

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-d") == 0)
        glob_debug_active = true;
    NetTools::log("Debug active.");

    // Main program:

    int interfaceCount = 0;

    cin >> interfaceCount;

    assert(interfaceCount > 0);

    RoutingTable routesTable;

    for (int i = 0; i < interfaceCount; i++)
    {
        std::string interfaceAddrStr, sugar, distStr;
        cin >> interfaceAddrStr >> sugar >> distStr;
        unsigned distance = (unsigned)stoul(distStr);
        routesTable.addInterface(interfaceAddrStr, distance);
    }

    int socket = NetTools::createServer();
    NetTools::setBroadcastPermission(socket);

    while (true)
    {
        NetTools::listen(socket, routesTable);

        NetTools::spread(socket, routesTable);

        routesTable.turnEnd();
    }

    close(socket);
    return 0;
}