/* ============================================================
 * Date  : 2008-12-31
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGIMAGEFRAME_H
#define PGIMAGEFRAME_H

#include <stdlib.h>
#include "PGSurface.h"
#include "PGContext.h"

class PGImageFrame
{
public:

	PGImageFrame(int width, int height) {
		m_width = width;
		m_height = height;
		m_hasAlpha = false;
		m_data = (width > 0 && height > 0) ? (unsigned int*) malloc(width * height * 4) : 0;
		m_surf = 0;
		m_requestedScale = m_scale = 1.0f;
	}

	~PGImageFrame() {
		free(m_data);
		if (m_surf)
			m_surf->releaseRef();
	}

	void setHasAlpha(bool val) { m_hasAlpha = val; }
	void setScale(float requestedScale, float actualScale)
	{
		m_requestedScale = requestedScale;
		m_scale = actualScale;
	}
	
	int width() const { return m_width; }
	int height() const { return m_height; }
	bool hasAlpha() const { return m_hasAlpha; }
	unsigned int* data() const { return m_data; }
	float requestedScale() const { return m_requestedScale; }

	void mapRect(PVertex2D& TopLeft, PVertex2D& BottomRight)
	{
		if (m_scale != 1.0f) {
			PValue scale(m_scale);
			TopLeft.X *= scale;
			TopLeft.Y *= scale;
			BottomRight.X *= scale;
			BottomRight.Y *= scale;
		}
	}

	PGSurface* surface() {

		if (m_surf)
			return m_surf;

		if (!m_data)
			return 0;

		m_surf = PGSurface::wrap((const unsigned int) m_width,
								 (const unsigned int) m_height,
								 (const unsigned char*) m_data,
								 m_hasAlpha);
		return m_surf;
	}

	PGImageFrame* downSample(float requestedScale) 
	{
		float actualScale = requestedScale;
		
		int width = (int)(m_width * requestedScale);
		int height = (int)(m_height * requestedScale);
		
		if (width == 0 || height == 0) {
			actualScale = 1.0f;
			width = m_width;
			height = m_height;
		}

		PGImageFrame* resized = new PGImageFrame(width, height);
		resized->setScale(requestedScale, actualScale);
		resized->setHasAlpha(this->hasAlpha());
		
		PGContext::downSample(resized->surface(), this->surface());
		return resized;
	}

private:

	int m_width;
	int m_height;
	bool m_hasAlpha;
	unsigned int* m_data;
	PGSurface* m_surf;
	float m_requestedScale;
	float m_scale;

private:

	PGImageFrame(const PGImageFrame&);
	PGImageFrame& operator=(const PGImageFrame&);
};

#endif /* PGIMAGEFRAME_H */
