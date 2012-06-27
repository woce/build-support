
/* Piranha gfx wrapper */

#ifndef FontPlatformData_h
#define FontPlatformData_h

#include "GlyphBuffer.h"
#include "FontDescription.h"

class PGContext;
class PGFont;

namespace WebCore {

class FontPlatformData {
public:
	FontPlatformData(WTF::HashTableDeletedValueType)
        : m_font(hashTableDeletedFontValue())
        { }
	
    FontPlatformData()
        : m_font(hashTableDeletedFontValue())
        { }

    FontPlatformData(const FontDescription&, const String& family);
	FontPlatformData(const FontPlatformData& );
	FontPlatformData& operator=(const FontPlatformData& f);
    FontPlatformData(float size, bool bold, bool italic);
    FontPlatformData(PGFont* fontFace, int size, bool bold, bool italic);

    ~FontPlatformData();

#ifndef NDEBUG
    String description() const;
#endif
	
    static bool init();

    bool isFixedPitch();
    float size() const { return m_fontDescription.specifiedSize(); }
    void setFont(PGContext*) const;

    unsigned hash() const
    {
        uintptr_t hashCodes[1] = { reinterpret_cast<uintptr_t>(m_font) };
        return StringImpl::computeHash( reinterpret_cast<UChar*>(hashCodes), sizeof(hashCodes) / sizeof(UChar));
    }

    bool operator==(const FontPlatformData&) const;
	bool isHashTableDeletedValue() const {
		return m_font == hashTableDeletedFontValue();
	}

	static String mappedFamilyName(const FontDescription& fontDescription, const AtomicString& familyName);
	
	PGFont*	m_font;

private:
    FontDescription m_fontDescription;
	static PGFont *hashTableDeletedFontValue() { return reinterpret_cast<PGFont*>(-1); }
};

}

#endif
