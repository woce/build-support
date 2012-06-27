/* ============================================================
 * Date  : 2008-09-22
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBPAGECLIENT_H
#define WEBOSWEBPAGECLIENT_H

#include <string>

#include "palmwebpage.h"
#include "palmwebframeclient.h"
#include "palmwebdefines.h"
#include "palmwebtypes.h"

namespace Palm
{

class WebPage;
class SSLValidationInfo;

class WEBKIT_API WebPageClient : public WebFrameClient
{
public:

	WebPageClient() {}
	~WebPageClient() {}

    virtual const char* getUserAgent() = 0;
    virtual void loadStarted() = 0;
    virtual void loadStopped() = 0;
    virtual void loadProgress(int progress) = 0;
    // Let the client know we are still active so the process isn't killed.
    virtual void loadActive() {;}
    virtual void setDeadlockDetectionInterval(const int IntervalInSeconds) {;}
    virtual void suspendDeadlockDetection() {;}
    virtual void resumeDeadlockDetection() {;}
	virtual void didFinishDocumentLoad() = 0;
	virtual void reportError(const char* url, int errCode, const char* msg) = 0;
	virtual void jsConsoleMessage(const char* inMsg, int lineNo, const char* inMsgSource) = 0;
	virtual void jsConsoleMessage(MessageLevel level, const char* inMsg, int lineNo, const char* inMsgSource);

	// JS dialogs
    virtual bool dialogAlert(const char* inMsg) = 0;
    virtual bool dialogConfirm(const char* inMsg) = 0;
    virtual bool dialogPrompt(const char* inMsg, const char* defaultValue, std::string& result) = 0;
    virtual bool dialogUserPassword(const char* inMsg, std::string& userName, std::string& password) = 0;
	virtual bool dialogSSLConfirm(Palm::SSLValidationInfo& sslInfo) = 0;
	
	// Mime/data handoff 
	/// WebKit either can't or won't by policy handle this mime type.
	/// @remarks Only mimeNotHandled or mimeNotHandled are called - never both.
	virtual void mimeHandoffUrl(const char* mimeType, const char* url) = 0;
	
	/// WebKit cannot handle this mime type.
	/// @remarks Only mimeNotHandled or mimeNotHandled are called - never both.
	virtual void mimeNotHandled(const char* mimeType, const char* url) = 0;

	/// Give the client a chance to intercept the navigation to a url.
	/// @param url The URL to which the page is navigating.
	/// @param isInitialOpen Is the navigation a result of calling openUrl, or is it something like a link click?
	/// @return true if the navigation was intercepted (whereby WebKit will not load the page) or 
	///         false to indicate the at the navigation was *not* intercepted and WebKit will load the page.
	virtual bool interceptPageNavigation(const char* url, bool isInitialOpen) = 0;

	/// @return true to have WebKit display standalone images (where the image is the main URL) in the main frame.
	virtual bool displayStandaloneImages() const = 0;

	/// @return true if WebKit should handle the URL scheme, false to handoff to host via mimeNotHandled.
	virtual bool shouldHandleScheme(const char* scheme) const = 0;
	
	// Downloads.
	virtual void downloadStart(const char* url) = 0;
	virtual void downloadProgress(const char* url, unsigned long bytesSoFar, unsigned long estimatedTotalSize) = 0;
	virtual void downloadError(const char* url, const char* msg) = 0;
	virtual void downloadFinished(const char* url, const char* mimeType, const char* tmpPathName) = 0;

    // New windows
	virtual WebPage* createPage(int width, int height, const char* name, const char* attributes) = 0;
	virtual void closePageSoon() = 0;

	// status message
	virtual void statusMessage(const char* msg) = 0;
	virtual void updateGlobalHistory(const char* url, bool reload) = 0;
	virtual void dispatchFailedLoad(const char* domain, int errorCode,
			const char* failingURL, const char* localizedDescription) = 0;
	virtual void setMainDocumentError(const char* domain, int errorCode,
			const char* failingURL, const char* localizedDescription) = 0;

	virtual bool requestGeolocationPermissionForDomain(const char* domain);

    virtual void frameCreated(Palm::WebFrame* frame) {}
    virtual void frameDestroyed(Palm::WebFrame* frame) {}

    virtual void needSensorEvent(Palm::SensorType type, bool enable) {}
};

}

#endif // WEBOSWEBPAGECLIENT_H
