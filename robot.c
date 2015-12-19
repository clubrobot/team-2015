#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "robot.h"
#include "error.h"

/////////////////////////////////////////////////////////////////////////////////////////

int createDirectory( char* filename )
{
    struct stat st;
    if( stat( filename, &st ) == -1 )
    {
        if( mkdir( filename, 0777 ) == -1 )
        {
            ERROR_ARGS( "cannot create directory %s\n", filename )
            return 0;
        }
    }
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////

void initUSBMapping( USBMapping* mapping )
{
    mapping->numSlots = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

int loadUSBMapping( USBMapping* mapping, char* filename )
{
    FILE* file;
    file = fopen( filename, "r" );
    if( file == NULL )
    {
    	ERROR_ARGS( "cannot open file %s\n", filename )
        return 0;
    }
    for( mapping->numSlots = 0; mapping->numSlots < USB_MAX_SLOTS; mapping->numSlots++ )
    {
        if( fscanf( file, "%s %d%*[ ]%[^\n]s",
            mapping->slots[ mapping->numSlots ].uuid,
            &mapping->slots[ mapping->numSlots ].id,
            mapping->slots[ mapping->numSlots ].desc ) < 2 )
        {
            break;
        }
    }
    fclose( file );
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////

int saveUSBMapping( USBMapping* mapping, char* filename )
{
    FILE* file;
    int i;
    file = fopen( filename, "w" );
    if( file == NULL )
    {
    	ERROR_ARGS( "cannot open file %s\n", filename )
        return 0;
    }
    for( i = 0; i < mapping->numSlots; i++ )
    {
        fprintf( file, "%s %d %s\n",
            mapping->slots[ i ].uuid,
            mapping->slots[ i ].id,
            mapping->slots[ i ].desc );
    }
    fclose( file );
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////

void printUSBMapping( USBMapping* mapping )
{
    int i;
    if( mapping != NULL )
    {
        for( i = 0; i < mapping->numSlots; i++ )
        {
            printf( "%s %d %s\n",
                mapping->slots[ i ].uuid,
                mapping->slots[ i ].id,
                mapping->slots[ i ].desc );
        }
    }
    else
    {
        printf( "NULL\n" );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

int addUSBSlot( USBMapping* mapping, char* uuid, int id, char* desc )
{
    if( mapping->numSlots < USB_MAX_SLOTS )
    {
        strcpy( mapping->slots[ mapping->numSlots ].uuid, uuid );
        mapping->slots[ mapping->numSlots ].id = id;
        if( desc != NULL )
            strcpy( mapping->slots[ mapping->numSlots ].desc, desc );
        mapping->numSlots++;
        return 1;
    }
    else
    {
    	ERROR_ARGS( "cannot add new USBSlot (%d slots max)\n", USB_MAX_SLOTS )
        return 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

int removeUSBSlot( USBMapping* mapping, int i )
{
    if( i >= 0 && i < mapping->numSlots )
    {
        for( ; i < mapping->numSlots - 1; i++ )
        {
            mapping->slots[ i ] = mapping->slots[ i + 1 ];
        }
        mapping->numSlots--;
        return 1;
    }
    else
    {
    	ERROR_ARGS( "cannot remove USBSlot %d (out of range)\n", i );
        return 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void initTCPConfig( TCPConfig* config )
{
    strcpy( config->ip, "localhost" );
    config->port = 3000;
}

/////////////////////////////////////////////////////////////////////////////////////////

int loadTCPConfig( TCPConfig* config, char* filename )
{
    FILE* file;
    file = fopen( filename, "r" );
    if( file == NULL )
    {
    	ERROR_ARGS( "cannot open file %s\n", filename )
        return 0;
    }
    fscanf( file, "%s %d", config->ip, &config->port );
    fclose( file );
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////

int saveTCPConfig( TCPConfig* config, char* filename )
{
    FILE* file;
    file = fopen( filename, "w" );
    if( file == NULL )
    {
    	ERROR_ARGS( "saveTCPConfig: cannot open file %s\n", filename )
        return 0;
    }
    fprintf( file, "%s %d", config->ip, config->port );
    fclose( file );
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////

void setTCPConfig( TCPConfig* config, char* ip, int port )
{
    strcpy( config->ip, ip );
    config->port = port;
}

/////////////////////////////////////////////////////////////////////////////////////////

void printTCPConfig( TCPConfig* config )
{
    if( config != NULL )
    {
        printf( "%s %d\n", config->ip, config->port );
    }
    else
    {
        printf( "NULL\n" );
    }
}
