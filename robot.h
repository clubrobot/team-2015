#ifndef __ROBOT_H__
#define __ROBOT_H__

/*///////////////////////////////////////////////////////////////////////////////////////*/

#define USB_UUID_LENGTH 10 // "xxxx-xxxx\0"
#define USB_DESC_LENGTH 141 // Like a tweet! :v

#define USB_MAX_SLOTS 20

#define TCP_IP_LENGTH 16 // "xxx.xxx.xxx.xxx\0"

/*///////////////////////////////////////////////////////////////////////////////////////*/

int createDirectory( char* filename );

/*///////////////////////////////////////////////////////////////////////////////////////*/

struct USBSlot
{
    char uuid[ USB_UUID_LENGTH ];
    int id;
    char desc[ USB_DESC_LENGTH ];
    struct USBSlot* next;
};
typedef struct USBSlot USBSlot;

/*///////////////////////////////////////////////////////////////////////////////////////*/

struct USBMapping
{
    USBSlot slots[ USB_MAX_SLOTS ];
    size_t numSlots;
};
typedef struct USBMapping USBMapping;

/*///////////////////////////////////////////////////////////////////////////////////////*/

void initUSBMapping( USBMapping* mapping );

int loadUSBMapping( USBMapping* mapping, char* filename );

int saveUSBMapping( USBMapping* mapping, char* filename );

int addUSBSlot( USBMapping* mapping, char* uuid, int id, char* desc );

int removeUSBSlot( USBMapping* mapping, int i );

void printUSBMapping( USBMapping* mapping );

/*///////////////////////////////////////////////////////////////////////////////////////*/

struct TCPConfig
{
    char ip[ TCP_IP_LENGTH ];
    int port;
};
typedef struct TCPConfig TCPConfig;

/*///////////////////////////////////////////////////////////////////////////////////////*/

void initTCPConfig( TCPConfig* config ); // useless at the moment

int loadTCPConfig( TCPConfig* config, char* filename );

int saveTCPConfig( TCPConfig* config, char* filename );

void setTCPConfig( TCPConfig* config, char* ip, int port );

void printTCPConfig( TCPConfig* config );


/*********************************** void showHelp() ******************************************/
void showHelp();
#endif /*__ROBOT_H__ */
