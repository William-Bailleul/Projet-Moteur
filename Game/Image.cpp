#include "Image.h"

Image::Image(std::string FileName) {
	m_Filename = FileName;
}

ComPtr<ID3D12Resource> Image::CreateTextureResource(ID3D12Device* device) {
	int width, height, channels;
	unsigned char* image = stbi_load(m_Filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (!image) {
		return nullptr;
	}

    D3D12_RESOURCE_DESC textureDesc = {}; 
    textureDesc.Width = width; 
    textureDesc.Height = height; 
    textureDesc.MipLevels = 1; 
    textureDesc.DepthOrArraySize = 1; 
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
    textureDesc.SampleDesc.Count = 1; 
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE; 
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D; 

    D3D12_HEAP_PROPERTIES heapProperties = {};  
    heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT; 

    ComPtr<ID3D12Resource> texture; 
    device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &textureDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&texture)); 

    const UINT64 uploadBufferSize = GetRequiredIntermediateSize(texture.Get(), 0, 1); 

    ComPtr<ID3D12Resource> uploadHeap; 
    device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&uploadHeap)); 
     
    D3D12_SUBRESOURCE_DATA textureData = {}; 
    textureData.pData = image;  
    textureData.RowPitch = width * 4; 
    textureData.SlicePitch = textureData.RowPitch * height; 

    ComPtr<ID3D12GraphicsCommandList> commandList; 
    
    UpdateSubresources(commandList.Get(), texture.Get(), uploadHeap.Get(), 0, 0, 1, &textureData);

    // Transition texture to shader resource state
        device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, nullptr, nullptr, IID_PPV_ARGS(&commandList)); 

        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(texture.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        commandList->ResourceBarrier(1, &barrier); 

        commandList->Close(); 
        ID3D12CommandList* ppCommandLists[] = { commandList.Get() }; 
        device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)); 
        //commandQueue->ExecuteCommandLists(1, ppCommandLists); 

    return texture;
}