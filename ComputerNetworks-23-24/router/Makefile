# Wojciech Kieloch 339952 2024 SK
# Dodanie flagi -DDEBUG do CPPFLAGS skompiluje projekt w trybie do debugowania.

CPPFLAGS= -std=c++20 -Wall -Wextra -O3 -Iheaders -g
PROJECT_NAME=router.elf

COMPILE=g++ $(CPPFLAGS) -c 
LINK=g++ $(CPPFLAGS) -o $(PROJECT_NAME)

BIN_DIR=bin
MOVE_TO_BIN_DIR=mv -f *.o $(BIN_DIR)

#####################################

TASK_LIST=panic main NetTools RoutingMSG RoutingTable
OBJ_LIST=bin/main.o bin/panic.o bin/NetTools.o bin/RoutingMSG.o bin/RoutingTable.o

all: $(TASK_LIST)
	$(LINK) $(OBJ_LIST)

main:
	$(COMPILE) main.cpp -o $(BIN_DIR)/main.o

panic:
	$(COMPILE) panic.cpp -o $(BIN_DIR)/panic.o

NetTools:
	$(COMPILE) NetTools.cpp -o $(BIN_DIR)/NetTools.o

RoutingMSG:
	$(COMPILE) RoutingMSG.cpp -o $(BIN_DIR)/RoutingMSG.o

RoutingTable:
	$(COMPILE) RoutingTable.cpp -o $(BIN_DIR)/RoutingTable.o
	
clean:
	rm -f $(BIN_DIR)/*.o; rm -f *.o

distclean: clean
	rm -f $(PROJECT_NAME)


