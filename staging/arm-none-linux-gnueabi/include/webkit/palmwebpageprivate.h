/* ============================================================
 * Date  : 2008-09-22
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBPAGEPRIVATE_H
#define WEBOSWEBPAGEPRIVATE_H

#include "Page.h"

#if USE(V8)
	#include "npapi.h"
	#include "npfunctions.h"
	#include "v8.h"
	#include "ScriptController.h"
	#include "V8Proxy.h"
	#include "V8NPObject.h"
	#include "DOMWindow.h"
	#include "npruntime.h"
	#include "npruntime_impl.h"
#else
	#include "runtime.h"
	#include "npapi.h"
	#include "npruntime.h"
	#include "npruntime_impl.h"
#endif


namespace WebKit
{
	class ChromeClient;
	class ContextMenuClient;
	class EditorClient;
	class DragClient;
	class InspectorClient;
}

namespace WebCore
{
	class Page;
    class DeviceOrientationClientPalm;
    class DeviceMotionClientPalm;
}

namespace Palm
{

class WebView;
class WebFrame;
class WebPageClient;


class WebPagePrivate
{
public:

	WebPagePrivate(WebPage* page);
	~WebPagePrivate();

	void init(bool createRenderer=true);
	void initBrowserFuncs();

    static WebCore::Page* core(WebPage* p);
	static Palm::WebPage* kit(WebCore::Page* p);
	
	WebPage* parent;
	WebView* view;
	WebFrame* mainFrame;
	WebPageClient* client;

    WebKit::ChromeClient* chromeClient;
    WebKit::ContextMenuClient* contextMenuClient;
    WebKit::EditorClient* editorClient;
	WebKit::DragClient* dragClient;
	WebKit::InspectorClient* inspectorClient;
    WebCore::DeviceOrientationClientPalm* deviceOrientationClient;
    WebCore::DeviceMotionClientPalm* deviceMotionClient;
    WebCore::Page* page;

	NPNetscapeFuncs browserFuncs;
	bool m_logOnNextPaint;
};

}

WebCore::Page* core(Palm::WebPage* p);
Palm::WebPage* kit(WebCore::Page* p);

#endif /* WEBOSWEBPAGEPRIVATE_H */
