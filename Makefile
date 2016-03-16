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

all: robot clean

install: robot clean
	mv robot $(INSTALL_PATH)
	-mkdir $(FOLDER_PATH)
	touch $(USB_PATH) $(TCP_PATH)
	cp get_USBidbyTTY.sh $(FOLDER_PATH)
	-chmod -R 777 $(FOLDER_PATH)

robot: main.o robot.o uuidwatcher.o
	$(CC) -o build/$(ARCH)/$@ $^ $(LDFLAGS)

main.o: robot.h uuidwatcher.h

robot.o: robot.h error.h

uuidwatcher.o: uuidwatcher.h error.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	-rm -rf *.o
	-rm -rf *~
	
uninstall:
	-rm -rf $(INSTALL_PATH)/robot
	-rm -rf $(FOLDER_PATH)
