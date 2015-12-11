#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "robot.h"

#define FOLDER_PATH "/home/amadou/Bureau/robot/"
// #define FOLDER_PATH "/etc/robot/"
#define USB_PATH FOLDER_PATH "usbmapping.cfg"
#define TCP_PATH FOLDER_PATH "TCP.cfg"

void showHelp()
{
	printf("Usage:\n");
	printf("1)robot usb list ---pour lister les uuid\n");
	printf("2) robot usb clear ---pour effacher tous les uuid\n");
	printf("3) robot usb add id [description] ---pour ajouter un uuid\n");
	printf("4) robot usb remove id ---pour supprimer un uuid en particulier\n");
	printf("5) robot tcp show ---affiche l'ip et le port\n");
	printf("6) robot tcp set ip port ---attribue un nouveau ip et port\n");
}

int main( int argc, char* argv[] )
{
    USBMapping map;
    TCPConfig config;
    int help = 0;

    createDirectory( FOLDER_PATH );

    initUSBMapping( &map );
    loadUSBMapping( &map, USB_PATH );
    if(argc > 1)
    {
    	if(strcmp(argv[1],"usb")== 0)
    	{
    		if(argc > 2)
    		{
    		if(strcmp(argv[2],"list")== 0)
    		{
    					if(map.numSlots != 0) printUSBMapping(&map);
    					else printf("%s est vide !\n",USB_PATH);
    		}else
    		if(strcmp(argv[2],"add")== 0)
    		{
    			char *desc = NULL;
    			int id = -1, i;
    			char* uuid = "1547-2589";
    			if(argc > 3)
    			{
    			 sscanf(argv[3],"%d",&id);
    			 if(argc > 4 ){ desc = argv[4];
    				 for(i=5;i < argc; ++i){ strcat( desc," "); strcat(desc,argv[i]);}}
    			 if(id > -1 ) addUSBSlot(&map, uuid, id, desc );
    			 saveUSBMapping(&map,USB_PATH);
    			}else help =1;
    		}
    		else
    		if(strcmp(argv[2],"clear")== 0)
    		{
    					initUSBMapping( &map );
    					saveUSBMapping(&map,USB_PATH);
    		}
    		else
    		if(strcmp(argv[2],"remove")== 0)
    		{
    			int i = -1, j=0, v = 0;
    				if(argc > 3) sscanf(argv[3],"%d",&i);printf("-- %d --\n",i);
    					if(i > -1 )
    					{
    						for(j=0;j<map.numSlots;++j)
    						{
    							if(map.slots[j].id == i)
    							{
    							 removeUSBSlot(&map,j);
    							 v = 1;
    							}
    						}
    						if(v == 1)
    						saveUSBMapping(&map,USB_PATH);
    						else
    							printf("l'id est incorrect !\n");
    					}
    					else
    					{
    						printf("le paramettre id est absent !\n");
    						printf("usage:\n robot usb remove id\n");
    					}
    		}else help = 1;
    	 }else help =1;
    	}
    	else
    	{

    		if(strcmp(argv[1],"tcp")== 0)
    		{

    			initTCPConfig(&config);
    			loadTCPConfig(&config,TCP_PATH);
                if(argc < 3){ showHelp(); return 0;}
    			if(strcmp(argv[2],"show")== 0)
    			{
    				printTCPConfig(&config);
    			}else
    			if(strcmp(argv[2],"set")== 0)
    			{
    				if(argc > 4)
    				{
						int i = -1;
						sscanf(argv[4],"%d",&i);
						setTCPConfig(&config, argv[3], i);
						saveTCPConfig( &config, TCP_PATH );
    				}else help =1;
    			}else help =1;
    		} else help =1;
    	}
    }
    else help =1;

    if(help) showHelp();

    return 0;
}
