/* ============================================================
 * Date  : 2009-01-06
 * Copyright 2009 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGIMAGEGIFDECODER_H
#define PGIMAGEGIFDECODER_H

#include <gif_lib.h>

#include "PGImageDecoder.h"

class PGImageGifDecoder : public PGImageDecoder
{
public:

	PGImageGifDecoder(const char* data, int dataLen);
	~PGImageGifDecoder();

	virtual const char* name() const { return "GIF"; }
	
	virtual bool getDimensions(int& width, int& height);
	virtual int numFrames();
	virtual PGImageFrame* getFrame(int frameIndex, float scale = 1.0f);

private:

	static int gifInputFunc(GifFileType*, GifByteType*, int);

private:

	void readHeader();

	const char* m_data;
	const int m_dataLen;
	int m_dataReadPos;
	
	bool m_readHeader;
	int m_width;
	int m_height;
	int m_numFrames;
	
};
	

#endif /* PGIMAGEGIFDECODER_H */
