CROSS_COMPILE?=
ARCH?=i86
INSTALL_DIR?=/usr/

CC=$(CROSS_COMPILE)g++

#All directories that contain sourcefiles
SUBDIRS := Log

#Load all .cpp files in the subdirs
SRCS := $(wildcard $(SUBDIRS:%=%/*.cpp))
SRCS += $(wildcard *.cpp)

BUILD_DIR := build/$(ARCH)

OBJS := $(SRCS:.cpp=.o)

OBJS_LINK := $(addprefix $(BUILD_DIR)/,$(OBJS))

INC := $(SRCS:.cpp=.h)

INC_PATH := /usr/include/

LIBS := -lpthread -lrobot-comlib

LIBNAME = robot-robot

BINARY := lib$(LIBNAME).so

LIB_INSTALL_DIR = $(INSTALL_DIR)lib
INC_INSTALL_DIR = $(INSTALL_DIR)include/$(LIBNAME)

#ne cree pas les binaires pour les sous-repertoires
$(BUILD_DIR)/%.o: %.cpp
	$(CC) -Wall -c -std=c++0x -fPIC -pthread -I $(INC_PATH) -o $@ "$<"

all: create_dir $(OBJS_LINK)
	$(CC) -shared -o $(BUILD_DIR)/$(BINARY) $(OBJS_LINK) $(LIBS)

clean:
	-rm -r build/$(ARCH)/*
	
create_dir:
	-@mkdir build $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SUBDIRS)) 2> /dev/null || true

install:
	cp $(BUILD_DIR)/$(BINARY) $(LIB_INSTALL_DIR)/$(BINARY)
	-@mkdir $(INC_INSTALL_DIR)
	-@mkdir $(INC_INSTALL_DIR)/Log
	cp *.h $(INC_INSTALL_DIR)
	cp Log/*.h $(INC_INSTALL_DIR)/Log

	
uninstall:
	-rm -r $(INC_INSTALL_DIR)
	-rm $(LIB_INSTALL_DIR)/$(BINARY)
