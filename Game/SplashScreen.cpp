#include "SplashScreen.h"

SplashScreen::SplashScreen(std::string filename, int nDuration) {
    image = new Image(filename);
    QueryPerformanceCounter((LARGE_INTEGER*)&m_StartTime);
    m_EndTime = m_StartTime + nDuration;
    //render image
}