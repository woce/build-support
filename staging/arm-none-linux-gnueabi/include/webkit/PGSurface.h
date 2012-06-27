/* ============================================================
 * Date  : 2008-08-07
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGSURFACE_H
#define PGSURFACE_H

#include <stdint.h>
#include <stdio.h>

#include <map>

#include <PPixmap.h>

#include "PGShared.h"

class PGContextIface;

typedef void (*StreamWriteFunction)( unsigned char* data, int length, void* user ); 

class PGEXPORT PGSurface : public PGShared
{
public:

	enum Attributes {
		ATTR_ENCODED = 1 << 0,
		ATTR_SHM     = 1 << 1,
		ATTR_DISK    = 1 << 2
	};

	static PGSurface* createFromJPEGFile(const char* filePath);
	static PGSurface* createFromPNGFile(const char* filePath);
	static PGSurface* createFromPNGStream(const unsigned char* data);
	static PGSurface* create(uint32_t width, uint32_t height, bool hasAlpha = false, const unsigned char* pixelData = 0);
	static PGSurface* wrap(uint32_t width, uint32_t height, const unsigned char* pixelData, bool hasAlpha = false);

	uint32_t width() const { return m_width; }
	uint32_t height() const { return m_height; }
	uint32_t bpp() const { return 32; }
	uint32_t rowbytes() const { return m_width * 4; }
	uint8_t* raster() const { return m_raster; }
	bool hasAlpha() const { return m_hasAlpha; }
	uint8_t* scanline(uint32_t line) const { return m_raster + line * m_width * 4; }

	void setHasAlpha(bool enable);

	bool writePNGToStream( StreamWriteFunction func, void* user );
	bool writePNG(const char* filePath);
    uint32_t writeJPGToStream(void *out, int quality=95 );
    bool writeJPG(const char* filePath, int quality=95 );

    bool openJPG(FILE* fp, int width, int height, struct jpeg_compress_struct* jpgInfo, struct jpeg_error_mgr* jerr, int quality=95);
    int appendToJPG(struct jpeg_compress_struct* jpgInfo, int height=-1);
    int appendWhiteToJPG(struct jpeg_compress_struct* jpgInfo);
    bool closeJPG(struct jpeg_compress_struct* jpgInfo);

	virtual PGSurface* subSurface(PRect rect) const;

	virtual PGSurface* scale(uint32_t width, uint32_t height) const;

	void desaturate();

	void setQuality(PSampling quality);

	uint32_t attributes() const { return m_attributes; }

	PPixmap* pgPixmap() const { return m_pixmap; }
	
protected:

	PGSurface();
	virtual ~PGSurface();

	PGContextIface* m_context;
	uint8_t* m_raster;
	uint32_t m_width;
	uint32_t m_height;
	bool     m_hasAlpha;
	uint32_t m_attributes;
	bool     m_ownData;

	PPixmap* m_pixmap;

	typedef std::pair<int,int> PointPair;
	typedef std::map<PointPair, PGSurface*> PointPairSurfaceMap;
	mutable PointPairSurfaceMap m_subSurfaces;

private:

	// Non-copyable
	PGSurface(const PGSurface&);
	PGSurface& operator=(const PGSurface&);

	friend class PGContext;
};

#endif /* PGSURFACE_H */
