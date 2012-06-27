/* ============================================================
 * Date  : 2011-03-11
 * Copyright 2011 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBFRAMECLIENT_H
#define WEBOSWEBFRAMECLIENT_H

#include <string>

#include "palmwebframe.h"
#include "palmwebdefines.h"

namespace Palm
{

class WebPage;
class SSLValidationInfo;

class WEBKIT_API WebFrameClient
{
public:

	WebFrameClient() {}
	~WebFrameClient() {}

	virtual void urlTitleChanged(const char* uri, const char* title) = 0;

	virtual const char* getIdentifier() = 0;
	virtual bool isBusPriviledged() = 0;

	// Javascript object
	virtual void jsObjectCleared() = 0;
};

}

#endif // WEBOSWEBFRAMECLIENT_H
