
/*
	Copyright 2008 Palm Inc.
*/

#ifndef __webkitpalmsettings_h__
#define __webkitpalmsettings_h__

#include "webkitpalmdefines.h"

#include <string>

#define kMaxFilePath  (1024)
#define kMaxAgentStringLen  (1024)
#define kMaxMediaPipelineOptionStringLen  (1024)


struct WebKitPalmSettings 
{
	enum SpellChecking {
    	DISABLED,
    	UNDERLINE,
    	AUTO_CORRECT
    };
	bool 			private_browsing;
	bool 			java_script_enabled;
	bool 			java_script_can_open_windows_automatically;
	bool 			plugins_enabled;
	bool			acceptCookies;

	bool            runningInBrowserServer;
	
	bool            enableEnhancedViewport;

	int				browserViewWidth;
	int				browserViewHeight;
	
	unsigned long	memCacheMinDeadBytes;
	unsigned long	memCacheMaxDeadBytes;
	unsigned long	memCacheTotalBytes;
	unsigned long	pageCacheCapacity;
	
	bool			diskCacheEnabled;
	unsigned long	diskCacheTotalBytes;
	bool			diskCacheDebug;
	unsigned long	diskCacheLargestObjectSize;
	char			diskCachePath[kMaxFilePath+1];

	bool			logURLs;
	
	bool			enableTextIndexing;			///< Automatically create hyperlinks for text that looks like URL's, etc.

	bool			enableStickyState;			///< If modifier key is pressed w/o another key then remember state.
	SpellChecking	checkSpelling;				///< Check for spelling errors and underline/auto-correct if specified.
	bool			checkGrammar;				///< Auto capitalize first word of sentence.
	bool			shortcutChecking;			///< Should I look for shortcuts and replace if found?

    unsigned        wordCompletionStartLength;  ///< minimum number of characters we need before offering word completions.

	bool			enableFitWidth;
	bool			enableLayoutPaintThrottling;
	bool			enableFrameFlattening;
	
	char			font_symbol[kMaxFilePath+1];
	char			appDatabasePath[kMaxFilePath+1];
	char			webkitDataPath[kMaxFilePath+1];
	unsigned long long appDatabaseQuota;
	char			cookieJarPath[kMaxFilePath+1];	
	char			s_pluginsPath[kMaxFilePath+1];
	char            s_userInstalledPluginsPath[kMaxFilePath+1];
	int				debuggerServerPort;
	bool			debuggerEnable;
	bool			enableDeveloperExtras;
    int             profilerVerbosity;  ///< 0: profiling disabled
	bool			debugServiceHandles;
	
	bool			outputFpsEnable;
	char			outputFpsFileName[kMaxFilePath+1];

	bool			enableLocalStorage;
	char			localStoragePath[kMaxFilePath+1];

	bool			enableAppCache;
	char			appCacheDbPath[kMaxFilePath+1];
	int				appCacheDbMaxSize;

	bool			lunaCacheResources;
	bool			enableBytecodeCache;
	
	bool			disableAlphaBlend;
	bool			disableAutoScroll;
	
	float			fontScaleFactor;
	bool			showClickedLink;
    int             clickSearchRectangleTopPadding;
    int             clickSearchRectangleRightPadding;
    int             clickSearchRectangleBottomPadding;
    int             clickSearchRectangleLeftPadding;
    bool            enableClickSearchRectangleExpansion;
		
	bool			enableFastLocalLoad;
	
	int				networkTimeoutSeconds;
	bool			enableSqliteExtensions;
	bool			enableSynchronousDatabase;

	
	char			sharedClipboardFile[kMaxFilePath+1];
	
	int				userAgentIndex;
	char			userAgentTokensPath[kMaxFilePath+1];
	char			userAgentOverride[kMaxAgentStringLen+1];

    float           defaultZoomFactor;
    int				defaultVisibleHeight;

	int				minFontSize;
	int				minLogicalFontSize;
	int				defaultFixedFontSize;
	int				defaultFontSize;

	int             minTextAutoSizeFontSize;

	bool            disableGifAnimations;
	
	int				v8maxYoungSpaceBytes;
	int				v8maxOldSpaceBytes;
	int				v8StackLimitBytes;
	int				v8ExternalMemoryBytes;
	
	double			scriptMinimumTimerInterval; 
	
	char			tempSSLCertLocationPath[kMaxFilePath+1];
	
	bool			cachePluginsInDOM;

	char			diskImageCachePath[kMaxFilePath+1];
	int				diskImageCacheTotalBytes;
	int				diskImageFrameCacheTotalBytes;
	
	bool			sslStrictNameChecking;
	bool			enhanceExceptions;
	
	bool			enableEmoticons;
	char			emoticonImagesPath[kMaxFilePath+1];
	char 			emoticonBaseDictionaryFileAndPath[kMaxFilePath+1];
    char            emoticonClassName[kMaxFilePath+1];          ///< Class name to apply to all auto-replaced emoticons
	
	bool 			enableNoSteCommonTagsCheck;
	char			noSteCommonTagsFilePath[kMaxFilePath+1];

	char			fontsPath[kMaxFilePath+1];
	
	bool			logObjects;
	char			logObjectsFile[kMaxFilePath+1];
	
	bool			enableMemoryStats;

	int				maxActiveConnections;

	bool			enableCssOptimizations;

	int				freeMemoryThreshold;
	int				freeSwapThreshold;
	int				swapRateThreshold;
	bool			enableMemoryTracking;
    bool            enableOrphanedNodeReporting;
	
	int				maxInactiveFontData;
	int				targetInactiveFontData;

	int             maxImagePixelCount;

	unsigned long		htmlDbSize;

	char			defaultSerifFontFamilyName[kMaxFilePath+1];
	char			defaultSansSerifFontFamilyName[kMaxFilePath+1];
	char			defaultFixedFontFamilyName[kMaxFilePath+1];
	char			defaultStandardFontFamilyName[kMaxFilePath+1];
	
	bool            enableFileAccessWhitelist;

    int             spellWidgetYMargin;
    bool            enableAcceleratedCompositing;	// Use OpenGL ES to composite layers
	bool			showCompositedLayerBorders;		// Draw borders around layers for debugging purposes
    bool            sharedTexturesForCompositedLayers;
    
	char			defaultPrinterIP[kMaxFilePath+1];

    bool            clipboardWidgetsEnabled;
    bool            paintTextSelectionOnly;
    int             selectionMarkersTapTargetWidth;
    int             selectionMarkersTapTargetHeight;
    int             selectionHitTestOffset;

    char            mediaPlayPipelineOption[kMaxMediaPipelineOptionStringLen+1];

	bool smartTextEnabled() const;
};


// This is the global accessor to get the settings object.
WEBKIT_API WebKitPalmSettings*	PalmBrowserSettings( const char* configFile = 0 ); 

void WebKitPalmApplySettings();

#endif

