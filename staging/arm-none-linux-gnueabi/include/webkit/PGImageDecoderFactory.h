/* ============================================================
 * Date  : 2009-01-02
 * Copyright 2009 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGIMAGEDECODERFACTORY_H
#define PGIMAGEDECODERFACTORY_H

class PGImageDecoder;

class PGImageDecoderFactory
{
public:

	static PGImageDecoder* decoderForData(const char* data, const int dataLen);
	static int maxImageSize();
};

#endif /* PGIMAGEDECODERFACTORY_H */
