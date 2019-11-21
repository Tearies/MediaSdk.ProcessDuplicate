#pragma once
#include "d3d11_1.h"
using namespace System;

namespace MediaSdk
{
	namespace Common
	{
		ref class RenderTargetProxy
		{
		private:
			IntPtr^ surface;
			ID3D11Texture2D* renderSurface;
			ID3D11Device* pDevice;
			ID3D11DeviceContext* pdevicecontext;
			ID3D11RenderTargetView* prender_target_view;
			IDXGISwapChain* pswapChain;;
			/**
			 * @brief 需要显示的Surface
			 */
			property IntPtr^ Surface
			{
				IntPtr^ get()
				{
					return this->surface;
				};
				void set(IntPtr^ targetSurface)
				{
					this->surface = targetSurface;
				};
			};

		public:
			property ID3D11Texture2D* RenderSurface
			{
			private:
				void set(ID3D11Texture2D* value)
				{
					this->renderSurface = value;
				}
			public:
				ID3D11Texture2D* get()
				{
					return this->renderSurface;
				}
			}
		public:
			RenderTargetProxy(IntPtr^ targetSurface);
			void Update();
			void CopySource(ID3D11Texture2D* shared_resource);
		};
	}
}
