#pragma once
#include "Util.h"
#include "WindowMessageInject.h"
#include "MessageWindow.h"
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
			D3D11_TEXTURE2D_DESC* m_texture_2d_desc;
			ID3D11Texture2D* pSharedTexture;
			WindowMessageInject* messageInject;
			MessageWindow^ messageWindow;

		public:

			property D3D11_TEXTURE2D_DESC* TEXTURE2D_DESC
			{
				D3D11_TEXTURE2D_DESC* get()
				{
					return m_texture_2d_desc;
				}
			}
			property WindowMessageInject MessageInject
			{
				WindowMessageInject get()
				{
					return *messageInject;
				}
			}
			property ID3D11Device* Device
			{
				ID3D11Device* get()
				{
					return m_pDevice;
				}
			}

			property HANDLE ShardSurface
			{
				HANDLE get()
				{
					return targetShardSurface;
				}
			}
			property ID3D11DeviceContext* DeviceContext
			{
				ID3D11DeviceContext* get()
				{
					return m_pDeviceContext;
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
