#include "SplashScreen.h"

SplashScreen::SplashScreen( int nDuration) {
    QueryPerformanceCounter((LARGE_INTEGER*)&m_StartTime);
    m_EndTime = m_StartTime + nDuration;
    //render image
}