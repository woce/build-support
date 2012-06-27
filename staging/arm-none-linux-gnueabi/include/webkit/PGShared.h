/* ============================================================
 * Date  : 2008-08-07
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGSHARED_H
#define PGSHARED_H

#include <glib.h>

#ifdef G_OS_WIN32
	#ifdef BUILDING_WEBKIT
		#define PGEXPORT __declspec(dllexport)
	#else
		#define PGEXPORT __declspec(dllimport)
	#endif
#else
#define PGEXPORT __attribute__((visibility("default")))
#endif

class PGEXPORT PGShared
{
public:

	PGShared() : m_refCount(1) {}
	
	void addRef() {
		m_refCount++;
	}
	
	void releaseRef() {
		m_refCount--;
		if (!m_refCount)
			delete this;
	}
	
	int refCount() const {
		return m_refCount;
	}

private:

	int m_refCount;

protected:

	virtual ~PGShared() {}
};

#endif /* PGSHARED_H */
