#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <robot-comlib/Socket/TCPSocket.h>
#include <robot-robot/Log/LogClient.h>
#include "robot.h"
#include "uuidwatcher.h"

#define FOLDER_PATH "/etc/robot/"
#define USB_PATH FOLDER_PATH "usbmapping.cfg"
#define TCP_PATH FOLDER_PATH "TCP.cfg"

/////////////////////////////////////////////////////////////////////////////////////////

#define DEFAULT "\e[0m"
#define ERROR "\e[91m" // red ; I do not understand why a warning is raised here...
#define SUCCESS "\e[92m" // green
#define WARNING "\e[93m" // yellow
#define FIELD "\e[1m" // bold

/////////////////////////////////////////////////////////////////////////////////////////

#define LOAD_USB_MAPPING( map )\
		{ initUSBMapping( &map ); if( !loadUSBMapping( &map, USB_PATH ) )\
		{ printf( WARNING "Cannot load USB mapping\nThe file may not exist: %s\n" DEFAULT, USB_PATH ); } }

#define SAVE_USB_MAPPING( map )\
		{ if( !saveUSBMapping( &map, USB_PATH ) )\
	{ printf( ERROR "Cannot save USB mapping\nYou may not have the right permissions: %s\n" DEFAULT, TCP_PATH ); return -1; } }

#define LOAD_TCP_CONFIG( cfg )\
		{ initTCPConfig( &cfg ); if( !loadTCPConfig( &cfg, TCP_PATH ) )\
		{ printf( WARNING "Cannot load TCP config\nThe file may not exist: %s\n" DEFAULT, TCP_PATH ); } }

#define SAVE_TCP_CONFIG( cfg )\
		{ if( !saveTCPConfig( &cfg, TCP_PATH ) )\
	{ printf( ERROR "Cannot save TCP config\nYou may not have the right permissions: %s\n" DEFAULT, TCP_PATH ); return -1; } }

/////////////////////////////////////////////////////////////////////////////////////////

// TCPSocket
TCPSocket socket_socket;
int socket_port;
std::string socket_address;
int load_tcp_config();
int open_socket();
void close_socket();

// USB mapping related commands
int usb_list( int argc, char* argv[] );
int usb_add( int argc, char* argv[] );
int usb_remove( int argc, char* argv[] );
int usb_clear( int argc, char* argv[] );
int usb_reload( int argc, char* argv[] );

// TCP config related commands
int tcp_show( int argc, char* argv[] );
int tcp_set( int argc, char* argv[] );
int tcp_log( int argc, char* argv[] );

// TCP remote command
int rmt_cmd( int argc, char* argv[] );

// Miscellaneous commands
int help( int argc, char* argv[] );

/////////////////////////////////////////////////////////////////////////////////////////

void myPrintUSBSlot( USBSlot* slot, int success )
{
	printf( "%s%d\t%s\t%s\n" DEFAULT, ( success ) ? SUCCESS : "",  slot->id, slot->uuid, slot->desc );
}

/////////////////////////////////////////////////////////////////////////////////////////

void myPrintUSBMapping( USBMapping* map, int success )
{
	size_t i;
	printf( FIELD "ID\tUUID\t\tDescription\n" DEFAULT );
	for( i = 0; i < map->numSlots; i++ )
	{
		myPrintUSBSlot( &map->slots[ i ], i == success );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void myPrintTCPConfig( TCPConfig* cfg, int success )
{
	printf( FIELD "IP address\tPort\n" DEFAULT );
	printf( "%s%s\t%d\n" DEFAULT, ( success ) ? SUCCESS : "", cfg->ip, cfg->port );
}

/////////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[] )
{
	if( !createDirectory( FOLDER_PATH ) )
	{
		printf( ERROR "Can't create directory: %s\n" DEFAULT, FOLDER_PATH );
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
				else if( strcmp( argv[ 2 ], "reload" ) == 0 )
				{
					return usb_reload( argc, argv );
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
				else if( strcmp( argv[ 2 ], "log" ) == 0 )
				{
					return tcp_log( argc, argv );
				}
			}
		}
		else if( strcmp( argv[ 1 ], "remote" ) == 0 )
		{
			return rmt_cmd( argc, argv );
		}
	}
	return help( argc, argv );
}

int load_tcp_config() {
	int ret = 0;
	std::ifstream file;
	std::string port, configfilepath = "/etc/robot/TCP.cfg";

	try {
		file.open(configfilepath);
		file >> socket_address >> port;

		socket_port = std::stoi(port);
	}
	catch(std::ifstream::failure &exception) {
		std::cerr << "Cannot open TCP config file at : " << configfilepath << std::endl;
		ret = -1;
	}
	catch(std::invalid_argument &exception) {
		std::cerr << "Config file at : " << configfilepath << "is invalid\n"
				"Switching to default config" << std::endl;
		ret = -1;
	}
	file.close();

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////
int open_socket() {
	int ret = 0;
	try {
		socket_socket.connect(socket_address, socket_port);
	}
	catch(SocketException &exception) {
		std::cerr << exception.what() << std::endl;
		ret = -1;
	}

	return ret;
}

void close_socket() {
	socket_socket.close();

}

/////////////////////////////////////////////////////////////////////////////////////////
int usb_list( int argc, char* argv[] )
{
	USBMapping map;
	LOAD_USB_MAPPING( map )
	myPrintUSBMapping( &map, -1 );
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

int usb_add( int argc, char* argv[] )
{
	USBMapping map;
	int id = -1;
	char desc[ 141 ];
	char uuid[ 20 ];
	char tty[16];
	char cmd[40]="/etc/robot/get_USBidbyTTY.sh ";
	UUIDWatcher w;
	FILE *fp;

	LOAD_USB_MAPPING( map )
	if( argc > 3 )
	{
		sscanf( argv[ 3 ], "%d", &id );
		if( argc > 4 )
		{
			strcpy( desc, argv[ argc-1] );
		}

		if(argc == 5) {
			printf( "Please (re-)connect the device to detect its UUID...\n" );
			fflush( stdout );
			initUUIDWatcher( &w );
			scanUUID( &w, tty );
			closeUUIDWatcher( &w );

			printf("Device detected\n\tCOM port on %s\n", tty);
		}
		else if(argc == 6) {
			strcpy(tty, argv[ 4 ]);
		}

		usleep(500000);

		strcat(cmd, tty);
		/* Open the command for reading. */
		fp = popen(cmd, "r");
		if (fp == NULL) {
			printf("Failed to run command\n" );
		}
		/* Read the output a line at a time - output it. */
		while(fgets(uuid, sizeof(uuid), fp) != NULL) ;

		uuid[strlen(uuid)-1] = 0;

		/* close */
		pclose(fp);

		printf("\tUUID is %s\n", uuid);

		// UUID invalid
		if(strcmp(":", uuid)==0) {
			printf( ERROR "UIID %s is invalid\n" DEFAULT, uuid );
			return -1;
		}
		// ID invalid
		else if( id <= 0 )
		{
			printf( ERROR "ID %d is invalid\n" DEFAULT, id );
			return -1;
		}
		// Valid
		else
		{
			addUSBSlot(&map, uuid, id, desc );
			SAVE_USB_MAPPING( map )
			printf( SUCCESS "The device has been successfully added\n" DEFAULT );
			myPrintUSBMapping( &map, map.numSlots - 1 );
			return 0;
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
			for( j = 0; j < (int)map.numSlots; j++ )
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
			else
			{
				printf( ERROR "ID %d does not exist\n" DEFAULT, i );
				return -1;
			}
		}
		else
		{
			printf( ERROR "The specified ID is not valid\n" DEFAULT);
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

int usb_reload( int argc, char* argv[] )
{
	int ret;
	if(!(ret = load_tcp_config())) {

		printf( SUCCESS "The config file has been loaded\n" DEFAULT );

		ret = open_socket();
		uint8_t cmd[] = {1, 0, 0};


		if(!ret) {
			printf( SUCCESS "Connection done\n" DEFAULT );
			socket_socket.write(cmd, 3);
		}

		printf( SUCCESS "Command sent\n" DEFAULT );
		close_socket();
	}

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////

int tcp_show( int argc, char* argv[] )
{
	TCPConfig cfg;
	LOAD_TCP_CONFIG( cfg )
	myPrintTCPConfig( &cfg, 0 );
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
		printf( SUCCESS "The TCP path has been successfully set\n" DEFAULT );
		myPrintTCPConfig( &cfg, 1 );
		return 0;
	}
	return help( argc, argv );
}

int tcp_log( int argc, char* argv[] ) {
	int ret;
	if(!(ret = load_tcp_config())) {

		socket_port = 3003;

		printf( SUCCESS "The config file has been loaded\n" DEFAULT );

		LogClient log;

		log.launch(socket_address, socket_port);

		log.join();

	}

	return ret;
}

int rmt_cmd( int argc, char* argv[] ) {
		int ret;
		if(!(ret = load_tcp_config())) {

			printf( SUCCESS "The config file has been loaded\n" DEFAULT );

			ret = open_socket();

			if(!ret) {
				printf( SUCCESS "Connection done\n" DEFAULT );
				std::string cmd;

				for(int i=2; i<argc; i++) {
					cmd += std::string(argv[i]) + " ";
				}

				uint8_t* command = new uint8_t[3+cmd.size()+1];
				command[0] = cmd.size()+2;
				command[1] = 0;
				command[2] = 1;
				memcpy(command+3, cmd.c_str(), cmd.size()+1);

				socket_socket.write((uint8_t*)command, cmd.size()+4);

				delete(command);

				char c;
				while(socket_socket.read(&c, 1)) {
					std::cout << c << std::flush;
					if(c == 0) break;
				}

				close_socket();
			}

		}

		return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////

int help( int argc, char* argv[] )
{
	for(int i=0; i<argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("\n\n");

	printf( "Usage:\n"
			"  robot\tusb\t\n"
			"  \t\tlist\n"
			"  \t\tclear\n"
			"  \t\tadd\t<id>\t<description>\n"
			"  \t\tadd\t<id>\t<tty device>\t<description>\n"
			"  \t\tremove\t<id>\n"
			"  \t\treload\n"
			"  robot\ttcp\t\n"
			"  \t\tshow\n"
			"  \t\tset\t<ip>\t<port>\n"
			"  \t\tlog\n"
			"  robot\tremote\t<command>\n"
			"  robot help\n" );
	return -1;
}
