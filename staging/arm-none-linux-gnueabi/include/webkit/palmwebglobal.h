/* ============================================================
 * Date  : 2008-09-22
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBGLOBAL_H
#define WEBOSWEBGLOBAL_H

#include <glib.h>
#include <signal.h>
#include <stdio.h>

#include <string>

#include "palmwebdefines.h"

namespace v8
{
    class Context;
}

namespace Palm
{
	/**
	 * We use the same dbDump/dbRestore API's to backup and restore the cookie database
	 * but use this phony URL to identify the cookie database.
	 */
	const char* const k_PhonyCookieUrl = "cookie:db";

	struct DbBackupStatus {
		std::string url;      ///< The URL of the database being backed-up/restored.
		std::string dbname;   ///< The database name (not to be confused with the file name).
		int         err;      ///< The status code (see palmerrorcodes.h).
	};

	/**
	 * Definition of an interface that receives WebKit events.
	 *
	 * @note These functions are always called from the same thread that owns the 
	 *       GMainLoop passed into WebGlobal::init().
	 */
	class WebKitEventListener {
		public:
		virtual	void	dbDumpStarted	( const DbBackupStatus& status, void* userData ) = 0;
		virtual	void	dbDumpStopped	( const DbBackupStatus& status, void* userData ) = 0;
		virtual	void	dbRestoreStarted( const DbBackupStatus& status, void* userData ) = 0;
		virtual	void	dbRestoreStopped( const DbBackupStatus& status, void* userData ) = 0;
		virtual	void	dbMoveStatus    ( int err ) = 0;
	};

const unsigned int TextIndexer_PhoneNumber       = 0x01;   ///< Telephone numbers
const unsigned int TextIndexer_EmailAddress      = 0x02;   ///< email addresses
const unsigned int TextIndexer_WebLink           = 0x04;   ///< hyperlinks (with scheme)
const unsigned int TextIndexer_SchemalessWebLink = 0x08;   ///< hyperlinks w/o scheme
const unsigned int TextIndexer_Emoticon          = 0x10;   ///< emoticons :-)
const unsigned int TextIndexer_Default           = 0xff;   ///< Link everything.


class WEBKIT_API WebGlobal {

public:

	struct CacheTypeStatistic {
		int count;
		int size;
		int liveSize;
		int decodedSize;
	};

	struct CacheStatistics {
		CacheTypeStatistic images;
		CacheTypeStatistic cssStyleSheets;
		CacheTypeStatistic scripts;
		CacheTypeStatistic fonts;
	};

	static void init(GMainLoop* loop, WebKitEventListener* eventListener = NULL);
	static void initUsingSnapshot(GMainLoop* loop, const char* snapshotFile, WebKitEventListener* eventListener = NULL );
	
	static GMainLoop* mainLoop();

	static void setCookies(const char* url, const char* cookie);
	static std::string cookies(const char* url);

	static void clearCache();
	static void clearFontCache();
	static void clearLocalStorage();
	static void clearCookies();
	static void clearDiskImageCache();
	static void clearDOMCache();

	static void resetDateCache();
	static void garbageCollectNow();
	static void garbageCollectSoon();

    enum GCAvoidType {
        AVOID_ALL,
        AVOID_OLDGEN,
    };

    static void avoidGC(GCAvoidType type, unsigned long timeoutInMs = 5000);
    static void reallowGC(GCAvoidType type);
    static void resetGCAvoids();
	
    // Tells webkit to that it can clean up memory if it desires because the
    // device is idle and has some spare CPU cycles.
    // Can call repeatedly until it returns true to indicate that there's no
    // more work to do.
    static bool notifyIdle();

    // Tells webkit to clean up memory in preparation for the device going
    // to sleep.  Call repeatedly until it returns true to indicate that
    // there's no more work to do.
    static bool notifySleep();

    // Tells webkit to clean up memory in preparation for the device has just
    // woken up from a sleep, to cancel a previous sleep notification.  
    // Call repeatedly until it returns true to indicate that there's no
    // more work to do.
    static bool notifyWake();

    // Tells webkit to clean up memory aggressively to recover from a low
    // memory condition.
    static void notifyLowMemory();

    static void requestIdleGC();
    static bool canV8ContextReadFile(const v8::Context* context, const char* fileName);

    static bool handleSignal(int sig, siginfo_t *info, void *context);
    static void reportCrashDiagnostics(int sig, siginfo_t *info, void *context,
                                       int logfileFD, bool doVerboseCrashLogging,
                                       volatile bool *hasCrashedInHandler);

	static std::string runTextIndexerOnHtml( const std::string& inHtml, unsigned int flags = TextIndexer_Default );
	
	static std::string version();
	
	static void setUaProf( const std::string& uaProf );
	static const std::string& getUaProf();

	static void setLocale( const char* newLocale );
    static void setLocaleCollator(const char* newLocaleCollator);
	static const char* getLocale( );
    static const char* getLocaleCollator();

	static void addAppendedHTTPHeader( const char* name, const char* value );
	
	static void enableDebugger( bool toggle );
	
	static void setJavaScriptFlags( const char* flagsString );
	
	static void setJavaScriptTimeoutMs( unsigned long inTimeoutMs );	
	static void enableJavaScriptTimeout( bool bEnable );

	static CacheStatistics getCacheStatistics();

	static void restartNetworking();
	
	static void deleteDatabasesForDomain( const char* url );
	static bool copyDatabasesToDomain(const std::string& srcUrl, const std::string& dstUrl);

    static bool startDatabaseDump(const std::string& url, const std::string& dbname, 
                                  const std::string& dumpFile, void *userData, const std::string& cookieAppId = "");
    static bool startDatabaseRestore(const std::string& url, const std::string& dbname,
                                     const std::string& dumpFile, void* userData, const std::string& cookieAppId = "");
    static bool getDatabaseModInfo(const std::string& url, const std::string& dbname,
                                   time_t& mtime, int& numOpenMods, const std::string& cookieAppId = "");

	static void setSystemSuspending(bool);
	static bool isSystemSuspending();

	// For global search: This should be moved into a 
	// service for the browser application.
	static bool queryBrowserHistoryBookmarks( const char* key, int maxOut, std::string& jsonOut );

	static bool getSystemMemoryInfoMb(int& memTotal, int& memFree, int& swapTotal,
									  int& swapFree, int& cached, int& swapCached);

	static float getSystemAvailableMemoryScaleFactor();
	static bool smartKeySearchResponse(int requestId, const std::string& match);
	
	// Reporting (profiling) interface
	static void profilerEventStart( const std::string& name, const std::string& value );
	static void profilerEventEnd( const std::string& name, const std::string& value );

	static void setActiveApplicationId( const std::string& id );
	static const std::string& getActiveApplicationId();

};

};

// For backward compatibility. FIXME: Remove
extern "C" {
WEBKIT_API GMainLoop* webkit_palm_get_mainloop();
}


#endif /* WEBOSWEBGLOBAL_H */
