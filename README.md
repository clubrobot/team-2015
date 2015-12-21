# robot-utility

A little utility to assist the robot configuration.

It is a simple command line tool which can be used to:

* Set the USB mapping table of the daemon
* Set its IP address and the associated port

The resulting files can be found at :
- */etc/robot/usbmapping.cfg*
- */etc/robot/TCP.cfg*

See [Communication protocol](https://github.com/IR-RC/robot-documentation/wiki/Communication-protocol) for more information.

## Installation

Just clone this repository, open it in a terminal and tip: `sudo make install`

To uninstall it, just tip in the same way: `sudo make uninstall`

## Usage

This utility is decomposed in two subroutines: `robot usb` and `robot tcp`

You can tip one of the following commands:

* `robot usb list`

  Print the current USB mapping and a short description for every of its slots.

* `robot usb add id description`

  Add a new USB slot to the mapping table (up to 20).
  
  Be careful, `id` is not the Module's UUID but the id which will be used to identify it when receiving a Message ;
  the UUID is determined automatically by connecting the module when prompted to.

* `robot usb remove id`

  Remove the USB slot with index `id`.
  
* `robot usb clear`

  Remove all the USB slots of the mapping table.

* `robot tcp show`

  Print the current TCP configuration.

* `robot tcp set ip port`

  Set the IP address and the port to `ip` and `port`.
