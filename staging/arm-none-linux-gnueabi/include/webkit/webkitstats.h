#ifndef WEBKIT_STATS_H
#define WEBKIT_STATS_H

#include <string>
#include "palmwebdefines.h"

namespace Palm
{

namespace SimpleStats {
    class EventData;
}

class WEBKIT_API WebKitStats
{
public:

    static SimpleStats::EventData& getPaintEventData();
    static SimpleStats::EventData& getKeyboardEventData();
    static SimpleStats::EventData& getMouseDownEventData();
    static SimpleStats::EventData& getMouseMoveEventData();
    static SimpleStats::EventData& getMouseUpEventData();
    static SimpleStats::EventData& getGestureEventData();
    static SimpleStats::EventData& getScriptEvalEventData();
    static SimpleStats::EventData& getAcDoCompositeEventData();
    static SimpleStats::EventData& getAcUpdateContentsEventData();
    static SimpleStats::EventData& getAcTextureUpdateEventData();
    static SimpleStats::EventData& getAcPixmapCreateEventData();
    static SimpleStats::EventData& getAcDrawLayersEventData();
    static SimpleStats::EventData& getImageDecodeEventData();
    static SimpleStats::EventData& getJsGcEventData();
    static SimpleStats::EventData& getJsInvokeCallbackEventData();
    static SimpleStats::EventData& getJsInvokeListenerEventData();
    static SimpleStats::EventData& getJsInvokeTimerEventData();
    static SimpleStats::EventData& getJsCompileEventData();
    static SimpleStats::EventData& getJsRunEventData();
    static SimpleStats::EventData& getStyleRecalcEventData();
    static SimpleStats::EventData& getStyleForElementEventData();
    static SimpleStats::EventData& getDomEventDispatchEventData();
    static SimpleStats::EventData& getHtmlParseEventData();
    static SimpleStats::EventData& getServiceResponseEventData();

    static bool getJSON(std::string& json);

private:
};

}

#endif
