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
			ID3D11Texture2D* copyResource;


		public:

			property ID3D11Texture2D* SharedResource
			{
				ID3D11Texture2D* get()
				{
					return this->copyResource;
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
