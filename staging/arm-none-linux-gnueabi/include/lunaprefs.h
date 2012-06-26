/* -*-mode: C; fill-column: 78; c-basic-offset: 4; -*- */
/**********************************************************************
 * Copyright (c) 2008 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 **********************************************************************/

#ifndef _LUNAPREFS_H_
#define _LUNAPREFS_H_

#include <stdbool.h>
#include <json.h>
#include <cjson/json.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef int LPErr;
typedef void* LPAppHandle;

/* error codes.  These need to be integrated with other luna codes, I suspect */
#define LP_ERR_NONE            0
#define LP_ERR_INVALID_HANDLE  1 /* you forgot to call LPAppGetHandle first */
#define LP_ERR_NO_SUCH_KEY     2 /* no entry found for that key */
#define LP_ERR_MEM             3 /* out of memory */
#define LP_ERR_NOSUCHERR       4 /* bogus error code */
#define LP_ERR_BUSY            5 /* sqlite db is busy; try again */
#define LP_ERR_VALUENOTJSON    6 /* attempt to store something not a legal json document */
#define LP_ERR_ILLEGALKEY      7 /* empty string key */
#define LP_ERR_SYSCONFIG       8 /* critical system resource is missing */
#define LP_ERR_PARAM_ERR       9 /* something general wrong with parameters passed in */
#define LP_ERR_NOTIMPL        10 /* feature not implemented */
#define LP_ERR_INTERNAL       11 /* some component I called reported failure */
#define LP_ERR_DBERROR        12

    /**
     * Add a file FOO with contents "BAR" to this directory and you now have a
     * read-only system property com.palm.preferences.FOO with value "BAR".
     * Stored in /tmp, these do not survive a reboot, and the files themselves
     * can be written at will by any app.
     */
#define LP_RUNTIME_DIR "/tmp/misc-props"

/* See for inspiration, especially on scoping:
 * http://developer.apple.com/documentation/CoreFoundation/Conceptual/CFPreferences/CFPreferences.html
 */

/*
 * App prefs.  Each app has its own DB.
 */

/**
 * @ brief: nuke the DB associated with this app id.
 */
LPErr LPAppClearData( const char* appId );

LPErr LPAppGetHandle( const char* appId, LPAppHandle* handle );

/**
 * @param handle     returned via LPAppGetHandle.
 *
 * @param commit true means commit all statements actions made against
 *                   this handle, false means roll them all back.
 *
 */
LPErr LPAppFreeHandle( LPAppHandle handle, bool commit );


LPErr LPAppCopyValue( LPAppHandle handle, const char* key, char** jstr );
    /** LPAppCopyValueString 
     *
     * @brief convenience function.  Looks up value in DB, assumes it's an
     * array of one string, and returns that string.
     */
LPErr LPAppCopyValueString( LPAppHandle handle, const char* key, char** str );
LPErr LPAppCopyValueInt( LPAppHandle handle, const char* key, int* intValue );
LPErr LPAppCopyValueJ( LPAppHandle handle, const char* key, json_t** json );
LPErr LPAppCopyValueCJ( LPAppHandle handle, const char* key, struct json_object** json );

LPErr LPAppSetValue( LPAppHandle handle, const char* key, const char* const jstr );
    /** LPAppSetValueString 
     *
     * @brief convenience function.  Takes string, wraps it as an array of one
     * string to make it a legal json, and stores it.
     */
LPErr LPAppSetValueString( LPAppHandle handle, const char* key, const char* const str );
LPErr LPAppSetValueInt( LPAppHandle handle, const char* key, int intValue );
LPErr LPAppSetValueJ( LPAppHandle handle, const char* key, const json_t* json );
LPErr LPAppSetValueCJ( LPAppHandle handle, const char* key, struct json_object* json );

LPErr LPAppRemoveValue( LPAppHandle handle, const char* key );

/**
 * LPAppCopyKeys
 * 
 * Return in *json ptr to json consisting of a json array of strings
 * representing all the keys in the null-terminated string g_malloc'd
 * internally.  Caller must call g_free when done.
 */
LPErr LPAppCopyKeys( LPAppHandle handle, char** jstr );
LPErr LPAppCopyKeysJ( LPAppHandle handle, json_t** json );
LPErr LPAppCopyKeysCJ( LPAppHandle handle, struct json_object** json );

/**
 * LPAppCopyAll
 * 
 * Return in *json ptr to json-formatted string consisting of a json array of
 * key/value pairs representing all the keys and values.  The null-terminated
 * string returned is g_malloc'd internally.  Caller must call g_free when done.
 */
LPErr LPAppCopyAll( LPAppHandle handle, char** jstr );
LPErr LPAppCopyAllJ( LPAppHandle handle, json_t** json );
LPErr LPAppCopyAllCJ( LPAppHandle handle, struct json_object** json );


/*
 * Sys prefs.  There's one DB conceptually.  In reality the values can
 * come from anywhere: ROM tokens, sysfs entries, whatever.  These are
 * read-only values: no setters.  char* values returned are malloc'd
 * and belong to the caller, which must free() them when finished.
 */

/**
 * LPSystemCopyStringValue
 * 
 * Return in *value ptr to value only as null-terminated string
 * g_malloc'd internally.  Caller must call g_free when done.
 *
 * If we decide that the public interface return json objects only
 * then this becomes private.
 */
LPErr LPSystemCopyStringValue( const char* key, char** jstr );

/**
 * LPSystemCopyValue
 * 
 * Return in *json ptr to json consisting of { key : value } as
 * null-terminated string g_malloc'd internally.  Caller must call
 * g_free when done.
 */
LPErr LPSystemCopyValue( const char* key, char** jstr );
LPErr LPSystemCopyValueJ( const char* key, json_t** json );
LPErr LPSystemCopyValueCJ( const char* key, struct json_object** json );

/**
 * LPSystemCopyKeys
 * 
 * Return in *json ptr to json consisting of a json array of strings
 * representing all the keys in the null-terminated string g_malloc'd
 * internally.  Caller must call g_free when done.
 */

LPErr LPSystemCopyKeys( char** jstr );
LPErr LPSystemCopyKeysJ( json_t** json );
LPErr LPSystemCopyKeysCJ( struct json_object** json );

LPErr LPSystemCopyKeysPublic( char** jstr ); /* for use by the service only */
LPErr LPSystemCopyKeysPublicCJ( struct json_object** json ); /* for use by the service only */

/**
 * LPSystemCopyAll
 * 
 * Return in *json ptr to json-formatted string consisting of a json array of
 * key/value pairs representing all the keys and values.  The null-terminated
 * string returned is g_malloc'd internally.  Caller must call g_free when done.
 */
LPErr LPSystemCopyAll( char** jstr );
LPErr LPSystemCopyAllJ( json_t** json );
LPErr LPSystemCopyAllCJ( struct json_object** json );

LPErr LPSystemCopyAllPublic( char** jstr ); /* for use by the service only */
LPErr LPSystemCopyAllPublicCJ( struct json_object** json ); /* for use by the service only */

LPErr LPSystemKeyIsPublic( const char* key, bool* allowedOnPublicBus ); /* for use by the service only */

/**
 * LPErrorString
 * 
 * Return in *str ptr to user-readable string explanaing the error.  Caller must
 * call g_free when done.
 */
LPErr LPErrorString( LPErr err, char** str );

/*
 * Tokens: read-only system properties, e.g. BT address
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _LUNAPREFS_H_ */
