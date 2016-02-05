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

LIB_INSTALL_DIR := /usr/lib
INC_INSTALL_DIR := /usr/include

#ne cree pas les binaires pour les sous-repertoires
%.o: %.cpp
	g++ -Wall -c -std=c++0x -fPIC -pthread -I $(INC_PATH) -o "$@" "$<"

binary: $(OBJS)
	g++ -shared -o "$(BINARY)" $(OBJS) $(LIBS)

clean_obj:
	rm $(OBJS)

all: binary

clean: clean_obj
	rm $(BINARY)

install:
	cp $(BINARY) $(LIB_INSTALL_DIR)/$(BINARY)
	mkdir $(INC_INSTALL_DIR)
	mkdir $(INC_INSTALL_DIR)/Log
	cp *.h $(INC_INSTALL_DIR)
	cp Log/*.h $(INC_INSTALL_DIR)/Log

	
uninstall:
	rm -r $(INC_INSTALL_DIR)
	rm $(LIB_INSTALL_DIR)/$(BINARY)
