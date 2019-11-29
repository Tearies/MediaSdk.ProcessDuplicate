#include "pch.h"
#include "ProcessRender.h"
#include "D3D11Image.h"

#pragma once
using namespace MediaSdk::Controls;

namespace MediaSdk
{
	namespace Controls
	{
		ProcessRender::ProcessRender() :
			cCube(nullptr),
			imageSource(nullptr),
			duplicate_manager(nullptr)
		{

			Loaded += gcnew RoutedEventHandler(this, &ProcessRender::OnLoaded);

		}

		ProcessRender::~ProcessRender()
		{
			Loaded -= gcnew RoutedEventHandler(this, &ProcessRender::OnLoaded);
			duplicate_manager->End();
		}

		void ProcessRender::ResizeSurface()
		{
			/*	if (!this->IsLoaded)
					return;
				double dpiScale = 1.0;
				auto hwndTarget = static_cast<HwndTarget^>(PresentationSource::FromVisual(this)->CompositionTarget);
				if (hwndTarget != nullptr)
				{
					dpiScale = hwndTarget->TransformToDevice.M11;
				}
				int surfWidth = (int)(this->ActualWidth < 0 ? 0 : Math::Ceiling(this->ActualWidth * dpiScale));
				int surfHeight = (int)(this->ActualHeight < 0 ? 0 : Math::Ceiling(this->ActualHeight * dpiScale));
				this->imageSource->SetPixelSize(surfWidth, surfHeight);*/
		}

		void ProcessRender::OnRenderSizeChanged(SizeChangedInfo^ info)
		{

		}

		void ProcessRender::DoRender(IntPtr surface, bool isNewSurface)
		{
			this->Cube->Render(static_cast<void*>(surface), isNewSurface);
		}
	}
}


void ProcessRender::OnLoaded(Object^ sender, RoutedEventArgs^ e)
{
	cCube = gcnew CCube();
	duplicate_manager = gcnew ProcessDuplicateManager();
	const auto control = gcnew Image();
	control->Stretch = Stretch::UniformToFill;
	this->Child = control;
	ProcessConfiguration^ config = gcnew ProcessConfiguration();

	config->AppPath = "D:\\支持\\冀北\\日志+沙盘\\NinthLayer1112\\NinthLayer_New.exe";
	//config->AppPath = "notepad";
	if (!DesignerProperties::GetIsInDesignMode(this))
	{
		this->imageSource = gcnew D3D11Image();
		config->ImageSource = this->imageSource;
		const auto window = Window::GetWindow(this);
		const auto interophelper = gcnew WindowInteropHelper(window);
		config->ImageSource->WindowOwner = interophelper->Handle;
		config->ImageSource->OnRender = gcnew Action<IntPtr, bool>(this, &ProcessRender::DoRender);
		config->Application = this->Cube;
		control->Source = config->ImageSource;
		ResizeSurface();
		config->ImageSource->RequestRender();
		duplicate_manager->Start(config);
	}
}
