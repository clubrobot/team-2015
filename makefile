CC=$(CROSS_COMPILE)g++
ARCH?=i86

#Load all .cpp files in the subdirs
SRCS := $(wildcard $(SUBDIRS:%=$(SRCDIR)/%/*.cpp))
SRCS += $(wildcard *.cpp)

OBJS := $(SRCS:.cpp=.o)

INC := $(SRCS:.cpp=.h)

INC_PATH := /usr/include/

LIBS := -lpthread -lrobot-comlib -lrobot-robot

BINARY := robot-daemon

BIN_INSTALL_DIR := /usr/bin

%.o: %.cpp
	$(CC) -Wall -c -std=c++0x -fPIC -pthread -I $(INC_PATH) -o "$@" "$<"

binary: $(OBJS)
	$(CC) -o "build/$(ARCH)/$(BINARY)" $(OBJS) $(LIBS)

all: binary

clean:
	-rm $(OBJS)
	-rm build/*/$(BINARY)

install:
	cp build/$(ARCH)/$(BINARY) $(BIN_INSTALL_DIR)/$(BINARY)
	cp --parents get_TTYbyUSBid.sh /etc/robot
	
uninstall:
	-rm $(BIN_INSTALL_DIR)/$(BINARY)
