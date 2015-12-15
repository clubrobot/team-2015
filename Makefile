CC=gcc
CFLAGS=-Wall -pedantic -errors
LDFLAGS=
ifeq ($(DEBUG),yes)
	CFLAGS+= -g
endif
INSTALL_PATH=/usr/bin/
FOLDER_PATH=/etc/robot/
USB_PATH=$(FOLDER_PATH)usbmapping.cfg
TCP_PATH=$(FOLDER_PATH)TCP.cfg

install: robot clean
	mv robot $(INSTALL_PATH)

robot: main.o robot.o uuidwatcher.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: robot.h uuidwatcher.h

robot.o: robot.h

uuidwatcher.o: uuidwatcher.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf *~
	
uninstall: 
	rm -rf $(INSTALL_PATH)robot/
	rm -rf $(FOLDER_PATH)
	
