#include "pch.h"
#include "DwmEx.h"
#include "d3d11_1.h"
using namespace MediaSdk::DwmEx;

DwmExManager::DwmExManager() :
	DwmGetDxSharedSurface(nullptr),
	m_pDevice(nullptr),
	m_pDeviceContext(nullptr),
	m_descFrame(new D3D11_TEXTURE2D_DESC()),
	pSharedTexture(nullptr)
{
	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED | COINIT_DISABLE_OLE1DDE);
}


void DwmExManager::CopySource()
{
	try
	{
		ID3D11Texture2D* pFrameCopy = nullptr;
		HRESULT hr = m_pDevice->CreateTexture2D(m_descFrame, nullptr, &pFrameCopy);
		ID3D11Texture2D* pSharedTexture = nullptr;
		hr = m_pDevice->OpenSharedResource(targetShardSurface, __uuidof(ID3D11Texture2D), (void**)(&pSharedTexture));
		m_pDeviceContext->CopyResource(pFrameCopy, pSharedTexture);
		auto fileName = TEXT("D:\\Render\\") + ::GetTickCount64() + TEXT(".bmp");
		Util::SaveTextureToBmp(fileName, pFrameCopy);
		m_pDeviceContext->Unmap(pSharedTexture, 0);

	}
	catch (Exception ^ e)
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

	m_descFrame->Width = desc.Width;
	m_descFrame->Height = desc.Height;
	m_descFrame->Format = desc.Format;
	m_descFrame->ArraySize = 1;
	m_descFrame->BindFlags = 0; // D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
	m_descFrame->MiscFlags = 0; // D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_GDI_COMPATIBLE;
	m_descFrame->SampleDesc.Count = 1;
	m_descFrame->SampleDesc.Quality = 0;
	m_descFrame->MipLevels = 1;
	m_descFrame->CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	m_descFrame->Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
}
