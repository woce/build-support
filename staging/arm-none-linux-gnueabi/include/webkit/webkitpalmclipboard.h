
#ifndef __webkitpalmclipboard_h__
#define __webkitpalmclipboard_h__

#include <glib.h>
#include "webkitpalmdefines.h"

#ifdef __cplusplus
extern "C" {
#endif


// Clipboard (should be moved to own header)

typedef struct PalmClipboard PalmClipboard;

WEBKIT_API PalmClipboard*		palm_clipboard_create();
WEBKIT_API void					palm_clipboard_destroy(PalmClipboard*);
WEBKIT_API void 				palm_clipboard_set( PalmClipboard* cp, const char* type, const char* value );
WEBKIT_API int					palm_clipboard_get( PalmClipboard* cp, const char* type, const char** outValue );
WEBKIT_API void					palm_clipboard_clear( PalmClipboard* cp );

#ifdef __cplusplus
}
#endif

#endif


