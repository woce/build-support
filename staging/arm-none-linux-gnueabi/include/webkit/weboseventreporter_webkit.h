#ifndef __weboseventreporter_webkit_h__
#define __weboseventreporter_webkit_h__

#include <string>
#include <glib.h>
#if !defined(WEBOS_DESKTOP)
# include <weboseventreporter.h>
#endif

namespace webOS {

class Reporter
{
public:

    /**
     * Log events with the event reporter. This class will stop the activity when it is
     * destroyed or earlier if stop is explicitly called.
     */
    class Event
    {
    public:

        /**
         * Construct a new activity object.
         */
        Event(const void* token, const char* name, const char* fmt = "", ...);

        /**
         * Destructor. Will stop the activity if not already stopped.
         */
        ~Event();

        /**
         * Stop is called by the destructor, but you may stop it earlier by calling
         * this function.
         */
        void stop();

        /**
         * If you want to log an activity start w/o creating any objects.
         */
        static void logStart(const void* token, const char* name, const char* value="");

        /**
         * If you want to log an activity stop w/o creating any objects.
         */
        static void logStop(const void* token, const char* name, const char* value="");

        /**
         * Log an event with no duration.
         */
        static void logEvent(const void* token, const char* name, const char* fmt = "", ...);

    private:

        Event& operator=(const Event& rhs);

        const void* m_token;
        std::string m_name;
        bool m_started;
    };

    /**
     * Initialize the event reporter.
     */
    static void init(GMainLoop* mainLoop);

    /**
     * Set to true to enable the event reporter. Default is false.
     */
    static void setVerbosity(int verbosity);
   
    /**
     * Return the logging verbosity.
     */
    static int getVerbosity() { return s_verbosity; }

    /**
     * Is the event reporter enabled?
     */
    static bool isEnabled(void) { return s_verbosity > 0; }

private:

    static int s_verbosity;

    Reporter();
    ~Reporter();
};

}

#endif
