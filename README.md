# TCP-COM communication bridge

This is TCP-COM bridge that is run on the robot embedded system as a deamon. USB keys can be plugged in the robot's USB hub. These USB keys contain control electronics (microcontrollers, LEDs, amplifiers...) that can interact with mechanic systems [(see here for more information)](https://github.com/IR-RC/robot-documentation/wiki/Architecture-overview#overview).
The bridge host a TCP server on which any internal or external client process can connect to. In this way, a client process, developed for a given functionality (ex : motors control), can communicate with any USB key throught the COM port. This is really convenient as clients can be compiled and run on an external computer and remotely interact with the USB keys.

[Please see the wiki for more detailed informations](https://github.com/IR-RC/robot-daemon/wiki)
