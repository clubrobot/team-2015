#ifndef __ERROR_H__
#define __ERROR_H__

/////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
	#define VERBOSE 1
#else
	#define VERBOSE 0
#endif

/////////////////////////////////////////////////////////////////////////////////////////

#define ERROR( info )\
	{ if( VERBOSE )\
	{ fprintf( stderr, "%s: " info, __FUNCTION__ ); } }

#define ERROR_ARGS( info, ... )\
	{ if( VERBOSE )\
	{ fprintf( stderr, "%s: " info, __FUNCTION__, __VA_ARGS__ ); } }

#endif // ERROR_H_
