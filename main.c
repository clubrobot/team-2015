#include <stdio.h>
#include <stdlib.h>
#include "robot.h"

#define FOLDER_PATH "/home/ulysse/Bureau/robot/"
// #define FOLDER_PATH "/etc/robot/"
#define USB_PATH FOLDER_PATH "usbmapping.cfg"
#define TCP_PATH FOLDER_PATH "TCP.cfg"

int main( int argc, char* argv[] )
{
    USBMapping map;
    TCPConfig cfg;

    createDirectory( FOLDER_PATH );

    initUSBMapping( &map );
    loadUSBMapping( &map, USB_PATH );

    /* create a mapping from scratch
    initUSBMapping( &map );
    addUSBSlot( &map, "1234-5678", 0, "first slot" );
    addUSBSlot( &map, "0411-1995", 20, "my birthday" );
    addUSBSlot( &map, "8094-7319", 6, "" );
    addUSBSlot( &map, "1001-1001", 10, "" );
    addUSBSlot( &map, "4815-1623", 42, "lost" );
    removeUSBSlot( &map, 2 );
    //*/

    printUSBMapping( &map );
    saveUSBMapping( &map, USB_PATH );

    initTCPConfig( &cfg );
    loadTCPConfig( &cfg, TCP_PATH );

    /* create a config from scratch
    setTCPConfig( &cfg, "123.456.789.ABC", 1995 );
    //*/

    printTCPConfig( &cfg );
    saveTCPConfig( &cfg, TCP_PATH );

    return 0;
}
