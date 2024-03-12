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

    //private VertexBuffer m_vb;
    ID3D11Buffer* m_vb;
public:
    bool m_bInitialized = false;
    float fTimeLeft;

    SplashScreen(std::wstring FileName, int nDuration);
    ~SplashScreen();
};
