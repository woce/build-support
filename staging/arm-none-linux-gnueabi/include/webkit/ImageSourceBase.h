/* ============================================================
 * Date  : 2009-01-02
 * Copyright 2009 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef IMAGESOURCETYPE_H
#define IMAGESOURCETYPE_H

#include "IntSize.h"
#include "ImageSource.h"
#include "PlatformString.h"

class PGSurface;

namespace WebCore
{

class SharedBuffer;

class ImageSourceBase
{
public:

	ImageSourceBase() {}
	virtual ~ImageSourceBase() {}

	virtual void clear() = 0;
	virtual bool initialized() const  = 0;
	virtual void setData(SharedBuffer* data, bool allDataReceived) = 0;
	virtual bool isSizeAvailable() = 0;
	virtual IntSize size() const = 0;
	virtual int repetitionCount() = 0;
	virtual size_t frameCount() const = 0;
	virtual PGSurface* createFrameAtIndex(size_t index) = 0;
	virtual float frameDurationAtIndex(size_t index) = 0;
	virtual bool frameHasAlphaAtIndex(size_t index) = 0;
	virtual bool frameIsCompleteAtIndex(size_t index) = 0;
	virtual String filenameExtension() const = 0;
};

}

#endif /* IMAGESOURCETYPE_H */
