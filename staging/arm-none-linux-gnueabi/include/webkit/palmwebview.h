/* ============================================================
 * Date  : 2008-09-22
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBVIEW_H
#define WEBOSWEBVIEW_H

#include <iostream>
#include <vector>
#include <list>
#include <stdint.h>

#include "palmwebdefines.h"
#include "palmwebtypes.h"

// Piranha
class PGSurface;
class PGContext;
class PGContextIface;
class PGFallbackFonts;
typedef PGSurface NativeSurface;
typedef PGContext NativeContext;

// Webkit WebOS glue
class PalmClipboard;

namespace WTF
{
class String;
}

namespace WebCore
{
class Element;
class Node;
class HTMLImageElement;                                         
class Frame;
class VisiblePosition;
class IntPoint;
class IntRect;
class SpellingWidgetController;
class GraphicsContext;
class ChromeClient;
class Document;
}


namespace Palm
{

class WebPage;
class WebViewClient;
struct SmartZoomState;
class ClipboardController;
class WordCompletionController;
class WebFrame;
class WebGLES2Context;

struct ImageInfo {
	std::string baseUri;
	std::string src;
	std::string title;
	std::string altText;
	std::string mimeType;
	int 		width;
	int 		height;

	ImageInfo() : width(0), height(0) {}
};

struct ElementInfo {
	std::string element;///< element tag name.
	std::string id;		///< element id attribute.
	std::string name;	///< element name attribute.
	std::string cname;	///< element class attribute.
	std::string type;	///< element type attribute.
	WebRect		bounds;	///< element bounds (doc coords).
	bool		isEditable;	///< Does rootEditableElement return anything?
	int			x;		///< The X value for the element (doc coords). (see click rectangle expansion)
	int			y;		///< The Y value for the element (doc coords). (see click rectangle expansion)

	ElementInfo() : isEditable(false), x(0), y(0) {
		bounds.left = bounds.top = bounds.right = bounds.bottom = 0;
	}
};

class WebViewPrivate;
class PalmFpsHandler;

class WEBKIT_API WebView
{
    friend class WebCore::ChromeClient;
    friend class WebViewPrivate;
public:

	WebView(WebViewClient* client=0);
	~WebView();

	WebViewClient* client() const;
	WebPage* page() const;

	void resize(int width, int height);
	void sendResizeEvent();
	void getContentRect(int& contentX, int& contentY, int& width, int& height);
	void getContentSize(int& width, int& height);
	void getContentPosition(int& c, int& y);
	void setContentPosition(int x, int y, bool updateOffset = false);

	int getFontScale() const;
	void setFontScale(int zoom);
	void setMinFontSize(int minFontSizePt);

	bool isEditing();

	void setScale(double scale);
	void setScaleAndPosition(double scale, int x, int y);
	double getScale() const;

	void fitWidth();

	void layoutIfNeeded();
	
	void setFallbackFonts( PGFallbackFonts* fonts );
	
	bool paint(NativeContext* context, int contentX, int contentY,
			   int width, int height, bool recomposite, bool mayScale);

	void focus(bool enable);
	void animate();

	bool keyEvent(unsigned short keyCode, unsigned short modifier, bool keyDown);
	bool mouseEvent(MouseEventType type, int x, int y, int clickCount, bool shiftKey=false, bool ctrlKey=false, bool altKey=false, bool metaKey=false, bool isSimulated=false);
	bool gestureEvent(GestureEventType type, int x, int y, float rotation, float scale, int centerX, int centerY,
					  bool shiftKey=false, bool ctrlKey=false, bool altKey=false, bool metaKey=false);
	bool touchEvent(Palm::TouchEventType type, const TouchPointPalm* touches, unsigned touchesLen,
					bool ctrlKey, bool altKey, bool shiftKey, bool metaKey);
    bool mouseHoldEvent(int x, int y);
                                                                                                     
	void setViewIsActive(bool isActive);
	bool isViewActive();
    void setViewIsVisible(bool isVisible);

    bool orientationChangeEvent(int position, float pitch, float roll, uint32_t time);
    bool shakeEvent(int shakeState, float shakeMagnitude, uint32_t time);
    bool accelerationEvent(float accelX, float accelY, float accelZ, uint32_t time);
    bool compassEvent(float magHeading, float trueHeading, float accuracy, uint32_t time);
	
	bool smartZoomAuto(int mouseX, int mouseY);

	// lockAreaHandle is a pointer to a plugin's WidgetRenderer, to which gestures and mouse 
    // events are redirected, when lockAreaHandle is not null
	bool smartZoomCalculate(int mouseX, int mouseY, WebRect& rect, int* lockAreaHandle);
	std::vector<WebRect> smartZoomCalculate(int mouseX, int mouseY);
	void smartZoomReset();
	
	void setViewportMeta(bool canScale, double scaleValue, int pageWidth, int pageHeight);
	void setInterrogateClicks(bool enable);
	bool getInterrogateClicks() const;

	int findString(const char* str, bool forward, bool caseSensitive, bool wrap, bool startWithSelection);
	void clearSelection();
	void selectAll();

    class TouchAdjuster {
    public:
        TouchAdjuster(unsigned topPadding, unsigned rightPadding, unsigned bottomPadding, unsigned leftPadding);

        WebCore::IntPoint findCandidatePointForTouch(const WebCore::IntPoint&, WebCore::Document*) const;

    private:
        unsigned m_topPadding;
        unsigned m_rightPadding;
        unsigned m_bottomPadding;
        unsigned m_leftPadding;
    };

	bool isInteractiveAtPoint(int mouseX, int mouseY);
    bool isClickableAtPoint(int mouseX, int mouseY);
	bool inspectUrlAtPoint(int x, int y, char*& outUrl, char*& outDesc, WebRect& outRect) const;
	
	bool downloadImageAtPoint( int x, int y, std::string& outFileName );
	bool getImageInfoAtPoint(int scaledX, int scaledY, ImageInfo& info);
	bool getElementInfoAtPoint(int scaledX, int scaledY, ElementInfo& info);

	void setTransparent(bool enable);
	bool getTransparent() const { return m_isTransparent; }
	
	void cut();
	bool copy();
	void paste();

	void setTextCaret(TextCaretType type);
	void getTextCaretPos( int& left, int& top, int& right, int& bottom );

	// system drag
	void dragStart(PalmClipboard*, int x, int y);
	void dragEnter(PalmClipboard*, int x, int y);
	void dragMove(PalmClipboard*, int x, int y);
	void dragLeave(PalmClipboard*, int x, int y);
	bool dragEnd(PalmClipboard*, int x, int y);

	void openInspectorAtPoint(int mouseX, int mouseY);
	void inspectAtPoint(int mouseX, int mouseY);

	void enableScrollbars(bool enable);
	bool scrollbarsEnabled() const;

	void popupMenuSelect(void* menu, int32_t selectedIdx);

	bool getElementWithAttrContentRect(const char* attrName, WebRect& rect);
	
	bool clickWouldChangeNodeFocus( int x, int y );
	
	void showClickedLink( bool bEnableDisable );

    void dumpRenderTree(std::ostream &output = std::cout);
    void dumpRenderTree(const char* fileName);
    void dumpCompositedTree(std::ostream &output = std::cout);
    void dumpCompositedTree(const char* fileName);
    static void dumpMemStats(std::ostream &output = std::cout);
    static void dumpMemStats(const char* fileName);

	// used to find flash content for routing mouse events
	void getFlashRects(std::vector<Palm::WebRect>& nodeRects);

	// used by link highlighting to get line rects of link
	void getInteractiveNodeRects(int mouseX, int mouseY, std::vector<Palm::WebRect>& nodeRects);
	
	// used by the framework to insert text into editable fields in the browser
	bool insertStringAtCursor(const char* str);

    // takes a string of text and sends it to the currently focused node
    // as a series of key events
    bool insertStringAsKeyEvents(const char* str);
	
	// used to make a document editable so that a selection can be made in it
	bool setSelectionMode(bool on);
	
	// used by webview to determine if we should go into special selection mode
	// for copy and paste. If an editable field is at coordinates, then we don't
	// go into design mode
	bool isEditableAtPoint(int x, int y);
	
	// to be used by the framework in the future (adauria)
	Palm::WebRect getFocusedNodeRect();
	
	// used by webview to enable edit->copy menu if a selection is a range
	bool selectionIsRange();
	
	void setMouseMode(MouseMode mode);

	void setViewport(const WebRect& rect, double zoom = 0.0f);
	const WebRect& getViewport();

	void pluginSpotlightStart(const WebRect& rect);
	void pluginSpotlightEnd();

	// used to launch a plugin in its own scene
	void launchFullscreenView(int pluginView);

	void hideSpellingWidget(void);
	void hideClipboardWidget(bool resetSelection);

// --> Palm IME support
	void setComposingText(const char* text);
	void commitComposingText();

	void performEditorAction(int fieldAction);

	void removeInputFocus();
// <--

	WebViewPrivate* privateData() {return m_data;}

    void print(const char* frameName, int lpsJobId, int printableWidth, int printableHeight, int printDpi, bool landscape, bool reverseOrder=false) const;

	// Debug Functions
	std::vector<PGSurface*> getCompositingLayers();

	bool supportsAcceleratedCompositing() const { return m_supportsAcceleratedCompositing; }
	void setSupportsAcceleratedCompositing(bool val);
	void unmapCompositingTextures();
    WebGLES2Context* getGLES2Context() const;
	
	static bool selectWordAroundCaret(WebCore::Frame* frame);
	static void selectWordAroundPosition(WebCore::Frame* frame, WebCore::VisiblePosition pos);
    const WebCore::IntRect wordBoundsAroundCaret(WebCore::Frame* frame);

    Palm::WebFrame* targetFrame() const { return m_targetFrame; }

    void setSupportsSingleAndLockStickyStates(bool enable);

    void usesSimulatedMouseClicks(bool val);

    WebCore::SpellingWidgetController* getSpellWidgetController();
    Palm::ClipboardController* getClipboardController();

    std::list<ScrollableLayerItem> getScrollableLayers() const;
    void scrollLayer(void* id, int deltaX, int deltaY);

private:

	class SpellingDragInfo;

	WebPage* m_page;
	WebViewClient* m_client;
	SmartZoomState* m_szState;
	bool m_interrogateClicks;
	bool m_scrollbarsEnabled;
	bool m_isTransparent;
	int m_lastMouseDownContentX;
	int m_lastMouseDownContentY;
	bool m_usingDifferentMousePos; ///< Using different mouse position other than one that came with mousedown.
    bool m_enableClickSearchRectangleExpansion;
	bool m_showClickedLinkThisView;
	bool m_isActive;
	PGFallbackFonts* m_fallbackFonts;
	WebCore::Node* m_nodeUnderMouseUp;
	MouseMode m_mouseMode;
	WebCore::Node* m_scrollingNode;	///< The node currently being scrolled by mouse moves
	WebRect m_viewport;
	SpellingDragInfo* m_dragInfo;
	
	WebViewPrivate* m_data;

    PalmFpsHandler* m_fpsHandler;

	// used to determine if webview is in copy and paste selection mode
	bool m_selectingForCopy;
	
	bool m_supportsAcceleratedCompositing;

	bool privateInteractiveAtPoint(int unscaled_x, int unscaled_y);
    bool findInteractivePt(int docX, int docY, int& newDocX, int& newDocY);
	bool privateGetElementInfoAtPoint(int x, int y, ElementInfo& info);
	bool trySendKeyPressForClipboardOperation( unsigned short key );
	bool replaceWordAroundCaret(const WTF::String* newWord);
	bool processTapForSpellingWidget(const WebCore::IntPoint& viewPt, bool isSimulatedMouseEvt);
	void paintRemainingWindowSurface(PGContextIface* context);

    void adjustPointForClicking(WebCore::IntPoint& clickPoint);
    WebCore::Node* getInteractiveNodeInRectangle(int mouseX, int mouseY);
	WebCore::Node* getInteractiveNodeAtPoint(int mouseX, int mouseY);
	static bool makeFileNameUnique(std::string& fname);
	static bool isImageSourceData(const WebCore::HTMLImageElement* img);
	static void replaceSelection(WebCore::Frame* frame, const WTF::String* newWord);

    Palm::WordCompletionController* getWordCompletionController();

    Palm::WebFrame* m_targetFrame;

    bool m_usesSimulatedMouseClicks;

	// not implemented	
	WebView();
};

}

#endif /* WEBOSWEBVIEW_H */
