#include "GameManager.h"
#include "Window.h"
#include "SplashScreen.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Image.h"
//-----------------------
#include "../Engine/ComponentRenderMesh.h"
#include "../Engine/EngineObject.h"
#include "../Engine/GeometryHandler.h"
#include "../Engine/Shader.h"

int main() {
	ComPtr<ID3D12Device> device;
	D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
	Image image = Image("test.jpg");
	ComPtr<ID3D12Resource> texture = image.CreateTextureResource(device.Get());
	SplashScreen splash = SplashScreen(5.0f);
	

	ComPtr<ID3D12DescriptorHeap> srvHeap; 
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart(); 

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {}; 
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; 
	srvDesc.Texture2D.MostDetailedMip = 0; 
	srvDesc.Texture2D.MipLevels = -1; 

	device->CreateShaderResourceView(texture.Get(), &srvDesc, srvHandle); 

	ComPtr<ID3D12GraphicsCommandList> commandList;


	//----------------------------- 
	//A tester et modifier

	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	bool msaaEnabled = true;
	UINT msaaQuality = 4; // Assuming you've queried this value

	EngineObject oEngineOject = EngineObject(1,1,1);
	Texture newTexture;
	newTexture.Resource = texture;
	//	Shader(Microsoft::WRL::ComPtr<ID3D12Device> Device, DXGI_FORMAT BBufferFormat, DXGI_FORMAT DStencilFormat, bool MSAAState, UINT MSAAQuality);
	Shader* shader = new Shader(device, backBufferFormat, depthStencilFormat, msaaEnabled, msaaQuality);
	GeometryHandler geoHan;
	GeometryHandler::Mesh mesh = geoHan.BuildBox(800,600,1,1);
	ComponentRenderMesh splashRender = ComponentRenderMesh(&oEngineOject, mesh, shader, &newTexture);

	commandList->SetDescriptorHeaps(1, srvHeap.GetAddressOf());
	commandList->SetGraphicsRootDescriptorTable(0, srvHeap->GetGPUDescriptorHandleForHeapStart()); 
	return 0;
}