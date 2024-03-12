#include "SplashScreen.h"

SplashScreen::SplashScreen(std::wstring filename, int nDuration) {
    image = new Image(filename);
    //m_StartTime = DXUtil.Timer(TIMER.GETABSOLUTETIME);
    QueryPerformanceCounter((LARGE_INTEGER*)&m_StartTime);
    m_EndTime = m_StartTime + nDuration;
    //m_ vb = new VertexBuffer(typeof(CustomVertex.TransformedTextured), 4, CGameEngine.Device3D, Usage.WriteOnly, CustomVertex.TransformedTextured.Format, Pool.Default);
}