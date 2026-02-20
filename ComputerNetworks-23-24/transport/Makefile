# Wojciech Kieloch 339952 2024

CPPFLAGS= -std=c++20 -Wall -Wextra -O3 -Iheaders -g #-DDEBUG
PROJECT_NAME=transport.elf

COMPILE=g++ $(CPPFLAGS) -c 
LINK=g++ $(CPPFLAGS) -o $(PROJECT_NAME)

BIN_DIR=bin
MOVE_TO_BIN_DIR=mv -f *.o $(BIN_DIR)

#####################################

TASK_LIST=panic main Buffer BufferHandler Client Tools
OBJ_LIST= bin/main.o bin/panic.o bin/Buffer.o bin/BufferHandler.o bin/Client.o bin/Tools.o
all: $(TASK_LIST)
	$(LINK) $(OBJ_LIST)

main:
	$(COMPILE) main.cpp -o $(BIN_DIR)/main.o

panic:
	$(COMPILE) panic.cpp -o $(BIN_DIR)/panic.o

Buffer:
	$(COMPILE) Buffer.cpp -o $(BIN_DIR)/Buffer.o

BufferHandler:
	$(COMPILE) BufferHandler.cpp -o $(BIN_DIR)/BufferHandler.o

Client:
	$(COMPILE) Client.cpp -o $(BIN_DIR)/Client.o

Tools:
	$(COMPILE) Tools.cpp -o $(BIN_DIR)/Tools.o
	
clean:
	rm -f $(BIN_DIR)/*.o; rm -f *.o

distclean: clean
	rm -f $(PROJECT_NAME)


