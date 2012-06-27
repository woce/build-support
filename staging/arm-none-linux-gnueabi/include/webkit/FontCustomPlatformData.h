
// Copyright 2010 Palm Inc.

#ifndef FontCustomPlatformData_h
#define FontCustomPlatformData_h

#include <wtf/text/WTFString.h>
#include <wtf/Noncopyable.h>

class PGFont;

namespace WebCore {

class FontPlatformData;
class SharedBuffer;

struct FontCustomPlatformData : Noncopyable {
    FontCustomPlatformData(PGFont* fontFace)
    : m_fontFace(fontFace)
    {}

    ~FontCustomPlatformData();

    FontPlatformData fontPlatformData(int size, bool bold, bool italic);

    static bool supportsFormat(const String&);
    
    PGFont* m_fontFace;
};

FontCustomPlatformData* createFontCustomPlatformData(SharedBuffer* buffer);

}

#endif
