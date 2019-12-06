#include "pch.h"
#include "D3D11Image.h"
#include "SurfaceQueueInteropHelper.h"

namespace MediaSdk
{
	namespace Controls
	{
		static D3D11Image::D3D11Image()
		{
			OnRenderProperty = DependencyProperty::Register("OnRender",
			                                                Action<IntPtr, bool>::typeid,
			                                                D3D11Image::typeid,
			                                                gcnew UIPropertyMetadata(
				                                                nullptr, gcnew PropertyChangedCallback(
					                                                &RenderChanged)));

			WindowOwnerProperty = DependencyProperty::Register("WindowOwner",
			                                                   IntPtr::typeid,
			                                                   D3D11Image::typeid,
			                                                   gcnew UIPropertyMetadata(
				                                                   IntPtr::Zero,
				                                                   gcnew PropertyChangedCallback(&HWNDOwnerChanged)));
		}

		D3D11Image::D3D11Image()
		{
		}

		D3D11Image::~D3D11Image()
		{
			if (this->helper != nullptr)
			{
				this->helper->~SurfaceQueueInteropHelper();
				this->helper = nullptr;
			}
		}

		Freezable^ D3D11Image::CreateInstanceCore()
		{
			return gcnew D3D11Image();
		}

		void D3D11Image::HWNDOwnerChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs args)
		{
			D3D11Image^ image = dynamic_cast<D3D11Image^>(sender);

			if (image != nullptr)
			{
				if (image->helper != nullptr)
				{
					image->helper->HWND = static_cast<IntPtr>(args.NewValue);
				}
			}
		}

		void D3D11Image::RenderChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs args)
		{
			D3D11Image^ image = dynamic_cast<D3D11Image^>(sender);

			if (image != nullptr)
			{
				if (image->helper != nullptr)
				{
					image->helper->RenderD2D = static_cast<Action<IntPtr, bool>^>(args.NewValue);
				}
			}
		}

		void D3D11Image::EnsureHelper()
		{
			if (this->helper == nullptr)
			{
				this->helper = gcnew SurfaceQueueInteropHelper();
				this->helper->HWND = this->WindowOwner;
				this->helper->D3DImage = this;
				this->helper->RenderD2D = this->OnRender;
			}
		}

		void D3D11Image::RequestRender()
		{
			this->EnsureHelper();
			if (nullptr != this->OnRender)
			{
				this->helper->RequestRenderD2D();
			}
		}

		void D3D11Image::SetPixelSize(int pixelWidth, int pixelHeight)
		{
			this->EnsureHelper();
			this->helper->SetPixelSize(static_cast<UInt32>(pixelWidth), static_cast<UInt32>(pixelHeight));
		}
	};
}
