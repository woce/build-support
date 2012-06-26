
/* NOTE : this is a hand-made config.h for building c-json */

#ifndef __config_h__
#define __config_h__


#define STDC_HEADERS 1
#define HAVE_STRINGS_H 1
#define HAVE_STRNCASECMP 1
#define HAVE_UNISTD_H 1
#define HAVE_SYS_STAT 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_FCNTL_H 1
#define HAVE_STDARG_H 1
#define HAVE_VSNPRINTF 1
#if defined(__CYGWIN__)
#define HAVE_VASPRINTF 1
#endif

#endif
