CC=$(CROSS_COMPILE)g++
ARCH?=i86

CFLAGS=-Wall
LDFLAGS=
ifeq ($(DEBUG),yes)
	CFLAGS+= -g -DDEBUG
endif
INSTALL_PATH=/usr/bin
FOLDER_PATH=/etc/robot
USB_PATH=$(FOLDER_PATH)/usbmapping.cfg
TCP_PATH=$(FOLDER_PATH)/TCP.cfg

SRCS := $(wildcard *.cpp)

BUILD_DIR := build/$(ARCH)

OBJS := $(SRCS:.cpp=.o)

OBJS_LINK := $(addprefix $(BUILD_DIR)/,$(OBJS))

BINARY := robot

all: create_dir $(OBJS_LINK)
	$(CC) -o $(BUILD_DIR)/$(BINARY) $(OBJS_LINK) $(LDFLAGS) -lpthread -lrobot-comlib -lrobot-robot

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -o $@ -c -std=c++0x $< $(CFLAGS) 

clean:
	-rm -r build/$(ARCH)/*
	
.PHONY: create_dir
create_dir:
	-@mkdir build $(BUILD_DIR) 2> /dev/null || true

install:
	mv $(BUILD_DIR)/robot $(INSTALL_PATH)
	-mkdir $(FOLDER_PATH)
	touch $(USB_PATH) $(TCP_PATH)
	echo "127.1.1.0 3000" > $(TCP_PATH)
	cp get_USBidbyTTY.sh $(FOLDER_PATH)
	-chmod -R 777 $(FOLDER_PATH)
	
uninstall:
	-rm -rf $(INSTALL_PATH)/robot
	-rm -rf $(FOLDER_PATH)
