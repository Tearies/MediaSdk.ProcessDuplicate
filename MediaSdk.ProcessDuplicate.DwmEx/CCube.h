#pragma once
#include <windows.h>
#include <d3d11.h>

namespace MediaSdk
{
	namespace DxRender
	{
		public ref class CCube
		{ 
		private:
			HINSTANCE m_hInst;
			D3D_DRIVER_TYPE m_driverType;
			D3D_FEATURE_LEVEL m_featureLevel;
			UINT m_Width;
			UINT m_Height;
			ID3D11Device* m_pd3dDevice;
			ID3D11DeviceContext* m_pImmediateContext;
			IDXGISwapChain* m_pSwapChain = NULL;
			ID3D11RenderTargetView* m_pRenderTargetView = NULL;
			ID3D11Texture2D* backBufffer;  
			ID3D11Texture2D* outputBufffer;
			void InitDevice(); 
		public: 
			CCube();
			HRESULT Render(void* pResource, bool isNewSurface);
			HRESULT InitRenderTarget(void* pResource);
			void SetUpViewport();
			property ID3D11Texture2D* BackBuffer
			{
				ID3D11Texture2D* get()
				{
					return backBufffer;
				}
				void set(ID3D11Texture2D* buffer)
				{
					backBufffer = buffer;
				}
			}
		};
	}
}
