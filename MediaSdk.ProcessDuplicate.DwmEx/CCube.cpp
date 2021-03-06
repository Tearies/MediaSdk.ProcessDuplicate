#include "pch.h"
#include "CCube.h"
 


namespace MediaSdk
{

	namespace DxRender
	{
		void CCube::InitDevice()
		{
			HRESULT hr = S_OK;
			ID3D11Device* pd3dDevice;
			ID3D11DeviceContext* pImmediateContext;
			IDXGISwapChain* pSwapChain;
			D3D_FEATURE_LEVEL featureLevel;
			UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

			D3D_DRIVER_TYPE driverTypes[] =
			{
				D3D_DRIVER_TYPE_HARDWARE,
				D3D_DRIVER_TYPE_WARP,
				D3D_DRIVER_TYPE_REFERENCE,
			};
			UINT numDriverTypes = ARRAYSIZE(driverTypes);

			// DX10 or 11 devices are suitable
			D3D_FEATURE_LEVEL featureLevels[] =
			{
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
			};
			UINT numFeatureLevels = ARRAYSIZE(featureLevels);

			for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
			{
				hr = D3D11CreateDevice(NULL, driverTypes[driverTypeIndex], NULL, createDeviceFlags, featureLevels,
					numFeatureLevels,
					D3D11_SDK_VERSION, &pd3dDevice, &featureLevel, &pImmediateContext);

				if (SUCCEEDED(hr))
				{
					m_driverType = driverTypes[driverTypeIndex];
					m_pd3dDevice = pd3dDevice;
					m_pImmediateContext = pImmediateContext;
					break;
				}
			}
		}

		CCube::CCube()
		{
			m_hInst = NULL;
			m_featureLevel = D3D_FEATURE_LEVEL_11_0;
			m_pd3dDevice = NULL;
			m_pImmediateContext = NULL;
			remoting_texture_desc=new D3D11_TEXTURE2D_DESC;
			messageInject = new WindowMessageInject;
			DwmGetDxSharedSurface = Util::LoadWinAPILibraryAs<PFDwmGetDxSharedSurface>("user32.dll", "DwmGetDxSharedSurface");
			this->InitDevice();
		}

		HRESULT CCube::Render(void* pResource, bool isNewSurface)
		{
			HRESULT hr = S_OK;

			if (isNewSurface)
			{
				m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
				hr = InitRenderTarget(pResource);
				if (FAILED(hr))
				{
					return hr;
				}
			}
			const float ClearColor[4] = { 0.0, 0.0, 0.0, 1.0f };
			m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
			ID3D11Texture2D* pFrameCopy = nullptr;
			hr = m_pd3dDevice->CreateTexture2D(Remoting_DESC, nullptr, &pFrameCopy);
			ID3D11Texture2D* pSharedTexture = nullptr;
			hr = m_pd3dDevice->OpenSharedResource(targetShardSurface, __uuidof(ID3D11Texture2D), (void**)(&pSharedTexture));
			m_pImmediateContext->CopyResource(pFrameCopy, pSharedTexture);
			D3D11_MAPPED_SUBRESOURCE tempsubsource;
			m_pImmediateContext->Map(pFrameCopy, 0, D3D11_MAP_READ, 0, &tempsubsource);

			ID3D11Resource* resource;
			m_pRenderTargetView->GetResource(&resource);
			m_pImmediateContext->UpdateSubresource(resource, 0, 0, tempsubsource.pData, tempsubsource.RowPitch, tempsubsource.DepthPitch);
			m_pImmediateContext->Unmap(pFrameCopy, 0);


			if (nullptr != m_pImmediateContext)
				m_pImmediateContext->Flush();
			ReleaseInterface(resource);
			ReleaseInterface(pFrameCopy);
			ReleaseInterface(pSharedTexture);
			return hr;
		}

		HRESULT CCube::InitRenderTarget(void* pResource)
		{
			HRESULT hr = S_OK;
			IUnknown* pUnk = (IUnknown*)pResource;

			IDXGIResource* pDXGIResource;
			hr = pUnk->QueryInterface(__uuidof(IDXGIResource), (void**)&pDXGIResource);
			if (FAILED(hr))
			{
				return hr;
			}

			HANDLE sharedHandle;
			hr = pDXGIResource->GetSharedHandle(&sharedHandle);
			if (FAILED(hr))
			{
				return hr;
			}

			pDXGIResource->Release();

			IUnknown* tempResource11;
			hr = m_pd3dDevice->OpenSharedResource(sharedHandle, __uuidof(ID3D11Resource), (void**)(&tempResource11));
			if (FAILED(hr))
			{
				return hr;
			}

			ID3D11Texture2D* pOutputResource;
			hr = tempResource11->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&pOutputResource));
			if (FAILED(hr))
			{
				return hr;
			}
			ReleaseInterface(tempResource11);
			D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
			rtDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtDesc.Texture2D.MipSlice = 0;
			ID3D11RenderTargetView* pRenderTargetView;
			hr = m_pd3dDevice->CreateRenderTargetView(pOutputResource, &rtDesc, &pRenderTargetView);
			if (FAILED(hr))
			{
				return hr;
			}

			D3D11_TEXTURE2D_DESC outputResourceDesc;
			pOutputResource->GetDesc(&outputResourceDesc);
			if (outputResourceDesc.Width != m_Width || outputResourceDesc.Height != m_Height)
			{
				m_Width = outputResourceDesc.Width;
				m_Height = outputResourceDesc.Height;

				SetUpViewport();
			}

			m_pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
			ReleaseInterface(m_pRenderTargetView);
			m_pRenderTargetView = pRenderTargetView;
			ReleaseInterface(pOutputResource);
			return hr;
		}

		void CCube::SetUpViewport()
		{
			D3D11_VIEWPORT vp;
			vp.Width = (float)m_Width;
			vp.Height = (float)m_Height;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			m_pImmediateContext->RSSetViewports(1, &vp);
		}

		void CCube::Initialize(HWND handle)
		{
			messageInject->TargetHandle = handle;
			if(InternalInitailize())
			{
				messageInject->Start();
			}
			
		}

		bool CCube::InternalInitailize()
		{
			HWND targetWindow = messageInject->TargetHandle;
			LUID adapterLuid = { 0, };
			ULONG pFmtWindow = 0;
			ULONG pPresentFlags = 0;
			ULONGLONG pWin32kUpdateId = 0;
			HANDLE temp_targetShardSurface = nullptr;
			BOOL bSuccess = DwmGetDxSharedSurface(targetWindow, &temp_targetShardSurface, &adapterLuid, &pFmtWindow,
				&pPresentFlags, &pWin32kUpdateId);
			if (!bSuccess)
			{
				return true;
			}
			targetShardSurface = NULL;
			targetShardSurface = temp_targetShardSurface;
			
			ID3D11Texture2D* pSharedTexture = nullptr;
			HRESULT hrOpenSharedResource = m_pd3dDevice->OpenSharedResource(targetShardSurface, __uuidof(ID3D11Texture2D), (void**)(&pSharedTexture));
			D3D11_TEXTURE2D_DESC desc = { 0, };
			pSharedTexture->GetDesc(&desc);
			remoting_texture_desc->Width = desc.Width;
			remoting_texture_desc->Height = desc.Height;
			remoting_texture_desc->Format = desc.Format;
			remoting_texture_desc->ArraySize = 1;
			remoting_texture_desc->BindFlags = 0; // D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
			remoting_texture_desc->MiscFlags = 0; // D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_GDI_COMPATIBLE;
			remoting_texture_desc->SampleDesc.Count = 1;
			remoting_texture_desc->SampleDesc.Quality = 0;
			remoting_texture_desc->MipLevels = 1;
			remoting_texture_desc->CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
			remoting_texture_desc->Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
			ReleaseInterface(pSharedTexture);
			return true;
		}
		void CCube::Resize()
		{
		 InternalInitailize();
			
		}

		void CCube::Stop()
		{
			messageInject->Stop();
		}
	}
}
