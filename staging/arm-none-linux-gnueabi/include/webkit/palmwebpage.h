/* ============================================================
 * Date  : 2008-09-21
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBPAGE_H
#define WEBOSWEBPAGE_H

#include <string>
#include <vector>

#include "palmwebdefines.h"

namespace Palm
{

// This must be kept identical to the enum in Chrome.h
enum MessageLevel {
    TipMessageLevel,
    LogMessageLevel,
    WarningMessageLevel,
    ErrorMessageLevel
};


class WebView;
class WebFrame;
class WebPageClient;
class WebPagePrivate;

struct WEBKIT_API WebPageStatistics
{
	unsigned long numImages;
	unsigned long totalImagesBytes;

	unsigned long numRenderTreeNodes;
	unsigned long numRenderLayers;
	
	unsigned long numDOMNodes;

	unsigned long numOutstandingServiceRequests;
};

class WEBKIT_API WebPage
{
public:

	// Page without a view
	WebPage();
	// Page with a view
	WebPage(WebView* view);
	~WebPage();

	void setClient(WebPageClient* client);
	WebPageClient* client() const;

	WebView* view() const;

	WebFrame* mainFrame() const;

	void load(const char* url);
	void stopLoading();
	void reload();
	void loadString(const char* content, const char* contentMimeType,
					const char* contentEncoding, const char* baseUrl);
	void loadHtmlString(const char* content, const char* baseUrl);

	bool canGoBackward();
	bool canGoForward();
	void goBackward();
	void goForward();
	void clearBackForwardList();

	std::string getContents(bool markedUp);
	
	void inspect();
	void inspectRemote(bool enable);
	void closeInspector();

    // Throttles the rate of timer callbacks for this webpage.
    // If throttleLevelFrom0To100Percent is 100%, then minThrottleMS is ignored.
    // Otherwise, time callback intervals will be multiplied by a factor of
    // 100.0 / throttleLevelFrom0To100Percent, and subject to a minimum of
    // minThrottleMS milliseconds.
    //
    // If throttleLevelFrom0To100Percent is 0%, then the timers will be suspended.
    // If suspension is not possible, then the webpage to throttle the timers to
    // 1% as an approximation i.e. intervals takes 100 times longer.
    void throttle(unsigned int throttleLevelFrom0To100Percent, unsigned int minThrottleMS);

	bool evaluateScript(const char* script);

	void cancelDownload(const char* url);

	bool createJsObject(void* objClass, const char* name, void** obj, void** browserFuncs);
	
	bool getStatistics( WebPageStatistics& outStats );

	void notifyTextEntryAutoCorrect();

	void setPrivateBrowsingEnabled(bool enabled);
	
	void setJavaScriptCanOpenWindowsAutomatically(bool enabled);
	
	void setJavaScriptEnabled(bool enabled);
	
	void setPluginsEnabled(bool enabled);
	
	void setEnhancedViewportEnabled(bool enabled);

	void setIgnoreMetaRefreshTags(bool ignore);

	int outstandingDatabaseTasks();
	
	void enableHttpProxy(const char* host, const int port);
	void disableHttpProxy();
	
	void forceNetworkInterface(const char* interfaceName);

	void logOnNextPaint();

	double getPageScaleFactor() const;

    void forceDNSServers(const char* dnsServers);

private:

	WebPagePrivate* d;

	friend class WebFrame;
	friend class WebView;
	friend class WebPagePrivate;
	
private:

	WebPage(const WebPage&);
	WebPage& operator=(const WebPage&);
};

}

#endif /* WEBOSWEBPAGE_H */
