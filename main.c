#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "robot.h"

#define FOLDER_PATH "/home/amadou/Bureau/robot/"
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
    if(argc > 1)
    {
    	if(strcmp(argv[1],"usb")== 0)
    	{
    		if(strcmp(argv[2],"list")== 0)
    		{
    					if(map.numSlots != 0) printUSBMapping(&map);
    					else printf("%s est vide !\n",USB_PATH);
    		}
    		if(strcmp(argv[2],"add")== 0)
    		{
    		}

    		if(strcmp(argv[2],"clear")== 0)
    		{
    					initUSBMapping( &map );
    					saveUSBMapping(&map,USB_PATH);
    		}

    		if(strcmp(argv[2],"remove")== 0)
    		{
    			int i = -1;
    					sscanf(argv[3],"%d",&i);printf("-- %d --\n",i);
    					if(i > -1 )
    					{
    						removeUSBSlot(&map,i);
    						saveUSBMapping(&map,USB_PATH);
    					}
    					else
    					{
    						printf("le paramettre id est absent !\n");
    						printf("usage:\n robot usb remove id\n");
    					}
    		}
    	}
    }

    printTCPConfig( &cfg );
    saveTCPConfig( &cfg, TCP_PATH );

    return 0;
}
