SRCDIR :=

#All directories that contain sourcefiles
SUBDIRS := 

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
	g++ -Wall -c -std=c++0x -fPIC -pthread -I $(INC_PATH) -o "$@" "$<"

binary: $(OBJS)
	g++ -o "$(BINARY)" $(OBJS) $(LIBS)

clean_obj:
	rm $(OBJS)

all: binary

clean: clean_obj
	rm $(BINARY)

install:
	cp $(BINARY) $(BIN_INSTALL_DIR)/$(BINARY)
	cp --parents get_TTYbyUSBid.sh /etc/robot
	
uninstall:
	rm $(BIN_INSTALL_DIR)/$(BINARY)
