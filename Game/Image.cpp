#include "Image.h"

Image::Image(std::wstring FileName) {
	m_sFilename = FileName;
	m_charFileName = m_sFilename.c_str();
}

void Image::Load() {
	m_Texture = DirectX::CreateDDSTextureFromFile(m_d3dDevice, m_charFileName, nullptr, m_textureView);
}