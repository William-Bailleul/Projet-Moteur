#pragma once
#include <Windows.h>
class SplashScreen 
{
private:
    __int64 m_StartTime;
    //float m_StartTime;
    float m_EndTime;

public:
    float fTimeLeft;

    SplashScreen( int nDuration);
    ~SplashScreen();
};
