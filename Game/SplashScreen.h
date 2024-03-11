#pragma once
#include "Image.h"
class SplashScreen 
{
private:
    Image* image;
    float m_StartTime;
    float m_EndTime;
    //private VertexBuffer m_vb;
public:
    bool m_bInitialized = false;
    float fTimeLeft;

    SplashScreen(std::wstring FileName, int nDuration);
    ~SplashScreen();
};
