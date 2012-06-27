/* ============================================================
 * Date  : 2008-08-07
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGCONTEXT_H
#define PGCONTEXT_H

#include <stdint.h>
#include <PContext.h>

#include "PGShared.h"
#include "PGContextIface.h"

class PGSurface;
class PGFont;
struct PGContextState;

class PGEXPORT PGContext : public PGContextIface
{
public:

	static PGContext* create();
	static void downSample(PGSurface* dst, PGSurface* src);
	
	PGSurface* createSurface(uint32_t width, uint32_t height,
							 bool hasAlpha = false, const void* pixelData = 0);
	PGSurface* wrapBitmapData(uint32_t width, uint32_t height,
							  bool hasAlpha, const void* pixelData, uint32_t pitch = 0);
	void destroySurface(PGSurface* surf);


	void setDisplay(PDisplay Display = PPrimary, unsigned Layer = 1, PFormat Format = PFORMAT_8888, unsigned Buffers = 2);
	void setWindow(void* NativeWindowHandle);
	void setSurface(PGSurface* surf);
	PGSurface* getSurface() const;
	void flip();
	
	void setFont(PGFont* font);
	PGFont* font() const;
	void setFallbackFont(PGFont* font);
	void setFallbackFonts(PGFont** fonts, int numFonts, PFTRangeArray* ranges);

	// clears out the gfx stack
	void reset();

	void push();
	void pop();

	int originX() const;
	int originY() const;

	void translate(int x, int y);
    void _translate(float x, float y);
    void rotate(float radians);
    void scale(float x, float y);

    void setCapRule(PCapRule rule);
    void setJoinRule(PJoinRule rule);
    void setMiterLimit(PValue limit);
	void setFillColor(const PColor32& color);
	void setStrokeColor(const PColor32& color);
	void setStrokeThickness(float thickness);
	void setFillOpacity(unsigned char opacity);
	void setStrokeOpacity(unsigned char opacity);
	void setStrokeStyle(const StrokeStyle style);
	void setCompositeOperation(const PCompRule op);

	void drawLine(int x1, int y1, int x2, int y2);
	void drawRect(int left, int top, int right, int bottom);
	void clearRect(int left, int top, int right, int bottom, PColor32 color = PColor32(0,0,0,0));	
	void drawRoundRect(int left, int top, int right, int bottom, int radiusX, int radiusY);
	void drawEllipse(PVertex2D center, PVertex2D radii);

	void drawArc(PVertex2D center, PVertex2D radii,
                 float startAngle, float extentAngle,
				 bool closed = false);

	void drawPolygon(int* x, int* y, unsigned count, bool closed = true, bool antialias=true);

	void drawCharacter(unsigned short character, int x, int y);
    void drawCharacters(int numChars, unsigned short* characters, float* x, float y);
	void drawPath(PGPath* path);
	
    void bitblt(PPixmap* src,
                int sLeft, int sTop, int sRight, int sBottom,
                int dLeft, int dTop, int dRight, int dBottom);
	void bitblt(PGSurface* src,
				int sLeft, int sTop, int sRight, int sBottom,
				int dLeft, int dTop, int dRight, int dBottom);
	void bitblt(PGSurface* src, PVertex2D SrcStart, PVertex2D SrcEnd, PVertex2D DstStart, PVertex2D DstEnd);

	void bitblt(PGSurface* src, int dLeft, int dTop, int dRight, int dBottom);

	void _bitblt(PGSurface* src,
				 int sLeft, int sTop, int sRight, int sBottom,
				 int dLeft, int dTop, int dRight, int dBottom);

	void drawPattern(PGSurface* pattern, int phaseX, int phaseY,
					 int dLeft, int dTop, int dRight, int dBottom);

	void drawPattern(PGSurface* pattern, const PMatrix3D& patternMatrix,
					 int dLeft, int dTop, int dRight, int dBottom,
					 PRepeatRule repeat = PRepeat);
	
	void clipRect(int left, int top, int right, int bottom);
	void addClipRect(int left, int top, int right, int bottom);
    void _addClipRect(float left, float top, float right, float bottom);
	void clipPath(PGPath* Path);    
	void clearClip();
	PRect getClipRect() const;
	float getScale() const;
	
	void setGlobalClipRect(int left, int top, int right, int bottom);

	void setFgColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF);
	void drawTextA(const char* str, int len, int x, int y, const PGFont* font);

    void concatMatrix(const float *Data);
    void matrix(float *Data) const;
    PMatrix3D matrix() const;


    int offsetX() const { return m_offset_x; }
    int offsetY() const { return m_offset_y; }
    void setOffsetX(const int offset) { m_offset_x = offset; }
    void setOffsetY(const int offset) { m_offset_y = offset; }

	// FIXME: should be protected 
public:
	PContext2D* pgContext() const { return m_gc; }
	
private:
	
	PGContext(PContext2D* gc);
	~PGContext();

	PGContextState* currState() const;

	void applyState();
	
private:

	PContext2D* m_gc;

	PGContextState* m_stateStack;	
	int m_currState;
	int m_stateTrampoline;


	PGSurface* m_surf;
	PGFont* m_font;

	bool m_stateChanged;

    int m_offset_x;
    int m_offset_y;

private:

	// Non-Copyable
	PGContext(const PGContext&);
	PGContext& operator=(const PGContext&);	
};

#endif /* PGCONTEXT_H */
