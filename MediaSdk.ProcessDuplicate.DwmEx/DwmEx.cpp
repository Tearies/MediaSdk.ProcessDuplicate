#include "pch.h"
#include "DwmEx.h"
#include "d3d11_1.h"
using namespace MediaSdk::DwmEx;

DwmExManager::DwmExManager() :
	DwmGetDxSharedSurface(nullptr),
	m_pDevice(nullptr),
	m_pDeviceContext(nullptr),
	m_texture_2d_desc(new D3D11_TEXTURE2D_DESC()),
	pSharedTexture(nullptr),
	messageInject(new WindowMessageInject()),
	messageWindow(gcnew MessageWindow())
{
	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED | COINIT_DISABLE_OLE1DDE);
}


void DwmExManager::CopySource()
{
	try
	{
		/*	ID3D11Texture2D* pFrameCopy = nullptr;
			HRESULT hr = m_pDevice->CreateTexture2D(m_descFrame, nullptr, &pFrameCopy);
			ID3D11Texture2D* pSharedTexture = nullptr;
			hr = m_pDevice->OpenSharedResource(targetShardSurface, __uuidof(ID3D11Texture2D), (void**)(&pSharedTexture));
			m_pDeviceContext->CopyResource(pFrameCopy, pSharedTexture);
			D3D11_MAPPED_SUBRESOURCE tempsubsource;
			m_pDeviceContext->Map(pFrameCopy, 0, D3D11_MAP_READ, 0, &tempsubsource);
			m_pDeviceContext->Unmap(pFrameCopy, 0);
			backBuffer = &tempsubsource;
			pFrameCopy->Release();
			pSharedTexture->Release();*/

	}
	catch (Exception ^ e)
	{
	}
}

void DwmExManager::Initialize(HWND targetWindow)
{
	messageInject->TargetHandle = targetWindow;
	DwmGetDxSharedSurface = Util::LoadWinAPILibraryAs<PFDwmGetDxSharedSurface>("user32.dll", "DwmGetDxSharedSurface");
	if (DwmGetDxSharedSurface == nullptr)
	{
		return;
	}
	LUID adapterLuid = { 0, };
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
	messageInject->Start();
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
	ID3D11Texture2D* pSharedTexture = nullptr;
	HRESULT hrOpenSharedResource = m_pDevice->OpenSharedResource(targetShardSurface, __uuidof(ID3D11Texture2D), (void**)(&pSharedTexture));
	D3D11_TEXTURE2D_DESC desc = { 0, };
	pSharedTexture->GetDesc(&desc);
	m_texture_2d_desc->Width = desc.Width;
	m_texture_2d_desc->Height = desc.Height;
	m_texture_2d_desc->Format = desc.Format;
	m_texture_2d_desc->ArraySize = 1;
	m_texture_2d_desc->BindFlags = 0; // D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
	m_texture_2d_desc->MiscFlags = 0; // D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_GDI_COMPATIBLE;
	m_texture_2d_desc->SampleDesc.Count = 1;
	m_texture_2d_desc->SampleDesc.Quality = 0;
	m_texture_2d_desc->MipLevels = 1;
	m_texture_2d_desc->CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	m_texture_2d_desc->Usage = D3D11_USAGE::D3D11_USAGE_STAGING;


}
