#include "GameManager.h"
#include "Window.h"
#include "SplashScreen.h"
#include "Image.h"

int WinMain() {
	ComPtr<ID3D12Device> device;
	D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

	Image image = Image("test");
	ComPtr<ID3D12Resource> texture = image.CreateTextureResource(device.Get());
	SplashScreen splash = SplashScreen(5.0f);
	

	ComPtr<ID3D12DescriptorHeap> srvHeap; // descriptor heap containing SRVs 
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart(); 

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {}; 
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; 
	srvDesc.Texture2D.MostDetailedMip = 0; 
	srvDesc.Texture2D.MipLevels = -1; 

	device->CreateShaderResourceView(texture.Get(), &srvDesc, srvHandle); 


	/*
		Texture2D gTexture : register(t0); // Texture register slot can vary based on your shader configuration
		SamplerState gSampler : register(s0); // Sampler register slot can vary based on your shader configuration

		// Use the texture in your shader
		float4 main(float2 texCoord : TEXCOORD) : SV_TARGET
		{
			return gTexture.Sample(gSampler, texCoord);
		}

			// Assuming you have a command list 'commandList' and a descriptor heap containing the SRVs 'srvHeap'
		commandList->SetDescriptorHeaps(1, srvHeap.GetAddressOf());
		commandList->SetGraphicsRootDescriptorTable(0, srvHeap->GetGPUDescriptorHandleForHeapStart()); // Assuming 0 is the root parameter index for the SRV
		*/
	return 0;
}