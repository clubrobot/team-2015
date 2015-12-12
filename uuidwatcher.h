#ifndef __UUIDWATCHER_H__
#define __UUIDWATCHER_H__

#include <sys/types.h> // ??
#include <sys/inotify.h>
#include <unistd.h> // ??

/////////////////////////////////////////////////////////////////////////////////////////

#define UUID_PATH "/dev/disk/by-uuid/"

#define EVENT_SIZE ( sizeof( struct inotify_event ) )
#define EVENT_BUFFER_LENGTH ( 1024 * ( EVENT_SIZE + 16 ) )

/////////////////////////////////////////////////////////////////////////////////////////

struct UUIDWatcher
{
	int fd;
	int wd;
	size_t len;
	char buf[ EVENT_BUFFER_LENGTH ];
	int i;
};
typedef struct UUIDWatcher UUIDWatcher;

/////////////////////////////////////////////////////////////////////////////////////////

int initUUIDWatcher( UUIDWatcher* watcher );

int pumpUUIDWatcher( UUIDWatcher* watcher );

void clearUUIDWatcher( UUIDWatcher* watcher );

void closeUUIDWatcher( UUIDWatcher* watcher );

int waitUUID( UUIDWatcher* watcher, char* dst );

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __UUIDWATCHER_H__
