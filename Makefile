CC=$(CROSS_COMPILE)gcc
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

SRCS := $(wildcard *.c)

BUILD_DIR := build/$(ARCH)

OBJS := $(SRCS:.c=.o)

OBJS_LINK := $(addprefix $(BUILD_DIR)/,$(OBJS))

BINARY := robot

all: create_dir $(OBJS_LINK)
	$(CC) -o $(BUILD_DIR)/$(BINARY) $(OBJS_LINK) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	-rm -r build/$(ARCH)/*
	
.PHONY: create_dir
create_dir:
	-@mkdir build $(BUILD_DIR) 2> /dev/null || true

install: robot clean
	mv robot $(INSTALL_PATH)
	-mkdir $(FOLDER_PATH)
	touch $(USB_PATH) $(TCP_PATH)
	echo "127.1.1.0 3000" > $(TCP_PATH)
	cp get_USBidbyTTY.sh $(FOLDER_PATH)
	-chmod -R 777 $(FOLDER_PATH)
	
uninstall:
	-rm -rf $(INSTALL_PATH)/robot
	-rm -rf $(FOLDER_PATH)
