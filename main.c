#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "robot.h"
#include "uuidwatcher.h"

#define FOLDER_PATH "/etc/robot/"
#define USB_PATH FOLDER_PATH "usbmapping.cfg"
#define TCP_PATH FOLDER_PATH "TCP.cfg"

/////////////////////////////////////////////////////////////////////////////////////////

#define LOAD_USB_MAPPING( map )\
	{ initUSBMapping( &map ); if( !loadUSBMapping( &map, USB_PATH ) )\
	{ printf( "Can't load USB mapping: %s", USB_PATH ); return -1; } }

#define SAVE_USB_MAPPING( map )\
	{ if( !saveUSBMapping( &map, USB_PATH ) )\
	{ printf( "Can't save USB mapping" ); return -1; } }

#define LOAD_TCP_CONFIG( cfg )\
	{ initTCPConfig( &cfg ); if( !loadTCPConfig( &cfg, TCP_PATH ) )\
	{ printf( "Can't load TCP config: %s", TCP_PATH ); return -1; } }

#define SAVE_TCP_CONFIG( cfg )\
	{ if( !saveTCPConfig( &cfg, TCP_PATH ) )\
	{ printf( "Can't save TCP config" ); return -1; } }

/////////////////////////////////////////////////////////////////////////////////////////

// USB mapping related commands
int usb_list( int argc, char* argv[] );
int usb_add( int argc, char* argv[] );
int usb_remove( int argc, char* argv[] );
int usb_clear( int argc, char* argv[] );

// TCP config related commands
int tcp_show( int argc, char* argv[] );
int tcp_set( int argc, char* argv[] );

// Miscellaneous commands
int help( int argc, char* argv[] );

/////////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[] )
{
	if( !createDirectory( FOLDER_PATH ) )
	{
		printf( "Can't create directory: %s", FOLDER_PATH );
		return -1;
	}
	if( argc > 1 )
	{
		if( strcmp( argv[ 1 ], "usb" ) == 0 )
		{
			if( argc > 2 )
			{
				if( strcmp( argv[ 2 ], "list" ) == 0 )
				{
					return usb_list( argc, argv );
				}
				else if( strcmp( argv[ 2 ], "add" ) == 0 )
				{
					return usb_add( argc, argv );
				}
				else if( strcmp( argv[ 2 ], "remove" ) == 0 )
				{
					return usb_remove( argc, argv );
				}
				else if( strcmp( argv[ 2 ], "clear" ) == 0 )
				{
					return usb_clear( argc, argv );
				}
			}
		}
		else if( strcmp( argv[ 1 ], "tcp" ) == 0 )
		{
			if( argc > 2 )
			{
				if( strcmp( argv[ 2 ], "show" ) == 0 )
				{
					return tcp_show( argc, argv );
				}
				else if( strcmp( argv[ 2 ], "set" ) == 0 )
				{
					return tcp_set( argc, argv );
				}
			}
		}
	}
	return help( argc, argv );
}

/////////////////////////////////////////////////////////////////////////////////////////

int usb_list( int argc, char* argv[] )
{
	USBMapping map;
	LOAD_USB_MAPPING( map )
	if( map.numSlots != 0 )
	{
		printUSBMapping( &map );
		return 0;
	}
	else
	{
		printf( "USB mapping is empty\n" );
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

int usb_add( int argc, char* argv[] )
{
	USBMapping map;
	int id = -1;
	char desc[ 141 ];
	char uuid[ 20 ];
	UUIDWatcher w;
	int i;
	LOAD_USB_MAPPING( map )
	if( argc > 3 )
	{
		sscanf( argv[ 3 ], "%d", &id );
		if( argc > 4 )
		{
			strcpy( desc, argv[ 4 ] );
			for( i = 5; i < argc; i++ )
			{
				strcat( desc, " " );
				strcat( desc, argv[ i ] );
			}
		}
		initUUIDWatcher( &w );
		scanUUID( &w, uuid );
		closeUUIDWatcher( &w );
		if( id > -1 )
		{
			addUSBSlot(&map, uuid, id, desc );
			SAVE_USB_MAPPING( map )
			return 0;
		}
		else
		{
			printf( "ID %d is invalid\n", id );
			return -1;
		}
	}
	return help( argc, argv );
}

/////////////////////////////////////////////////////////////////////////////////////////

int usb_remove( int argc, char* argv[] )
{
	USBMapping map;
	int found;
	int i, j;
	LOAD_USB_MAPPING( map )
	if( argc > 3 )
	{
		i = -1;
		sscanf( argv[ 3 ], "%d", &i );
		if( i > -1 )
		{
			for( j = 0; j < map.numSlots; j++ )
			{
				if( map.slots[ j ].id == i )
				{
					removeUSBSlot( &map, j );
					found = 1;
				}
			}
			if( found )
			{
				SAVE_USB_MAPPING( map )
				return 0;
			}
		}
		else
		{
			printf( "ID %d not found\n", i );
			return -1;
		}
	}
	return help( argc, argv );
}

/////////////////////////////////////////////////////////////////////////////////////////

int usb_clear( int argc, char* argv[] )
{
	USBMapping map;
	initUSBMapping( &map );
	SAVE_USB_MAPPING( map )
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

int tcp_show( int argc, char* argv[] )
{
	TCPConfig cfg;
	LOAD_TCP_CONFIG( cfg )
	printTCPConfig( &cfg );
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

int tcp_set( int argc, char* argv[] )
{
	TCPConfig cfg;
	int i = -1;
	LOAD_TCP_CONFIG( cfg )
	if( argc > 4 )
	{
		sscanf( argv[ 4 ], "%d" , &i );
		setTCPConfig( &cfg, argv[ 3 ], i );
		SAVE_TCP_CONFIG( cfg )
		return 0;
	}
	return help( argc, argv );
}

/////////////////////////////////////////////////////////////////////////////////////////

int help( int argc, char* argv[] )
{
	printf("Usage:\n");
	printf("\trobot usb list\n" );
	printf("\trobot usb clear\n" );
	printf("\trobot usb add id \"description\"\n");
	printf("\trobot usb remove id\n");
	printf("\trobot tcp show\n");
	printf("\trobot tcp set ip port\n");
	return -1;
}
