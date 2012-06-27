/* ============================================================
 * Date  : 2009-01-13
 * Copyright 2009 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGIMAGEPNGDECODER_H
#define PGIMAGEPNGDECODER_H

#include "PGImageDecoder.h"

class PGImagePngDecoder : public PGImageDecoder
{
public:

	PGImagePngDecoder(const char* data, int dataLen);
	~PGImagePngDecoder();

	virtual const char* name() const { return "PNG"; }
	
	virtual bool getDimensions(int& width, int& height);
	virtual int numFrames() { return 1; }
	virtual PGImageFrame* getFrame(int frameIndex, float scale = 1.0f);

private:

	const char* m_data;
	const int m_dataLen;
	bool m_readHeader;	
	int m_width;
	int m_height;
	bool m_hasAlpha;
};
	

#endif /* PGIMAGEPNGDECODER_H */
