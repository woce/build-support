#ifndef WEBKIT_FPS_HANDLER_H
#define WEBKIT_FPS_HANDLER_H

#include <stdio.h>

// 60 frames
#define FPS_SAMPLING_INTERVAL 60
// 200000 us or 0.2 seconds
#define MAX_TIME_INTERVAL 200

namespace Palm
{

class PalmFpsHandler
{
public:
    PalmFpsHandler();
    PalmFpsHandler(char fileName[]);
    ~PalmFpsHandler();
    void framePainted(long int elapsedTimeMs);

private:

    void writeFile();

    int m_nCount;
    long int m_previousTimeMs;
    long double m_nFps, m_nAverageFps, m_nStandardDeviation;
    long double m_nTotalDeviation;

    FILE *m_fLog;
    char m_sFileName[512];
};

}

#endif
