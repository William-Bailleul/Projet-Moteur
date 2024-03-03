#pragma once

#include "Utile.h"

class Shader
{
public:
	Shader(Microsoft::WRL::ComPtr<ID3D12Device> Device, DXGI_FORMAT BBufferFormat, DXGI_FORMAT DStencilFormat, bool MSAAState, UINT MSAAQuality);
	~Shader();

	ComPtr<ID3DBlob> mvsByteCode;
	ComPtr<ID3DBlob> mpsByteCode;
	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	ComPtr<ID3D12PipelineState> mPSO = nullptr;
	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

public:
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;
	DXGI_FORMAT mBackBufferFormat;
	DXGI_FORMAT mDepthStencilFormat;
	bool m4xMsaaState;
	UINT m4xMsaaQuality;

private:
	void BuildRootSignature();
	void CompileShaders(const std::wstring filename);
	void BuildPSO();


private:
	const char* entrypoint;
	const char* target;
	const char* entrypoint2;
	const char* target2;
};

