# Wojciech Kieloch 339952 2024

CPPFLAGS= -std=c++20 -Wall -Wextra -O3 -Iheaders -g

COMPILE=g++ $(CPPFLAGS) -c 
LINK=g++ $(CPPFLAGS) -o traceroute

TASK_LIST=MyUtil IcmpUtil panic main
OBJ_LIST=bin/MyUtil.o bin/IcmpUtil.o bin/panic.o bin/main.o

BIN_DIR=bin
MOVE_TO_BIN_DIR=mv -f *.o $(BIN_DIR)

all: $(TASK_LIST)
	$(LINK) $(OBJ_LIST)

MyUtil:
	$(COMPILE) MyUtil.cpp -o $(BIN_DIR)/MyUtil.o

IcmpUtil: 
	$(COMPILE) IcmpUtil.cpp -o $(BIN_DIR)/IcmpUtil.o

panic:
	$(COMPILE) panic.cpp -o $(BIN_DIR)/panic.o

main:
	$(COMPILE) main.cpp -o $(BIN_DIR)/main.o
	
clean:
	rm -f $(BIN_DIR)/*.o; rm -f *.o

distclean: clean
	rm -f traceroute


