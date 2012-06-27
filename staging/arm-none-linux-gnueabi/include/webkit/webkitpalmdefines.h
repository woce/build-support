

#ifndef WEBKIT_WEBOS_DEFINES_H
#define WEBKIT_WEBOS_DEFINES_H

// This causes symbols to be exported from the shared library
#ifdef G_OS_WIN32
    #ifdef BUILDING_WEBKIT
        #define WEBKIT_API __declspec(dllexport)
    #else
        #define WEBKIT_API __declspec(dllimport)
    #endif
#else
    #define WEBKIT_API __attribute__((visibility("default")))
#endif


#endif
