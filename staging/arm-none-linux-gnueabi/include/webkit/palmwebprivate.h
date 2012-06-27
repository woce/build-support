/* ============================================================
 * Date  : 2008-10-25
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBPRIVATE_H
#define WEBOSWEBPRIVATE_H

#include <palmwebglobal.h>

extern "C" {
void _malloc_thread_cleanup(void) __attribute__ ((weak));
}

namespace Palm
{
namespace
{

static gboolean threadCleanupIdleCallback(gpointer)
{
	Palm::WebGlobal::garbageCollectNow();
	return FALSE;
}

void threadCleanup()
{
	GSource* src = g_idle_source_new();
	g_source_set_callback(src, threadCleanupIdleCallback, NULL, NULL);
	g_source_attach(src, g_main_loop_get_context(WebGlobal::mainLoop()));
	g_source_unref(src);

	if (_malloc_thread_cleanup)
		_malloc_thread_cleanup();
}

}
}

#endif /* WEBOSWEBPRIVATE_H */
