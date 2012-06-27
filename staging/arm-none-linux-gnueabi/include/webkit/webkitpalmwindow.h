/* ============================================================
 * Date  : 2007-11-07
 * Copyright 2007 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBKITWEBOSWINDOW_H
#define WEBKITWEBOSWINDOW_H

#include <stdint.h>
#include "webkitpalmdefines.h"
#include "webkitpalmclipboard.h"

struct WebKitPalmPage;

struct WEBKIT_API WebKitPalmWindow {
public:

    WebKitPalmWindow() {}
    virtual ~WebKitPalmWindow() {}
	
	enum {
		caret_Normal,
		caret_ShiftSingle,
		caret_ShiftLock,
		caret_AltSingle,
		caret_AltLock
	};

    virtual void getVirtualWindowSize(uint32_t& width, uint32_t& height) = 0;
    virtual void getWindowSize(uint32_t& width, uint32_t& height) = 0;
    virtual const char* getUserAgent() = 0;
    virtual void resizeContents(uint32_t newWidth, uint32_t newHeight) = 0;
    virtual void zoomedContents(double scaleFactor, uint32_t newWidth, uint32_t newHeight, uint32_t newScrollOffsetX, uint32_t newScrollOffsetY) = 0;
    virtual void invalContents(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void scrollContents(uint32_t newContentsX, uint32_t newContentsY) = 0;
    virtual void pageLoadStarted() = 0;
    virtual void pageLoadStopped() = 0;
    virtual void pageLoadProgress(uint32_t progress) = 0;
	virtual void pageURIChanged(const char* uri) = 0;
	virtual void pageTitleChanged(const char* title) = 0;
	virtual void pageUrlTitleChanged(const char* uri, const char* title) = 0;
	virtual void screenSize( uint32_t& width, uint32_t& height ) = 0;
	virtual void reportError( const char* url, uint32_t errCode, const char* msg ) = 0;
	virtual void jsConsoleMessage( const char* /* inMsg */, int /* lineNo */, const char* /* inMsgSource */ ) { }
    virtual bool dialogAlert(const char* /* inMsg */) { return false; }
    virtual bool dialogConfirm(const char* /* inMsg */ ) { return false; }
    virtual bool dialogPrompt(const char* /* inMsg */, const char* /* defaultValue */, char** /* result */ ) { return false; }
    virtual bool dialogUserPassword(const char* /* inMsg */, char** /* userName */, char** /* password */) { return false; }
	virtual void linkClicked( const char* /*url*/ ) { }
	virtual void editorFocused( bool ) { }
	virtual const char* getIdentifier() { return ""; }
	
	// Mime/data handoff 
	virtual void mimeHandoffUrl( const char* /* mimeType */, const char* /* url */ ) { }
	virtual void mimeNotHandled( const char* /* mimeType */, const char* /* url */ ) { }
	// NOTE : Mime downloads come via the downloadFinished() handler.
	
	// Downloads.
	virtual void downloadStart( const char* /* url */ ) { }
	virtual void downloadProgress( const char* /* url */, unsigned long /* bytesSoFar */, unsigned long /* estimatedTotalSize */ ) { } 
	virtual void downloadError( const char* /* url */, const char* /* msg */ ) { }
	virtual void downloadFinished( const char* /* url */, const char* /* mimeType */, const char* /* tmp path name */ ) { }

    // New windows
    virtual WebKitPalmPage* createPage(int width, int height) { return 0; }
	virtual void closeWindowSoon() {}

	virtual void focus() {}
	virtual void unfocus() {}
	
	// text caret
	virtual int textCaretAppearance() { return caret_Normal; }

	// Javascript object
	virtual void jsObjectCleared() {}
	
	// status message
	virtual void statusMessage(const char* msg) {}
	
	// Dragging
	virtual void startDrag( int offset_x, int offset_y, void* dragImageRef, PalmClipboard* sysClipboard ) { }
};

#endif /* WEBKITWEBOSWINDOW_H */
