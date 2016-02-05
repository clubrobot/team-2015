#!/bin/bash
#This basic script return the usb vendorID:modelID from tty device name
#Author : Julien Maurat 02/2016

modelID="$(udevadm info -q property --name=$1 | grep 'ID_MODEL_ID')"
vendorID="$(udevadm info -q property --name=$1 | grep 'ID_VENDOR_ID')"
devID="$(echo $vendorID | egrep -o [0-9a-fA-F]{4}):$(echo $modelID | egrep -o [0-9a-fA-F]{4})"
echo "$devID"
