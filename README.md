# robot-utility
===============

A little utility to assist the robot configuration. 
Are currently supported:
* USB mapping (an UUID, an id and a short description)
* TCP configuration (an IP address and a port)

## Installation:

Just clone this repository, open it in a terminal and tip: "sudo make install"
To uninstall it just tip in the same way: "sudo make uninstall"

## Usage:

This is a command line tool only

* robot usb list
* robot usb add id description
* robot usb remove id
* robot usb clear
* robot tcp show
* robot tcp set ip port
