
// Copyright 2009 Palm Inc.

#ifndef __ObjectLog_h__
#define __ObjectLog_h__

#include <string>

#define WEBOS_OBJECT_LOG_ENABLE

#ifdef WEBOS_OBJECT_LOG_ENABLE
	
	#define WEBOS_OBJECT_NEW(obj,n) \
		Palm::ObjectLog::LogNew( obj,#n );
	
	#define WEBOS_OBJECT_DELETE(obj,n) \
		Palm::ObjectLog::LogDelete( obj, #n );
		
	#define WEBOS_LOG(...) {Palm::ObjectLog::Log("Palm " __VA_ARGS__);}
	
	namespace Palm
	{
		
	class ObjectLog 
	{
	public:
		
		static void LogNew( void* obj, const char* name );
		static void LogDelete( void* obj, const char* name );	
		static void Log( const char* ch, ... );	
	};
	
	};

#else
	
	#define WEBOS_OBJECT_NEW(obj,n)
	#define WEBOS_OBJECT_DELETE(obj,n)
	#define WEBOS_LOG(...) (void)0

#endif

void debugGetObjectCountersJSONString( std::string& outString );

#endif
