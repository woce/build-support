/* ============================================================
 * Date  : 2008-09-22
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBFRAME_H
#define WEBOSWEBFRAME_H

#include "palmwebdefines.h"
#include "v8.h"
#include <string>
#include <lunaservice.h>
#include "PGContext.h"
#include "PGSurface.h"
extern "C" {
#include <jpeglib.h>
}

//#define WEBKIT_PRINT_TESTING_ENABLED

namespace WebKit
{
class FrameLoaderClient;
}

namespace WebCore
{
	class Frame;
	class AccessibilityObject;
    class IntRect;
    class FloatRect;
    class GraphicsContext;
    class PrintContext;
}

namespace Palm
{

class WebPage;
class WebFramePrivate;
class WebFrameData;
class WebFrameClient;

class WEBKIT_API WebFrame
{
public:

	WebPage* page() const;
	WebFrame* parentFrame();

    void setClient(WebFrameClient* client);
    WebFrameClient* client() const;

    // LayoutTests
	std::string toHtml();
	std::string toPlainText();
	std::string frameName();
    std::string renderTreeDump();
    std::string layerTreeAsText() const;
    bool pushObjectIntoFrame( const char* name, v8::Handle<v8::Object> obj );
	WebCore::Frame* webcoreFrame();
	WebCore::AccessibilityObject* getFocusedAccessibleElement();
    bool createJsObject(void* objClass, const char* name, void** obj, void** browserFuncs);

    bool evaluateScript(const char* script);

    struct WebFramePrintCtx {
        // variables global to the print context:
        WebFrame* palmWebFrame;
        int lpsJobId;
#ifdef WEBKIT_PRINT_TESTING_ENABLED
        char printerId[100];  //TESTING PURPOSES ONLY!
        bool jobCloseNeeded;
#endif
        WebCore::PrintContext* printContext;
        int currentPage;
        int totalPages;
        float renderZoomFactor;
        int renderPageWidth;
        int renderPageHeight;
        int renderSwathHeight;
        bool reverseOrder;

        // variables used in the context of an individual page:
        std::string pathName;
        int y;
        bool renderDone;
        bool blankRemaining;
        unsigned long start_time;
        FILE* fp;
        PGContext* pgContext;
        PGSurface* pgSurface;
        WebCore::GraphicsContext* graphicsContext;
        struct jpeg_compress_struct* jpgInfo;
        struct jpeg_error_mgr* jpgErr;


        WebFramePrintCtx(WebFrame* webFrame, int jobId, WebCore::PrintContext* printContext) {
            this->palmWebFrame = webFrame;
            this->lpsJobId = jobId;
#ifdef WEBKIT_PRINT_TESTING_ENABLED
            this->jobCloseNeeded = false;
#endif
            this->printContext = printContext;
            this->renderDone = false;
            this->currentPage = 0;
            this->totalPages = 0;
            this->renderZoomFactor = 0;
            this->renderPageWidth = 0;
            this->renderPageHeight = 0;
            this->renderSwathHeight = 0;
            this->reverseOrder = false;

            this->y = 0;
            this->renderDone = false;
            this->blankRemaining = true;

            this->fp = NULL;
            this->graphicsContext = NULL;
            this->pgContext = NULL;
            this->pgSurface = NULL;
            this->jpgInfo = NULL;
            this->jpgErr = NULL;
        }
    };
    /* Luna Print Service calls */
    bool isPrinting();
    void setPrinting(bool isPrinting=true);
    void print(int lpsJobId, int printableWidth, int printableHeight, int printDpi, bool landscape, bool reverseOrder=false);

private:

    /* Luna Service printmgr has reserved -300's for WebKit-generated error codes */
    enum RenderStatusCode {
        RENDER_STATUS_DONE = 0,                 // All pages have been rendered successfully
        RENDER_STATUS_ERR_UNKNOWN = -301,       // Unknown error occurred
        RENDER_STATUS_ERR_LUNA_SERVICE = -302,  // Call to luna service failed
        RENDER_STATUS_ERR_INVALID_JOB = -303,   // Invalid job parameters, e.g., invalid page range
        RENDER_STATUS_ERR_FILE = -304           // File I/O error, e.g., open, write, jpeg rendering
    };


    void renderPageBegin(WebFramePrintCtx *ctx);
    void spoolSwath(WebCore::IntRect pageRect, WebCore::GraphicsContext& ctx, const WebCore::IntRect& swathRect, float printContextWidth, float renderZoomFactor);
    int getPageHeight(const WebCore::IntRect& pageRect, float printContextWidth, float renderZoomFactor);
    int getActualSwathHeight(int renderPageHeight, int y, int renderSwathHeight);
    bool registerLpsClient();
    void unregisterLpsClient();
    static void cleanupPrintContext(WebFramePrintCtx *ctx);
    static void cleanupPageContext(WebFramePrintCtx *ctx);
    bool sendLpsJobsSetRenderStatus(int lpsJobId, int code, const char* text);

    bool sendLpsJobsNewTempFile(WebFramePrintCtx *ctx);
    static bool lpsJobsNewTempFileCallback(LSHandle *sh, LSMessage *reply, void *ctx);

    bool sendLpsJobsResizeTempFile(WebFramePrintCtx *ctx, int newSize);
    static bool lpsJobsResizeTempFileCallback(LSHandle *sh, LSMessage *reply, void *ctx);

    bool sendLpsJobsAddFile(WebFramePrintCtx *ctx, const char* pathName);
    static bool lpsJobsAddFileCallback(LSHandle *sh, LSMessage *reply, void *ctx);

#ifdef WEBKIT_PRINT_TESTING_ENABLED
    /* TESTING PURPOSES ONLY! */
    /*   printers/getCurrent and jobs/open are called only when the jobID is invalid, */
    /*   which should never happen */
    bool sendLpsPrintersGetCurrent(WebFramePrintCtx *ctx);
    static bool lpsPrintersGetCurrentCallback(LSHandle *sh, LSMessage *reply, void *ctx);
    bool sendLpsJobsOpen(WebFramePrintCtx *ctx);
    static bool lpsJobsOpenCallback(LSHandle *sh, LSMessage *reply, void *ctx);
    /* Remove this function when the Print dialog is fully integrated with WebKit-based apps: */
    bool sendLpsJobsClose(int lpsJobId);
#endif

	WebFrame(WebPage* parent, bool createRenderer=true);
	WebFrame(WebFrame* parentFrame, WebFrameData* frameData);
	~WebFrame();

private:
	
	WebFramePrivate* d;
	LSHandle* m_lpsClient;
    bool m_isPrinting;

	friend class WebPage;
	friend class WebFramePrivate;
	friend class WebPagePrivate;
	friend class WebKit::FrameLoaderClient;
	
    
private:

	WebFrame(const WebFrame&);
	WebFrame& operator=(const WebFrame&);

};

}

#endif /* WEBOSWEBFRAME_H */
