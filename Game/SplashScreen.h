#pragma once
#include "Image.h"
#include <Windows.h>
class SplashScreen 
{
private:
    Image* image;
    __int64 m_StartTime;
    //float m_StartTime;
    float m_EndTime;

public:
    bool m_bInitialized = false;
    float fTimeLeft;

    SplashScreen(std::string FileName, int nDuration);
    ~SplashScreen();
};
