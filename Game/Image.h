#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include <vector>
#include "../Engine/d3dx12.h"
#include <iostream>

using Microsoft::WRL::ComPtr;

// Load image using STB Image
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Image
{
private:
	std::string m_Filename;
	ComPtr<ID3D12Fence> fence;

	
public:
	Image(std::string FileName);
	ComPtr<ID3D12Resource> CreateTextureResource(ID3D12Device* device);
};

