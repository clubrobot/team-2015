#!/bin/bash
#This basic script return the first tty device name coreponding to a usb vendorID:modelID
#Author : Julien Maurat 01/2016

#find all usb dev
for sysdevpath in $(find /sys/bus/usb/devices/usb*/ -name dev); do
    (
#strip /dev part
        syspath="${sysdevpath%/dev}"
#test if device is a tty subsystem
	if [ "$(udevadm info -q property -p $syspath | grep -c 'SUBSYSTEM=tty')" == "1" ]; then
#extract vendorID and modelID from info and put it in a vendorid:modelid format
	modelID="$(udevadm info -q property -p $syspath | grep 'ID_MODEL_ID')"
	vendorID="$(udevadm info -q property -p $syspath | grep 'ID_VENDOR_ID')"
	devID="$(echo $vendorID | egrep -o [0-9a-fA-F]{4}):$(echo $modelID | egrep -o [0-9a-fA-F]{4})"
#test it with the input ID
        	if [ "$devID" == "$1" ]; then
#extract the tty device name and break
		devname="$(udevadm info -q property -p $syspath | grep 'DEVPATH='| egrep -o '[[:alnum:]]+$')"
		echo "$devname"
		break
		fi
	fi
    )
done

