/* ============================================================
 * Date  : 2008-09-22
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBVIEWCLIENT_H
#define WEBOSWEBVIEWCLIENT_H

#include <stdint.h>

#include "palmwebdefines.h"
#include "palmwebtypes.h"
#include <stdint.h>

#include <ime/palmimedefines.h>

// FIXME: Move to namespace
class PalmClipboard;

namespace Palm
{

/** \defgroup FocusFlags editorFocused flags. */
/*\@{*/
const unsigned int EDITOR_STATE_AUTOCAP_SENTENCE         = 0x0001;
const unsigned int EDITOR_STATE_AUTOCAP_TITLE            = 0x0002;
const unsigned int EDITOR_STATE_AUTO_SUBSTITUTE          = 0x0004;
const unsigned int EDITOR_STATE_EMOTICONS                = 0x0008;
const unsigned int EDITOR_STATE_LINKER                   = 0x0010;
const unsigned int EDITOR_STATE_TEXT_ENTRY_OPT           = 0x0020;
const unsigned int EDITOR_STATE_TEXT_ENTRY_SHIFT         = 0x0040;
const unsigned int EDITOR_STATE_TEXT_ENTRY_LOCK          = 0x0080;
const unsigned int EDITOR_STATE_SPELL_CHECK_UNDERLINE    = 0x0100;
const unsigned int EDITOR_STATE_SPELL_CHECK_AUTO_CORRECT = 0x0200;
const unsigned int EDITOR_STATE_IME                      = 0x0400;

const unsigned int EDITOR_STATE_SPELL_CHECK_FLAGS = EDITOR_STATE_SPELL_CHECK_UNDERLINE |
													EDITOR_STATE_SPELL_CHECK_AUTO_CORRECT;

const unsigned int EDITOR_STATE_TEXT_ENTRY_OPT_LOCK = EDITOR_STATE_TEXT_ENTRY_OPT |
													EDITOR_STATE_TEXT_ENTRY_LOCK;

const unsigned int EDITOR_STATE_TEXT_ENTRY_SHIFT_LOCK = EDITOR_STATE_TEXT_ENTRY_SHIFT |
													EDITOR_STATE_TEXT_ENTRY_LOCK;
/*@}*/

class WebView;
class WebGLES2Context;

class WEBKIT_API WebViewClient
{
public:

	WebViewClient() {}
	virtual ~WebViewClient() {}
	
    virtual void getVirtualWindowSize(int& width, int& height) = 0;
    virtual void getWindowSize(int& width, int& height) = 0;
	virtual void getScreenSize( int& width, int& height ) = 0;
    virtual void resizedContents(int newWidth, int newHeight) = 0;
    virtual void zoomedContents(double scaleFactor, int newWidth, int newHeight, int newScrollOffsetX, int newScrollOffsetY) = 0;
    virtual void invalContents(int x, int y, int width, int height) = 0;
    virtual void scrolledContents(int newContentsX, int newContentsY) = 0;
    virtual void makePointVisible(int x, int y) = 0;
	virtual void linkClicked(const char* url) = 0;

	virtual bool smartKeySearch(int requestId, const char* query);
	virtual bool smartKeyLearn(const char* word);

	// Popup menus
	virtual bool popupMenuShow(void* menu, PopupMenuData* data) = 0;
	virtual bool popupMenuHide(void* menu) = 0;

	// focus stuff
	virtual void editorFocused(bool focused, unsigned int editorState);
	virtual void editorFocused(bool focused, int fieldType, int fieldActions, int fieldFlags);
	virtual void editorFocused(bool focused, const PalmIME::EditorState & editorState);
	virtual void focused() = 0;
	virtual void unfocused() = 0;

    virtual void autoCapEnabled(bool enabled);
	
	// text caret
	virtual TextCaretType textCaretAppearance() = 0;
    virtual void selectionChanged();

	// Dragging
	virtual void startDrag(int x, int y, int imgOffsetX, int imgOffsetY, void* dragImageRef, PalmClipboard* sysClipboard) = 0;

	// Viewport setting
    virtual void viewportTagParsed(double initialScale, double minimumScale, double maximumScale, int width, int height,
        bool userScalable, bool didUseConstantsForWidth, bool didUseConstantsForHeight) = 0;

	virtual void copiedToClipboard() = 0;
	virtual void pastedFromClipboard() = 0;
	
	// fullscreen spotlight
	virtual void pluginFullscreenSpotlightCreate(int spotlightHandle, int x, int y, int width, int height) = 0;
	virtual void pluginFullscreenSpotlightRemove() = 0;

    // interactive rects (pass mouse events), e.g., flash
    // TODO make these pure virtual once br server is in sync
    virtual void addInteractiveWidgetRect(uintptr_t id, int x, int y, int width, int height, InteractiveRectType type = InteractiveRectDefault);
    virtual void removeInteractiveWidgetRect(uintptr_t id, InteractiveRectType type = InteractiveRectDefault);

	// TODO make these pure virtual once br server is in sync
	virtual void needTouchEvents(bool needEvents);
    virtual void needSensorEvents(Palm::SensorType type, bool needEvents);
	virtual void openSearchUrl(const char* url);

    /**
     *  Function creates a sensor and returns an Opaque handle to the sensor instance
     *
     *  @param aType        - Type of the sensor to be created
     *  @param aDataCB      - Data callback will be called once data is available
     *  @param aErrCB       - Error callback will be called if there is some error encountered
     *  @param afnDelete    - Sensor Object deletion function
     *  @param pUserData    - User data - Ownership of this pointer is not transferred during this API.
     *  @return a Valid Handle of the sensor
     */
    virtual SensorHandle createSensor(SensorType aType, fnSensorDataCallback aDataCB, fnSensorErrorCallback aErrCB, fnSensorHandleDelete* afnDelete, void *pUserData) { return 0; }

    /**
     * Function destroys the particular sensor.
     *
     * @param apHandle - pointer to the handle of the sensor
     * @note apHandle will be invalid after this function call
     */
    virtual void destroySensor(SensorHandle* apHandle) { }

    /**
     * Function gets all the supported sensors by the platform
     *
     * @return json array list of all the sensors
     */
    virtual std::string getSupportedSensors() { return ""; }

    /**
     * Function sets the sensor rate for the given sensor
     */
    virtual bool setSensorRate(SensorHandle aHandle, SensorRate aRate) { return false; }

    /**
     * Start/Stop the sensor
     */
    virtual bool startSensor(SensorHandle aHandle, bool aOn) { return false; }

	virtual void spellingWidgetVisibleRectUpdate(int x, int y, int width, int height);

    virtual double getZoomLevel() { return 1.0; }
    virtual void showPrintDialog() { }

	// Support for GLES2 rendering
	virtual WebGLES2Context* createGLES2Context() { return 0; }

    // Called when a call to WebWidget::animate is required
    virtual void scheduleAnimation() { }

    virtual void suspendAppRendering();
    virtual void resumeAppRendering();

    virtual void setCanBlitOnScroll(bool val) {}
    virtual void didLayout() {}
};

}	

#endif /* WEBOSWEBVIEWCLIENT_H */
