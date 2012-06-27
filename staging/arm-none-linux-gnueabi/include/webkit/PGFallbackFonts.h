
#ifndef __CJKVUtil_h__
#define __CJKVUtil_h__

#include "PGContext.h"
#include "PGShared.h"

#define  kMaxFallbackFonts  8


	
class PGEXPORT PGFallbackFonts
{
public:
	PGFallbackFonts();
	~PGFallbackFonts();
	
	PGContextIface* sharedFontMeasuringContext() { return m_emptyContext; }
	bool setFallbackFontsIntoContext( PGContextIface* c );
	
	static void setThreadSpecificInstance(PGFallbackFonts* i ); 
	static PGFallbackFonts* threadSpecificInstance();
	
private:
	bool init();
	
	int m_numFonts;
	PGFont* m_CjkFonts[kMaxFallbackFonts];
	PFTRangeArray m_ranges;
	
	PGContextIface* m_emptyContext;
};


#endif

