/* ============================================================
 * Date  : 2008-12-31
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGIMAGEJPEGDECODER_H
#define PGIMAGEJPEGDECODER_H

#include "PGImageDecoder.h"

class PGImageJpegDecoder : public PGImageDecoder
{
public:

	PGImageJpegDecoder(const char* data, int dataLen);
	~PGImageJpegDecoder();

	virtual const char* name() const { return "JPEG"; }

	virtual bool getDimensions(int& width, int& height);
	virtual int numFrames() { return 1; }
	virtual PGImageFrame* getFrame(int frameIndex, float scale = 1.0f);

private:

	const char* m_data;
	const int m_dataLen;
	bool m_readHeader;
	int m_width;
	int m_height;
};

#endif /* PGIMAGEJPEGDECODER_H */
