CC=$(CROSS_COMPILE)g++
ARCH?=i86

#Load all .cpp files in the subdirs
SRCS := $(wildcard *.cpp)

BUILD_DIR := build/$(ARCH)

OBJS := $(SRCS:.cpp=.o)

OBJS_LINK := $(addprefix $(BUILD_DIR)/,$(OBJS))

INC := $(SRCS:.cpp=.h)

INC_PATH := /usr/include/

LIBS := -lpthread -lrobot-comlib -lrobot-robot

BINARY := robot-strategy

BIN_INSTALL_DIR := /usr/bin

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -Wall -c -std=c++0x -fPIC -pthread -I $(INC_PATH) -o "$@" "$<"

all: create_dir $(OBJS_LINK)
	$(CC) -o $(BUILD_DIR)/$(BINARY) $(OBJS_LINK) $(LIBS)

clean:
	-rm -r build/$(ARCH)/*

create_dir:
	-@mkdir build $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SUBDIRS)) 2> /dev/null || true

install:
	cp build/$(ARCH)/$(BINARY) $(BIN_INSTALL_DIR)/$(BINARY)
	
uninstall:
	-rm $(BIN_INSTALL_DIR)/$(BINARY)
