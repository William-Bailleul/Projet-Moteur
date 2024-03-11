#pragma once
#include <iostream>
#include "../Engine/DDSTextureLoader.h"


class Image
{
private:
	std::wstring m_sFilename;
	HRESULT m_Texture;

	ID3D11Device* m_d3dDevice;
	const wchar_t* m_charFileName;
	ID3D11Resource** m_texture;
	ID3D11ShaderResourceView** m_textureView;
	
public:
	Image(std::wstring FileName);
	void Load();
	
};

