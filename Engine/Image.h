#pragma once
#include <iostream>
#include <d3d11_1.h>
#include "d3dx12.h"
class Image
{
	/*
	private Texture m_image = null;
	private ImageInformation m_info = new ImageInformation();
	private string    m_sFilename;*/
private:
	std::string m_sFilename;
	
public:
	Image(std::string fileName);
	void Load();
};

