/* ============================================================
 * Date  : 2008-09-22
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBFRAMEPRIVATE_H
#define WEBOSWEBFRAMEPRIVATE_H

#include "KURL.h"
#include "PlatformString.h"

namespace WebCore
{
class Frame;
class HTMLFrameOwnerElement;
}

namespace WebKit
{
class FrameLoaderClient;
}

namespace Palm
{

class WebFrame;
class WebPage;
class WebFrameClient;

class WebFrameData
{
public:

    WebCore::HTMLFrameOwnerElement* ownerElement;

	// FIXME: Do we need these?
	WebCore::KURL url;
    WTF::String name;
};
	

class WebFramePrivate
{
public:

    static WebCore::Frame* core(WebFrame* f);
	static WebFrame* kit(WebCore::Frame*);

	WebFrame* parentFrame;
	WebPage* palmPage;
	WebFrameClient* client;

	WebCore::Frame* frame;
	WebKit::FrameLoaderClient* frameLoaderClient;
};

}

// Outside the namespace
WebCore::Frame* core(Palm::WebFrame* f);
Palm::WebFrame* kit(WebCore::Frame* f);

#endif /* WEBOSWEBFRAMEPRIVATE_H */
