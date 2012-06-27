/* ============================================================
 * Date	 : 2008-12-31
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGPATH_H
#define PGPATH_H

#include <stdint.h>
#include <PPath.h>
#include <PMatrix3D.h>
#include "PGShared.h"
#include "FloatPoint.h"
#include "FloatRect.h"
#include "TransformationMatrix.h"
#include "AffineTransform.h"

struct PGPathElement
{
	enum ElementType
	{
    ArcTo,
	MoveTo,
	LineTo,
	BezierTo,
	Close,
	};
	ElementType Type;
	int		PointIndex;

	PGPathElement(ElementType _Type, int _PointIndex) 
	: Type(_Type),
	  PointIndex(_PointIndex)
	{
	}

};

struct PGPathData
{
	PGPathElement* Element;
	int		   MaxElements;
	int		   NumElements;
	
	PVertex2D*	   Point;
	int		   MaxPoints;
	int		   NumPoints;

	// Not used.  Don't think Record/Playback needs the transform.
	//PMatrix3D	   Transform;
};

	
class PGEXPORT PGPath
{
public:

	PGPath();
	~PGPath();
	
	// Must be copiable
	PGPath(const PGPath&);
	PGPath& operator=(const PGPath&);
	
	PPath*		pgPath() const { return m_path; }
	PGPathData* pgPathData() const { return m_data; }
	
	bool isEmpty() const;
	
	void clear();
	void moveTo(const WebCore::FloatPoint&);
	void lineTo(const WebCore::FloatPoint&);
	void bezierTo(const WebCore::FloatPoint& controlPoint1, const WebCore::FloatPoint& controlPoint2, const WebCore::FloatPoint&);
	void arcTo( const WebCore::FloatPoint& end, const WebCore::FloatPoint& center, const float radius, const bool ccw);
	void close();
	void transform(const WebCore::TransformationMatrix&);
	void transform(const WebCore::AffineTransform&);

    WebCore::FloatRect boundingRect() const;
	WebCore::FloatPoint currentPosition();
    
	void loadPathData(PGPathData* PathData);

	void enableRectHitDetect(bool Enable, const WebCore::FloatRect* Rect = NULL);
	bool isRectHitDetectEnabled(WebCore::FloatRect* Rect = NULL);
	
protected:

	PPath*		m_path;
	PMatrix3D	m_transform;
	PGPathData*	m_data;
	bool		m_dataAllocated;

	// For rectangle hit detection
	bool                 m_rectOnly;
	WebCore::FloatRect   m_floatRect;
	
	int	 addElement(const PGPathElement& Element);
	int	 addPoint(const PVertex2D& Point);
	
private:
	
	void allocPathData(int MaxElements = 10, int MaxPoints = 20, PPath* Path = NULL);
	void freePathData();
	void copyPathData(const PGPath&);
    
	friend class PGContext;
};

#endif /* PGPATH_H */
