#pragma once
 
#include <d3d11.h>
#include "WindowMessageInject.h"
#include "DwmEx.h"


namespace MediaSdk
{
	using namespace ProcessDuplicate::Common;
	namespace DxRender
	{
		public  class CCube
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
			ID3D11DepthStencilView* m_pDepthStencilView;
			ID3D11Texture2D* outputBufffer;
			D3D11_TEXTURE2D_DESC* remoting_texture_desc;
			void InitDevice();
			WindowMessageInject* messageInject;
			PFDwmGetDxSharedSurface DwmGetDxSharedSurface;
			HANDLE targetShardSurface = nullptr;
			ID3D11InputLayout* m_pVertexLayout;
			ID3D11VertexShader* m_pVertexShader;
			ID3D11PixelShader* m_pPixelShader;
			ID3D11Buffer* m_pVertexBuffer;
			//DwmExManager^ dwmExManager;
		public:
			_declspec(property(get = GetRemotingDESC)) D3D11_TEXTURE2D_DESC* Remoting_DESC;

			CCube();
			D3D11_TEXTURE2D_DESC* GetRemotingDESC()
			{
				return remoting_texture_desc;
			}
			HRESULT Render(void* pResource, bool isNewSurface);
			HRESULT InitRenderTarget(void* pResource);
			void SetUpViewport();
			void Initialize(HWND handle);
			bool InternalInitailize();
			void Resize();
			void Stop();
		};
	}
}
