#include "pch.h"
#include "DwmEx.h"
#include "d3d11_1.h"
using namespace MediaSdk::DwmEx;

DwmExManager::DwmExManager() :
	DwmGetDxSharedSurface(nullptr),
	m_pDevice(nullptr),
	m_pDeviceContext(nullptr),
	m_descFrame(nullptr)

{
}


void DwmExManager::CopySource()
{
	try
	{
		m_pDeviceContext->CopyResource(copyResource, pSharedTexture);
	}
	catch (Exception^ e)
	{
	}
}

void DwmExManager::Initialize(HWND targetWindow)
{
	DwmGetDxSharedSurface = Util::LoadWinAPILibraryAs<PFDwmGetDxSharedSurface>("user32.dll", "DwmGetDxSharedSurface");
	if (DwmGetDxSharedSurface == nullptr)
	{
		//Diagnostics::Debug::WriteLine("1");
		return;
	}
	//Diagnostics::Debug::WriteLine("2");

	LUID adapterLuid = {0,};
	ULONG pFmtWindow = 0;
	ULONG pPresentFlags = 0;
	ULONGLONG pWin32kUpdateId = 0;
	HANDLE temp_targetShardSurface = targetShardSurface;
	BOOL bSuccess = DwmGetDxSharedSurface(targetWindow, &temp_targetShardSurface, &adapterLuid, &pFmtWindow,
	                                      &pPresentFlags, &pWin32kUpdateId);
	if (!bSuccess)
	{
		return;
	}
	targetShardSurface = temp_targetShardSurface;
	D3D_FEATURE_LEVEL pFeatureLevel;
	UINT Flags = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SINGLETHREADED;
	auto temp_pDevice = m_pDevice;
	auto temp_m_pDeviceContext = m_pDeviceContext;
	HRESULT hr = ::D3D11CreateDevice(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, Flags, nullptr, 0, D3D11_SDK_VERSION,
		&temp_pDevice, &pFeatureLevel, &temp_m_pDeviceContext
	);
	if (FAILED(hr))
	{
		return;
	}

	m_pDevice = temp_pDevice;
	m_pDeviceContext = temp_m_pDeviceContext;
	ID3D11Texture2D* tpSharedTexture;
	HRESULT hrOpenSharedResource = m_pDevice->OpenSharedResource(targetShardSurface, __uuidof(ID3D11Texture2D),
	                                                             (void**)(&tpSharedTexture));
	if (FAILED(hr))
	{
		return;
	}
	pSharedTexture = tpSharedTexture;
	D3D11_TEXTURE2D_DESC desc = {0,};
	pSharedTexture->GetDesc(&desc);
	D3D11_TEXTURE2D_DESC _descFrame = {0,};
	_descFrame.Width = desc.Width;
	_descFrame.Height = desc.Height;
	_descFrame.Format = desc.Format;
	_descFrame.ArraySize = 1;
	_descFrame.BindFlags = 0; // D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
	_descFrame.MiscFlags = 0; // D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_GDI_COMPATIBLE;
	_descFrame.SampleDesc.Count = 1;
	_descFrame.SampleDesc.Quality = 0;
	_descFrame.MipLevels = 1;
	_descFrame.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	_descFrame.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
	m_descFrame = &_descFrame;
	ID3D11Texture2D* tmpcopyResource;
	m_pDevice->CreateTexture2D(m_descFrame, nullptr, &tmpcopyResource);
	copyResource = tmpcopyResource;
}
