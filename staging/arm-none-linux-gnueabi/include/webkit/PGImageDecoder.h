/* ============================================================
 * Date  : 2008-12-31
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGIMAGEDECODER_H
#define PGIMAGEDECODER_H

#include <stdint.h>

class PGImageFrame;

class PGImageDecoder
{
public:

	PGImageDecoder(const char* data, int dataLen) : m_failed(false) {}
	virtual ~PGImageDecoder() {}

	virtual const char* name() const = 0;

	virtual bool getDimensions(int& width, int& height) = 0;
	virtual int numFrames() = 0;
	virtual PGImageFrame* getFrame(int frameIndex, float scale = 1.0f) = 0;
	virtual bool failed() const { return m_failed; }

protected:

	bool m_failed;
};

#endif /* PGIMAGEDECODER_H */
