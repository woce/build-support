/* ============================================================
 * Date  : 2008-11-05
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGCONTEXTIFACE_H
#define PGCONTEXTIFACE_H

#include <stdint.h>
#include <PContext.h>

#include "PGShared.h"

class PGSurface;
class PGFont;
class PGPath;

class PGContextIface : public PGShared
{
	friend class PGFont;
	friend class PGPath;
	
public:

	enum StrokeStyle {
        NoStroke,
        SolidStroke,
        DottedStroke,
        DashedStroke
    };

	PGContextIface()
		: m_pathClippingEnabled(true)
	{
#if P_BACKEND == P_BACKEND_LAG
		// Path clipping too slow.
		m_pathClippingEnabled = false;
#endif		
	}
	
	virtual ~PGContextIface() {}

	virtual PGSurface* createSurface(uint32_t width, uint32_t height,
									 bool hasAlpha = false, const void* pixelData = 0) = 0;
	virtual PGSurface* wrapBitmapData(uint32_t width, uint32_t height,
									  bool hasAlpha, const void* pixelData, uint32_t pitch = 0) = 0;
	virtual void destroySurface(PGSurface* surf) = 0;

	virtual void setDisplay(PDisplay Display = PPrimary, unsigned Layer = 1, PFormat Format = PFORMAT_8888, unsigned Buffers = 2) = 0;
	virtual void setWindow(void* NativeWindowHandle) = 0;
	virtual void setSurface(PGSurface* surf) = 0;
	virtual PGSurface* getSurface() const = 0;
	virtual void flip() = 0;
	
	virtual void setFont(PGFont* font) = 0;
	virtual PGFont* font() const = 0;
	virtual void setFallbackFont(PGFont* font) = 0;
	virtual void setFallbackFonts(PGFont** fonts, int numFonts, PFTRangeArray* ranges) = 0;

	virtual void reset() = 0;

	virtual void push() = 0;
	virtual void pop() = 0;

	virtual int originX() const = 0;
	virtual int originY() const = 0;
	
	virtual void translate(int x, int y) = 0;
    virtual void _translate(float x, float y) = 0;
    virtual void rotate(float radians) = 0;
    virtual void scale(float x, float y) = 0;
	virtual float getScale() const = 0;

	virtual void setFillColor(const PColor32& color) = 0;
	virtual void setStrokeColor(const PColor32& color) = 0;
	virtual void setStrokeThickness(float thickness) = 0;
	virtual void setFillOpacity(unsigned char opacity) = 0;
	virtual void setStrokeOpacity(unsigned char opacity) = 0;
	virtual void setStrokeStyle(const StrokeStyle style) = 0;

	virtual void drawLine(int x1, int y1, int x2, int y2) = 0;	
	virtual void drawRect(int left, int top, int right, int bottom) = 0;
	virtual void clearRect(int left, int top, int right, int bottom, PColor32 color = PColor32(0,0,0,0)) = 0;
	virtual void drawRoundRect(int left, int top, int right, int bottom, int radiusX, int radiusY) = 0;

	virtual void drawEllipse(PVertex2D center, PVertex2D radii) = 0;
	virtual void drawArc(PVertex2D center, PVertex2D radii,
                         float startAngle, float extentAngle,
						 bool closed = false) = 0;
	
	virtual void drawPolygon(int* x, int* y, unsigned count, bool closed = true, bool antialias=true) = 0;
	virtual void drawPath(PGPath* path) = 0;

	virtual void drawCharacter(unsigned short character, int x, int y) = 0;
    virtual void drawCharacters(int numChars, unsigned short* characters, float* x, float y) = 0;

    virtual void bitblt(PPixmap* src,
                        int sLeft, int sTop, int sRight, int sBottom,
                        int dLeft, int dTop, int dRight, int dBottom) = 0;
	virtual void bitblt(PGSurface* src,
						int sLeft, int sTop, int sRight, int sBottom,
						int dLeft, int dTop, int dRight, int dBottom) = 0;
	virtual void bitblt(PGSurface* src, int dLeft, int dTop, int dRight, int dBottom) = 0;

	virtual void _bitblt(PGSurface* src,
						 int sLeft, int sTop, int sRight, int sBottom,
						 int dLeft, int dTop, int dRight, int dBottom) = 0;
	
	virtual void drawPattern(PGSurface* pattern, int phaseX, int phaseY,
							 int dLeft, int dTop, int dRight, int dBottom) = 0;
	virtual void drawPattern(PGSurface* pattern, const PMatrix3D& patternMatrix,
							 int dLeft, int dTop, int dRight, int dBottom,
							 PRepeatRule repeat = PRepeat) = 0;
	
	virtual void clipRect(int left, int top, int right, int bottom) = 0;
	virtual void addClipRect(int left, int top, int right, int bottom) = 0;
    virtual void _addClipRect(float left, float top, float right, float bottom) = 0;
	virtual void clipPath(PGPath* Path) = 0;
	virtual void clearClip() = 0;

    virtual void concatMatrix(const float *Data) = 0;
    virtual void matrix(float *Data) const = 0;

	virtual bool usesEncodedImages() const { return false; }

	void setPathClippingEnabled(bool val) { m_pathClippingEnabled = val; }
	bool pathClippingEnabled() const { return m_pathClippingEnabled; }

	// FIXME: should be protected 
public:
	virtual PContext2D* pgContext() const = 0;
	
private:

	bool m_pathClippingEnabled;
};

#endif /* PGCONTEXTIFACE_H */
