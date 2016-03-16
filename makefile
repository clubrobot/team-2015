CC=$(CROSS_COMPILE)g++
ARCH?=i86
INSTALL_DIR?=/usr/
#All directories that contain sourcefiles
SUBDIRS := Log

#Load all .cpp files in the subdirs
SRCS := $(wildcard $(SUBDIRS:%=%/*.cpp))
SRCS += $(wildcard *.cpp)

OBJS := $(SRCS:.cpp=.o)

INC := $(SRCS:.cpp=.h)

INC_PATH := /usr/include/

LIBS := -lpthread -lrobot-comlib

LIBNAME = robot-robot

BINARY := lib$(LIBNAME).so

LIB_INSTALL_DIR = $(INSTALL_DIR)lib
INC_INSTALL_DIR = $(INSTALL_DIR)include/$(LIBNAME)

#ne cree pas les binaires pour les sous-repertoires
%.o: %.cpp
	$(CC) -Wall -c -std=c++0x -fPIC -pthread -I $(INC_PATH) -o "$@" "$<"

all: $(OBJS)
	$(CC) -shared -o "build/$(ARCH)/$(BINARY)" $(OBJS) $(LIBS)

clean:
	-rm $(OBJS)
	-rm build/*/$(BINARY)

install:
	cp build/$(ARCH)/$(BINARY) $(LIB_INSTALL_DIR)/$(BINARY)
	-mkdir $(INC_INSTALL_DIR)
	-mkdir $(INC_INSTALL_DIR)/Log
	cp *.h $(INC_INSTALL_DIR)
	cp Log/*.h $(INC_INSTALL_DIR)/Log

	
uninstall:
	-rm -r $(INC_INSTALL_DIR)
	-rm $(LIB_INSTALL_DIR)/$(BINARY)
