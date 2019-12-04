#pragma once
#include "pch.h"
#include "D3D11Image.h"
#include "ProcessDuplicateManager.h"
#include "CCube.h"

using namespace System;
using namespace System::Windows::Interop;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace Windows::Media;
using namespace ComponentModel;
using namespace MediaSdk::DxRender;
using namespace Microsoft::Win32;
namespace MediaSdk
{
	namespace Controls
	{
		public ref class ProcessRender : public Border
		{
		private:
			D3D11Image^ imageSource;
			ProcessDuplicateManager^ duplicate_manager;
			CCube^ cCube;
		public:
			property CCube^ Cube
			{
				CCube^ get()
				{
					return this->cCube;
				}
			}

			property D3D11Image^ ImageSource
			{
				D3D11Image^ get()
				{
					return this->imageSource;
				}
			}

			ProcessRender();
			~ProcessRender();
			void ResizeSurface();
			void OnRenderSizeChanged(SizeChangedInfo^ info) override;
			void DoRender(IntPtr surface, bool isNewSurface);
			void OnLoaded(System::Object^ sender, System::Windows::RoutedEventArgs^ e);
		};
	}
}
