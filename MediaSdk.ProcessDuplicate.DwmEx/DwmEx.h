#pragma once
#include "Util.h"
using namespace System;
using namespace MediaSdk::ProcessDuplicate::Common;

namespace MediaSdk
{
	namespace DwmEx
	{
		public ref class DwmExManager
		{
		private:
			PFDwmGetDxSharedSurface DwmGetDxSharedSurface;
			HANDLE targetShardSurface = nullptr;
			ID3D11Device* m_pDevice;
			ID3D11DeviceContext* m_pDeviceContext;
			D3D11_TEXTURE2D_DESC* m_descFrame;
			ID3D11Texture2D* pSharedTexture;
			D3D11_MAPPED_SUBRESOURCE* backBuffer;
		public:

			property D3D11_MAPPED_SUBRESOURCE* BackBuffer
			{
				D3D11_MAPPED_SUBRESOURCE* get()
				{
					return backBuffer;
				}
			}
		 
			/**
			 * \brief 
			 */
			DwmExManager();
			void CopySource();
			void Initialize(HWND targetWindow);
		};
	}
}
