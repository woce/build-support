/* ============================================================
 * Date  : 2008-08-08
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGFONT_H
#define PGFONT_H

#include <PFont.h>

#include "PGShared.h"

class PGContext;
class PGContextIface;

class PGEXPORT PGFont : public PGShared
{
public:

	static PGFont* createFromFile(const char* filePath, int size, int faceIndex=0);

	void setPointSize(int size, bool changeOriginalPointSize = false);
	int pointSize() const;
	int originalPointSize() const;
	const char* fileName() const { return m_fileName; }
	void setClampWidth(bool val) { m_clampWidth = val; }
	
	int	ascent() const;
	int	descent() const;
	int	height() const;
	int	xheight() const;
	int	spacewidth() const;
	int	lineheight( ) const;
	bool isFixedPitch() const;

	PValue width(unsigned short c, PGContextIface* measuringContext=0);
	bool containsGlyphForCharCode( unsigned short inCharCode );

	bool operator==(const PGFont& other) const;

private:

	PGFont();
	~PGFont();

private:

	PFont* m_font;
	int m_origPtSize;
	int m_ptSize;
	int m_ascent;
	int m_descent;
	int m_height;
	int m_xHeight;
	int m_spaceWidth;
	int m_lineHeight;
	bool m_fixedPitch;
	char* m_fileName;
	bool m_clampWidth;

	friend class PGContext;

private:
	
	PGFont(const PGFont&);
	PGFont& operator=(const PGFont&);
};

#endif /* PGFONT_H */
