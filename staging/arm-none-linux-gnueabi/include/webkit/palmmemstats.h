/* ============================================================
 * Date  : 2009-02-08
 * Copyright 2009 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSMEMSTATS_H
#define WEBOSMEMSTATS_H

#include "palmwebdefines.h"

#include <string>
#include <map>

namespace Palm
{

class WEBKIT_API MemStats
{
public:

	static void inc(const char* category, int size);
	static void dec(const char* category, int size);
	static void set(const char* category, int size);
	static void dumpToConsole();
	static bool getJSON( std::multimap<std::string,std::string>& outDocMapJSON, std::string& outCountersJSON );

private:

	static void init();
};

}

#if defined(ENABLE_MEMORY_STATS)

#define WEBOS_MEMSTATS_INC(category, size)		\
	Palm::MemStats::inc(category, size)
#define WEBOS_MEMSTATS_DEC(category, size)		\
	Palm::MemStats::dec(category, size)
#define WEBOS_MEMSTATS_SET(category, size)		\
	Palm::MemStats::set(category, size)

#else

#define WEBOS_MEMSTATS_INC(category, size)	
#define WEBOS_MEMSTATS_DEC(category, size)
#define WEBOS_MEMSTATS_SET(category, size)

#endif

#endif /* WEBOSMEMSTATS_H */
