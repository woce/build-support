// @@@LICENSE
//
//      Copyright (c) 2007-2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

/**
 * @mainpage
 *
 * <h1>PmLogLib</h1>
 *
 * This library supports instrumenting code to produce runtime text output
 * to indicate run status.
 * We differentiate output into two types, tracing and logging.
 *   
 * Tracing code is for detailed debugging for use by individual component
 * development.  It is turned on only locally and only as needed, and is
 * *not* included in the main build or release product.  The system
 * support for tracing code will not be as efficient in this case as it
 * will lean more towards ease of use.
 *  
 * Logging code, on the other hand, is included in the main build and 
 * release product.  The purpose is to log errors and important diagnostics 
 * information in the device logs.
 * 
 * Logging code may also support more verbose diagnostic
 * levels which may be turned on dynamicly as needed on the device.  The
 * intent of the system is that logging code which is not enabled has
 * minimal performance impact.  In particular, a logging call which is not
 * enabled should not result in a library call or evaluation of parameters.
 * This is enabled by requiring logging clients to initialize a logging
 * context that is managed by the PmLog system.  The context includes a
 * memory field that can be quickly checked by the logging call to know
 * whether the call is enabled.
 *  
 * <em>Example usage:</em>
 * 
 * @code
 *	PmLogContext	gMyContext;
 * 
 *	void MyComponentInit(void)
 *	{
 * 		// Get a pointer to the context for this component.  
 * 		// The context is created if it does not already exist.
 * 		PmLogGetContext("PmMyComponent", &gMyContext);
 *	}
 *
 *	void MyComponentRun(void)
 *	{
 * 		int err;
 * 
 *		PmLogPrintDebug(gMyContext, "Calling Foo");
 * 		err = Foo();
 * 		if (err)
 * 		{
 *			PmLogPrintError(gMyContext, "Foo error %d", err);
 * 		}
 * 	}
 * @endcode
 * 
 **********************************************************************/

/**
* @brief  This header file specifies the public interface to PmLogLib
*
* @file PmLogLib.h
* <hr>
**/

#ifndef PMLOGLIB_H
#define PMLOGLIB_H


#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C"
{
#endif


//#####################################################################


// GCC supplies the __attribute__ extension which we take advantage of.
//
// In particular we use the 'format' attribute that tells GCC to do
// 'printf'-style checking, e.g. that the variable arguments match
// the format string in type and number.  E.g. "%s (%d)" would require
// a character string and integer parameters to follow, else a compiler
// warning would result.

/* If we're not using GNU C, elide __attribute__ */
#ifndef __GNUC__
#define __attribute__(x)  /* NOTHING */
#endif


// note: we use macros rather than inline function declarations to
// avoid potential configuration and usage issues.


//#####################################################################


// Error class for this module.
// This should really come from a common Palm header somewhere.
#define PMLOG_ERR(offset)	(0x6C670000 | offset)


/*********************************************************************/
/* PmLogErr */
/**
@brief  Type definition for error codes returned by this module's APIs.
**********************************************************************/

//?? To Do: clean up and rename these to be more clear

enum
{
	kPmLogErr_None					= 0,
	//------------------------------------------------
	kPmLogErr_InvalidParameter		= PMLOG_ERR(1),
	kPmLogErr_InvalidContextIndex	= PMLOG_ERR(2),
	kPmLogErr_InvalidContext		= PMLOG_ERR(3),
	kPmLogErr_InvalidLevel			= PMLOG_ERR(4),
	kPmLogErr_InvalidFormat			= PMLOG_ERR(5),
	kPmLogErr_InvalidData			= PMLOG_ERR(6),
	kPmLogErr_NoData				= PMLOG_ERR(7),
	kPmLogErr_TooMuchData			= PMLOG_ERR(8),
	kPmLogErr_LevelDisabled			= PMLOG_ERR(9),
	kPmLogErr_FormatStringFailed	= PMLOG_ERR(10),
	kPmLogErr_TooManyContexts		= PMLOG_ERR(11),
	kPmLogErr_InvalidContextName	= PMLOG_ERR(12),
	kPmLogErr_ContextNotFound		= PMLOG_ERR(13),
	kPmLogErr_BufferTooSmall		= PMLOG_ERR(14),
	//------------------------------------------------
	kPmLogErr_Unknown				= PMLOG_ERR(999)
};

typedef int32_t PmLogErr;


//#####################################################################


/*********************************************************************/
/* PmLogLevel */
/**
@brief  Type definition for discrete logging level.
		The values are intentionally identical to the equivalent syslog
		priority value.
**********************************************************************/
enum
{
	kPmLogLevel_None		= -1,	/* no output */
	kPmLogLevel_Emergency	= 0,	/* system is unusable */
	kPmLogLevel_Alert		= 1,	/* action must be taken immediately */
	kPmLogLevel_Critical	= 2,	/* critical conditions */
	kPmLogLevel_Error		= 3,	/* error conditions */
	kPmLogLevel_Warning		= 4,	/* warning conditions */
	kPmLogLevel_Notice		= 5,	/* normal but significant condition */
	kPmLogLevel_Info		= 6,	/* informational */
	kPmLogLevel_Debug		= 7		/* debug-level messages */
};

typedef int PmLogLevel;


//#####################################################################


// arbitrary maximum length of context name
#define PMLOG_MAX_CONTEXT_NAME_LEN	63


// arbitrary maximum number of context
#define PMLOG_MAX_NUM_CONTEXTS		226


//#####################################################################


/*********************************************************************/
/* PmLogContext */
/**
@brief  Type definition for the logging context as returned by
		PmLogGetContext.  This is a read-only data view.  Clients
		should treat this as an opaque structure, however it is
		referenced by the macro/inline functions here.
**********************************************************************/

typedef struct
{
	int	enabledLevel;	/* levels <= enabledLevel are enabled */
	int flags;
}
PmLogContextInfo;

typedef const PmLogContextInfo* PmLogContext; 


/*********************************************************************/
/* kPmLogGlobalContext */
/**
@brief  For efficiency, every client component should get a context
		using PmLogGetContext and use that for subsequent logging calls.
		But, for simplicity of the client we'll also allow specifying
		the global context via a special value.  But in that case,
		the client-side level check can't be made inline, so every log 
		call will incur the cost of the library call and parameter
		evaluation.
**********************************************************************/
#define kPmLogGlobalContext	((PmLogContext) NULL)


/*********************************************************************/
/* kPmLogGlobalContextName */
/**
@brief  This is the context name reported for the global context.
		Note that it uses special characters so it won't conflict
		with user-defined context names.
**********************************************************************/
#define kPmLogGlobalContextName "<global>"


/*********************************************************************/
/* PmLogGetNumContexts */
/**
@brief  Returns the number of defined contexts, including the global
		context.

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidParameter
**********************************************************************/
PmLogErr PmLogGetNumContexts(int* pNumContexts);


/*********************************************************************/
/* PmLogGetIndContext */
/**
@brief  Returns the context by index where index = 0..numContexts - 1.

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidParameter
**********************************************************************/
PmLogErr PmLogGetIndContext(int contextIndex, PmLogContext* pContext);


/*********************************************************************/
/* PmLogFindContext */
/**
@brief  Returns the logging context for the named context, or
		NULL if the context does not exist.

		If contextName is NULL, an error is returned.
		
@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidParameter
			kPmLogErr_InvalidContext
			kPmLogErr_InvalidContextName
**********************************************************************/
PmLogErr PmLogFindContext(const char* contextName, PmLogContext* pContext);


/*********************************************************************/
/* PmLogGetContext */
/**
@brief  Returns/creates the logging context for the named context.
		
		If contextName is NULL, returns the global context.
		
		Context names must be 1..31 characters long, and each
		character must be one of A-Z, a-z, 0-9, '_', '-', '.'.
		
		Component hierarchies can be indicated using '.' as the path
		separator.
		E.g. "FOO.BAR" would indicate the "BAR" subcomponent
		of the "FOO" component.

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidParameter
			kPmLogErr_InvalidContext
			kPmLogErr_InvalidContextName
**********************************************************************/
PmLogErr PmLogGetContext(const char* contextName, PmLogContext* pContext);


/*********************************************************************/
/* PmLogGetContextInline */
/**
@brief  Returns/creates the logging context for the named context.
		If contextName is NULL, returns the global context.
		This form of the API is not for general use.  It is needed
		to support the trace macros that want to use a named context,
		but can't easily support a global variable to cache the context
		and instead need to look it up every time.
**********************************************************************/
PmLogContext PmLogGetContextInline(const char* contextName);


/*********************************************************************/
/* PmLogGetContextName */
/**
@brief  Returns the name of the specified context into the specified
		string buffer.
		May be used for the global context.

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidParameter
**********************************************************************/
PmLogErr PmLogGetContextName(PmLogContext context, char* contextName,
	size_t contextNameBuffSize);


/*********************************************************************/
/* PmLogGetContextLevel */
/**
@brief  Gets the logging level for the specified context.
		May be used for the global context.  This should generally not
		be used by the components doing logging themselves.
		Instead just use the PmLogPrint etc. APIs which will do
		inline enabled checks.

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidParameter
**********************************************************************/
PmLogErr PmLogGetContextLevel(PmLogContext context, PmLogLevel* levelP);


/*********************************************************************/
/* PmLogSetContextLevel */
/**
@brief  Sets the logging level for the specified context.
		May be used for the global context.  This should generally not
		be used by the components doing logging themselves.  Instead
		the Debug Prefs / Log Manager should be used to set the
		dynamic configuration.

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidContext
			kPmLogErr_InvalidLevel
**********************************************************************/
PmLogErr PmLogSetContextLevel(PmLogContext context, PmLogLevel level);


//#####################################################################


/*********************************************************************/
/* PmLogIsEnabled */
/**
@brief  Returns true if and only if the specified message priority
		is enabled in the specified context.
		
proto:	bool PmLogIsEnabled(PmLogContext context, PmLogLevel level);
**********************************************************************/
#define PmLogIsEnabled(context, level)	\
	(((context) == kPmLogGlobalContext) ||	\
	 ((level) <= (context)->enabledLevel))


//#####################################################################


/*********************************************************************/
/* PmLogPrint_ */
/**
@brief  Logs the specified formatted text to the specified context.

		For efficiency, this API should not be used directly, but
		instead use the wrappers (PmLogPrint, PmLogPrintError, ...) that
		bypass the library call if the logging is not enabled.

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidContext
			kPmLogErr_InvalidLevel
			kPmLogErr_InvalidFormat
**********************************************************************/
PmLogErr PmLogPrint_(PmLogContext context, PmLogLevel level,
	const char* fmt, ...)
     __attribute__((format(printf, 3, 4)));


/*********************************************************************/
/* PmLogPrint */
/**
@brief  Logs the specified formatted text, tagged with the specified
		level, to the specified context.
		
proto:	PmLogErr PmLogPrint(PmLogContext context, PmLogLevel level,
			const char* fmt, ...);

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidContext
			kPmLogErr_InvalidLevel
			kPmLogErr_InvalidFormat
			kPmLogErr_LevelDisabled
**********************************************************************/
#define	PmLogPrint(context, level, ...)	\
	(PmLogIsEnabled(context, level) \
		? PmLogPrint_(context, level, __VA_ARGS__) \
		: kPmLogErr_LevelDisabled)


/*********************************************************************/
/* PmLogPrintError */
/**
@brief  Logs the specified formatted text, tagged as error level,
		to the specified context.
		
proto:	void PmLogPrintError(PmLogContext context,
			const char* fmt, ...);
**********************************************************************/
#define	PmLogPrintError(context, ...)	\
	(void) PmLogPrint(context, kPmLogLevel_Error, __VA_ARGS__)


/*********************************************************************/
/* PmLogPrintWarning */
/**
@brief  Logs the specified formatted text, tagged as warning level,
		to the specified context.
		
proto:	void PmLogPrintWarning(PmLogContext context,
			const char* fmt, ...);
**********************************************************************/
#define	PmLogPrintWarning(context, ...)	\
	(void) PmLogPrint(context, kPmLogLevel_Warning, __VA_ARGS__)


/*********************************************************************/
/* PmLogPrintInfo */
/**
@brief  Logs the specified formatted text, tagged as info level,
		to the specified context.
		
proto:	void PmLogPrintInfo(PmLogContext context,
			const char* fmt, ...);
**********************************************************************/
#define	PmLogPrintInfo(context, ...)	\
	(void) PmLogPrint(context, kPmLogLevel_Info, __VA_ARGS__)


/*********************************************************************/
/* PmLogPrintDebug */
/**
@brief  Logs the specified formatted text, tagged as debug level,
		to the specified context.
		
proto:	void PmLogPrintDebug(PmLogContext context,
			const char* fmt, ...);
**********************************************************************/
#define	PmLogPrintDebug(context, ...)	\
	(void) PmLogPrint(context, kPmLogLevel_Debug, __VA_ARGS__)


//#####################################################################


/*********************************************************************/
/* PmLogVPrint_ */
/**
@brief  Logs the specified formatted text to the specified context.

		For efficiency, this API should not be used directly, but
		instead use the wrappers (PmLogVPrint, PmLogVPrintError, ...)
		that bypass the library call if the logging is not enabled.

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidContext
			kPmLogErr_InvalidLevel
			kPmLogErr_InvalidFormat
**********************************************************************/
PmLogErr PmLogVPrint_(PmLogContext context, PmLogLevel level,
	const char* fmt, va_list args);


/*********************************************************************/
/* PmLogVPrint */
/**
@brief  Logs the specified formatted text, tagged with the specified
		level, to the specified context.
		
proto:	PmLogErr PmLogVPrint(PmLogContext context, PmLogLevel level,
			const char* fmt, va_list args);

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidContext
			kPmLogErr_InvalidLevel
			kPmLogErr_InvalidFormat
			kPmLogErr_LevelDisabled
**********************************************************************/
#define	PmLogVPrint(context, level, fmt, args)	\
	(PmLogIsEnabled(context, level) \
		? PmLogVPrint_(context, level, fmt, args) \
		: kPmLogErr_LevelDisabled)


/*********************************************************************/
/* PmLogVPrintError */
/**
@brief  Logs the specified formatted text, tagged as error level,
		to the specified context.
		
proto:	void PmLogVPrintError(PmLogContext context,
			const char* fmt, va_list args);
**********************************************************************/
#define	PmLogVPrintError(context, fmt, args)	\
	(void) PmLogVPrint(context, kPmLogLevel_Error, fmt, args)


/*********************************************************************/
/* PmLogVPrintWarning */
/**
@brief  Logs the specified formatted text, tagged as warning level,
		to the specified context.
		
proto:	void PmLogVPrintWarning(PmLogContext context,
			const char* fmt, va_list args);
**********************************************************************/
#define	PmLogVPrintWarning(context, fmt, args)	\
	(void) PmLogVPrint(context, kPmLogLevel_Warning, fmt, args)


/*********************************************************************/
/* PmLogVPrintInfo */
/**
@brief  Logs the specified formatted text, tagged as info level,
		to the specified context.
		
proto:	void PmLogVPrintInfo(PmLogContext context,
			const char* fmt, va_list args);
**********************************************************************/
#define	PmLogVPrintInfo(context, fmt, args)	\
	(void) PmLogVPrint(context, kPmLogLevel_Info, fmt, args)


/*********************************************************************/
/* PmLogVPrintDebug */
/**
@brief  Logs the specified formatted text, tagged as debug level,
		to the specified context.
		
proto:	void PmLogVPrintDebug(PmLogContext context,
			const char* fmt, va_list args);
**********************************************************************/
#define	PmLogVPrintDebug(context, fmt, args)	\
	(void) PmLogVPrint(context, kPmLogLevel_Debug, fmt, args)


//#####################################################################


/*********************************************************************/
/* PmLogDumpFormat */
/**
@brief  Placeholder struct.  Later we will allow passing in a struct
		of parameters for explicitly controlling the data dump formatting,
		e.g. allow specifying label offset, width of columns, etc.
		For now just use the magic value kPmLogDumpFormatDefault which
		will correspond to canonical hex + ASCII dump.
**********************************************************************/
struct PmLogDumpFormat;
typedef struct PmLogDumpFormat PmLogDumpFormat;

#define kPmLogDumpFormatDefault	((const PmLogDumpFormat*) NULL)


/*********************************************************************/
/* PmLogDumpData_ */
/**
@brief  Logs the specified binary data as text dump to the specified
		context. Specify kPmLogDumpFormatDefault for the formatting
		parameter.
		
		For efficiency, this API should not be used directly, but
		instead use the wrappers (PmLogDumpData, ...) that
		bypass the library call if the logging is not enabled.

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidContext
			kPmLogErr_InvalidLevel
			kPmLogErr_InvalidFormat
			kPmLogErr_LevelDisabled
			kPmLogErr_NoData
			kPmLogErr_InvalidData
**********************************************************************/
PmLogErr PmLogDumpData_(PmLogContext context, PmLogLevel level,
	const void* data, size_t numBytes, const PmLogDumpFormat* format);


/*********************************************************************/
/* PmLogDumpData */
/**
@brief  Logs the specified binary data as text dump to the specified
		context.  Specify kPmLogDumpFormatDefault for the formatting
		parameter.
		
proto:	PmLogErr PmLogDumpData(PmLogContext context, PmLogLevel level,
			const void* data, size_t numBytes,
			const PmLogDumpFormat* format);

@return Error code:
			kPmLogErr_None
			kPmLogErr_InvalidContext
			kPmLogErr_InvalidLevel
			kPmLogErr_InvalidFormat
			kPmLogErr_LevelDisabled
			kPmLogErr_NoData
			kPmLogErr_InvalidData
**********************************************************************/
#define	PmLogDumpData(context, level, data, numBytes, format)	\
	(PmLogIsEnabled(context, level) \
		? PmLogDumpData_(context, level, data, numBytes, format) \
		: kPmLogErr_LevelDisabled)


/*********************************************************************/
/* PmLogDumpDataError */
/**
@brief  Logs the specified binary data as text dump, tagged as error level,
		to the specified context.
		
proto:	void PmLogDumpDataError(PmLogContext context,
			const void* data, size_t numBytes,
			const PmLogDumpFormat* format);
**********************************************************************/
#define	PmLogDumpDataError(context, data, numBytes, format)	\
	(void) PmLogDumpData(context, kPmLogLevel_Error, data, numBytes, format)


/*********************************************************************/
/* PmLogDumpDataWarning */
/**
@brief  Logs the specified binary data as text dump, tagged as warning level,
		to the specified context.
		
proto:	void PmLogDumpDataWarning(PmLogContext context,
			const void* data, size_t numBytes,
			const PmLogDumpFormat* format);
**********************************************************************/
#define	PmLogDumpDataWarning(context, data, numBytes, format)	\
	(void) PmLogDumpData(context, kPmLogLevel_Warning, data, numBytes, format)


/*********************************************************************/
/* PmLogDumpDataInfo */
/**
@brief  Logs the specified binary data as text dump, tagged as info level,
		to the specified context.
		
proto:	void PmLogDumpDataInfo(PmLogContext context,
			const void* data, size_t numBytes,
			const PmLogDumpFormat* format);
**********************************************************************/
#define	PmLogDumpDataInfo(context, data, numBytes, format)	\
	(void) PmLogDumpData(context, kPmLogLevel_Info, data, numBytes, format)


/*********************************************************************/
/* PmLogDumpDataDebug */
/**
@brief  Logs the specified binary data as text dump, tagged as debug level,
		to the specified context.
		
proto:	void PmLogDumpDataDebug(PmLogContext context,
			const void* data, size_t numBytes,
			const PmLogDumpFormat* format);
**********************************************************************/
#define	PmLogDumpDataDebug(context, data, numBytes, format)	\
	(void) PmLogDumpData(context, kPmLogLevel_Debug, data, numBytes, format)


//#####################################################################


// Trace support


/*********************************************************************/
/* PMLOG_TRACES_ENABLED */
/**
	The client of this header file needs to define PMLOG_TRACES_ENABLED
	in their makefile or .c file before including the header.  Otherwise
	by default traces are disabled (i.e. not compiled).
**********************************************************************/

#ifdef PMLOG_TRACES_ENABLED

	#ifndef PMLOG_TRACE_CONTEXT
		#ifdef PMLOG_TRACE_COMPONENT
			#define PMLOG_TRACE_CONTEXT	\
				PmLogGetContextInline(PMLOG_TRACE_COMPONENT)
		#else
			#define PMLOG_TRACE_CONTEXT		kPmLogGlobalContext
		#endif
	#endif
	
	#define	PMLOG_TRACE(...)	\
		(void) PmLogPrint(PMLOG_TRACE_CONTEXT, kPmLogLevel_Debug, __VA_ARGS__)

	#define	PMLOG_TRACE_DATA(p, n)	\
		(void) PmLogDumpData(PMLOG_TRACE_CONTEXT, kPmLogLevel_Debug, p, n, \
			kPmLogDumpFormatDefault)

#else

	#define	PMLOG_TRACE(...)
	#define	PMLOG_TRACE_DATA(p, n)

#endif


//#####################################################################


/***********************************************************************
 * PmLogLevelToString
 *
 * Given a numeric level value, returning the matching symbolic string.
 * -1 (kPmLogLevel_None)      => "none"
 *  0 (kPmLogLevel_Emergency) => "emerg"
 * etc.
 * Returns NULL if the level is not valid.
 ***********************************************************************/
const char* PmLogLevelToString(PmLogLevel level);


/***********************************************************************
 * PmLogStringToLevel
 *
 * Given a symbolic level string, returning the matching numeric value.
 * "none"  => -1 (kPmLogLevel_None) 
 * "emerg" =>  0 (kPmLogLevel_Emergency)
 * etc.
 * Returns NULL if the level string is not matched.
 ***********************************************************************/
const int* PmLogStringToLevel(const char* levelStr);


//#####################################################################


/***********************************************************************
 * PmLogFacilityToString
 *
 * Given a numeric facility value, returning the matching symbolic string.
 * LOG_KERN => "kern"
 * LOG_USER => "user"
 * etc.
 * Returns NULL if the facility is not valid.
 ***********************************************************************/
const char* PmLogFacilityToString(int facility);


/***********************************************************************
 * PmLogStringToFacility
 *
 * Given a symbolic facility string, returning the matching numeric value.
 * "kern" => LOG_KERN 
 * "user" =>  LOG_USER
 * etc.
 * Returns NULL if the facility string is not matched.
 ***********************************************************************/
const int* PmLogStringToFacility(const char* facilityStr);


//#####################################################################


/***********************************************************************
 * PmLogGetErrDbgString
 *
 * Given the numeric error code value, returning a matching symbolic
 * string.  For debugging only, never to appear in user interface!
 ***********************************************************************/
const char* PmLogGetErrDbgString(PmLogErr logErr);


//#####################################################################


#ifdef __cplusplus
}
#endif	


#endif // PMLOGLIB_H
