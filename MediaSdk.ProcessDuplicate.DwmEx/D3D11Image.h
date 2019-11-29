#pragma once
#include "SurfaceQueueInteropHelper.h"
#include "DwmEx.h"
using namespace System;
using namespace System::Windows::Interop;
using namespace System::Windows;
namespace MediaSdk
{
	using namespace DwmEx;
	namespace Controls
	{
		public ref class D3D11Image : public D3DImage
		{
		private:
			static void RenderChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs args);
			static void HWNDOwnerChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs args);
			void EnsureHelper();
			static D3D11Image();
			SurfaceQueueInteropHelper^ helper;
			
		protected:
			Freezable^ CreateInstanceCore() override;
 
		public:
			D3D11Image();
			~D3D11Image();
		
			static DependencyProperty^ OnRenderProperty;
			static DependencyProperty^ WindowOwnerProperty;

			/// The OnRender action delegate will fire and pass the surface to the application that the DirectX rendering component should 
			/// render into.
			property Action<IntPtr, bool>^ OnRender
			{
				Action<IntPtr, bool>^ get()
				{
					return static_cast<Action<IntPtr, bool>^>(GetValue(OnRenderProperty));
				}

				void set(Action<IntPtr, bool>^ value)
				{
					SetValue(OnRenderProperty, value);
				}
			}

			property SurfaceQueueInteropHelper^ Helper
			{
				SurfaceQueueInteropHelper^ get()
				{
					return helper;
				}
				 
			}
			
			/// The window handle (HWND) of the Window which hosts the D3D11Image (used during DirectX surface creation).
			property IntPtr WindowOwner
			{
				IntPtr get()
				{
					return static_cast<IntPtr>(GetValue(WindowOwnerProperty));
				}

				void set(IntPtr value)
				{
					SetValue(WindowOwnerProperty, value);
				}
			}
			 
			
			/// The RequestRender method signals that the D3D11Image should get the DirectX rendering code to render a new frame to the provided surface.
			/// Typically the user of the D3D11Image calls this every time the CompositionTarget.Rendering event fires.
			void RequestRender();

			/// The application hosting the D3D11Image should ensure that the PixelSize is the number of pixels that the D3D11Image is
			/// being displayed in.
			void SetPixelSize(int pixelWidth, int pixelHeight);
		};
	}
}
