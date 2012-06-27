/* ============================================================
 * Date  : 2008-11-09
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef PGTHREADGLOBALCONTEXT_H
#define PGTHREADGLOBALCONTEXT_H

#include "PGShared.h"

class PGFallbackFonts;
class PGContextIface;

class PGEXPORT PGThreadGlobalContext : public PGShared
{
public:

	static PGThreadGlobalContext* instance();

	PGContextIface* graphicsContext();
	void setGraphicsContext(PGContextIface* iface);

private:

	PGContextIface* m_gc;

	PGFallbackFonts* m_fallbackFonts;
	
private:

	PGThreadGlobalContext();
	~PGThreadGlobalContext();
};

#endif /* PGTHREADGLOBALCONTEXT_H */
