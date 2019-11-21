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
			m_pVertexLayout = NULL;
			m_pVertexBuffer = NULL;
			this->InitDevice();
		}

		HRESULT CCube::Render(void* pResource, bool isNewSurface)
		{
			HRESULT hr = S_OK;

			/*if (isNewSurface)
			{
				m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
				hr = InitRenderTarget(pResource);
				if (FAILED(hr))
				{
					return hr;
				}
			}
			static float ClearColor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
			m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
			if (NULL != m_pImmediateContext)
			{
				m_pImmediateContext->Flush();
			}*/
			return hr;
		}

		HRESULT CCube::InitRenderTarget(ID3D11Texture2D* pResource)
		{
			HRESULT hr = S_OK;
			ID3D11RenderTargetView* pRenderTargetView;
			D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
			rtDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtDesc.Texture2D.MipSlice = 0;
			hr = m_pd3dDevice->CreateRenderTargetView(pResource, &rtDesc, &pRenderTargetView);
			if (FAILED(hr))
			{
				return hr;
			}
			m_pRenderTargetView = pRenderTargetView;
			D3D11_TEXTURE2D_DESC outputResourceDesc;
			pResource->GetDesc(&outputResourceDesc);
			if (outputResourceDesc.Width != m_Width || outputResourceDesc.Height != m_Height)
			{
				m_Width = outputResourceDesc.Width;
				m_Height = outputResourceDesc.Height;

				SetUpViewport();
			}

			m_pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

			if (NULL != pResource)
			{
				pResource->Release();
			}

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
	}
}
