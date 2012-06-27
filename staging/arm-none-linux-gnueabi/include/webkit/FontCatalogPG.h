
// Copyright 2008 Palm Inc.

#ifndef __FontCatalog_h__
#define __FontCatalog_h__

#include "PlatformString.h"

#include <list>

// Freetype (for polygon routines, *not* fonts.)
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftbitmap.h>
#include <freetype/ftoutln.h>


namespace WebCore
{
	
struct FontCatalogEntry;

// Font catalog matches based on font attributes in the file, *not* the file name.
// Think of it as a sort of fontconfig-lite.

class FontCatalog
{
	public:
		static FontCatalog* instance(const char* defaultFamily = 0 );
		
		enum {
			bold = 1, 
			italic = 2, 
			oblique = 4,	// this is a variant of italic ...
			condensed = 8,
			monospace = 16
		};
		
		
		// name is the font name from the file -- NOT a file name/path
		// family is same as FontDescription::enums 
		// flags are the enum above.
		String select( const String& name, int family, int flags );
		
	private:
		FontCatalog( const char* defaultFamily );
		FontCatalog( );
		~FontCatalog( );
		
		void scan( );
		void clear( );
		void dump( );
		
		String m_genericSerifName;
		String m_genericSansSerifName;
		String m_genericMonospaceName;
		String m_defaultFontPath;
		String m_defaultFamily;
		
		FT_Library m_ftlib;
		
		typedef std::list<FontCatalogEntry*> FontContainerType;
		FontContainerType m_fonts;

		FontCatalog& operator=( const FontCatalog& );
		FontCatalog( const FontCatalog& );
};

}

#endif

