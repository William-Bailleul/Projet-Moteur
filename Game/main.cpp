#include "GameManager.h"
#include "Window.h"
#include "SplashScreen.h"
#include "Image.h"
//-----------------------
/*
#include "../Engine/ComponentRenderMesh.h"
#include "../Engine/EngineObject.h"
#include "../Engine/GeometryHandler.h"
*/
int WinMain() {
	ComPtr<ID3D12Device> device;
	D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

	Image image = Image("test");
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

	commandList->SetDescriptorHeaps(1, srvHeap.GetAddressOf());
	commandList->SetGraphicsRootDescriptorTable(0, srvHeap->GetGPUDescriptorHandleForHeapStart()); 


	//----------------------------- 
	//A tester et modifier
	/*
	EngineObject oEngineOject = EngineObject(1,1,1);
	Texture newTexture;
	newTexture.Resource = texture;
	Shader* shader;
	GeometryHandler geoHan;
	GeometryHandler::Mesh mesh = geoHan.BuildBox(1,1,1,1);
	ComponentRenderMesh splashRender = ComponentRenderMesh(&oEngineOject, mesh, shader, &newTexture);
	*/
	return 0;
}