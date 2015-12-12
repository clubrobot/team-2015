CC=gcc
CFLAGS=-Wall -pedantic -errors
LDFLAGS=
ifeq ($(DEBUG),yes)
	CFLAGS+= -g
endif
FOLDER_PATH=/home/ulysse/Bureau/robot/
USB_PATH=$(FOLDER_PATH)usbmapping.cfg
TCP_PATH=$(FOLDER_PATH)TCP.cfg

all: robot

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
