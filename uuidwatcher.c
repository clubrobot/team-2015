#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uuidwatcher.h"

/////////////////////////////////////////////////////////////////////////////////////////

int initUUIDWatcher( UUIDWatcher* watcher )
{
	watcher->i = 0;
	watcher->len = 0;
	watcher->fd = inotify_init();
	if( watcher->fd == -1 )
	{
		fprintf( stderr, "initUUIDWatcher: cannot create inotify file descriptor" );
		return 0;
	}
	watcher->wd = inotify_add_watch( watcher->fd, UUID_PATH, IN_CREATE );
	if( watcher->wd == -1 )
	{
		fprintf( stderr, "initUUIDWatcher: cannot add inotify watch descriptor" );
		return 0;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

int pumpUUIDWatcher( UUIDWatcher* watcher )
{
	watcher->i = 0;
	watcher->len = read( watcher->fd, watcher->buf, EVENT_BUFFER_LENGTH );
	if( watcher->len == -1 )
	{
		fprintf( stderr, "pumpUUIDWatcher: cannot read inotify buffer" );
		watcher->len = 0;
		return 0;
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////

void clearUUIDWatcher( UUIDWatcher* watcher )
{
	watcher->len = 0;
	watcher->i = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

void closeUUIDWatcher( UUIDWatcher* watcher )
{
	inotify_rm_watch( watcher->fd, watcher->wd );
	close( watcher->fd );
}

/////////////////////////////////////////////////////////////////////////////////////////

int waitUUID( UUIDWatcher* watcher, char* dst )
{
	struct inotify_event *event;
	if( !watcher->len || watcher->i >= watcher->len )
	{
		pumpUUIDWatcher( watcher );
	}
	if( !watcher->len )
	{
		return 0;
	}
	event = ( struct inotify_event* ) &watcher->buf[ watcher->i ];
	if( event->len )
	{
		if( dst )
		{
			strcpy( dst, event->name );
		}
	}
	watcher->i += EVENT_SIZE + event->len;
	return 1;
}
