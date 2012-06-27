/* ============================================================
 * Date  : 2008-09-22
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBDEFINES_H
#define WEBOSWEBDEFINES_H

#include <glib.h>

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

#endif /* WEBOSWEBDEFINES_H */
