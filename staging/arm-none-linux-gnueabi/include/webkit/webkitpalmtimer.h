/* ============================================================
 * Date  : 2008-02-22
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBKITWEBOSTIMER_H
#define WEBKITWEBOSTIMER_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <webkitpalmdefines.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WebKitPalmTimer WebKitPalmTimer;
typedef void  (*WebKitPalmTimerCallback)(void* userArg);

WEBKIT_API WebKitPalmTimer* webkit_timer_new(WebKitPalmTimerCallback cb, void* userArg);
WEBKIT_API void             webkit_timer_fire(WebKitPalmTimer* timer, uint64_t timeInMs);
WEBKIT_API void             webkit_timer_delete(WebKitPalmTimer* timer);
WEBKIT_API void             webkit_timer_freeze();
WEBKIT_API void             webkit_timer_thaw();

#ifdef __cplusplus
}
#endif

#endif /* WEBKITWEBOSTIMER_H */
