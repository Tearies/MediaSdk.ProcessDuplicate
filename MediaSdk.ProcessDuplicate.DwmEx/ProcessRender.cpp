#include "pch.h"
#include "ProcessRender.h"
#include "D3D11Image.h"

#pragma once
using namespace MediaSdk::Controls;

namespace MediaSdk
{
	namespace Controls
	{
		ProcessRender::ProcessRender():
			cCube(nullptr),
			imageSource(nullptr),
			duplicate_manager(nullptr)
		{
			duplicate_manager = gcnew ProcessDuplicateManager();
			const auto control = gcnew Image();
			this->Child = control;
			ProcessConfiguration^ config = gcnew ProcessConfiguration();
			 
			config->AppPath = "D:\\支持\\冀北\\日志+沙盘\\NinthLayer1112\\NinthLayer_New.exe";
			if (!DesignerProperties::GetIsInDesignMode(this))
			{
				this->imageSource = gcnew D3D11Image();
				D3D11Image^ cc = this->imageSource;
				config->ImageSource = cc;
				config->Application = this->Cube;
				control->Source = config->ImageSource;
				config->ImageSource->
				//duplicate_manager->Start(config);
			}
		}

		ProcessRender::~ProcessRender()
		{
			duplicate_manager->End();
		}

		void ProcessRender::OnRenderSizeChanged(SizeChangedInfo^ info)
		{
			double dpiScale = 1.0;
			auto hwndTarget = static_cast<HwndTarget^>(PresentationSource::FromVisual(this)->CompositionTarget);
			if (hwndTarget != nullptr)
			{
				dpiScale = hwndTarget->TransformToDevice.M11;
			}
			int surfWidth = (int)(this->ActualWidth < 0 ? 0 : Math::Ceiling(this->ActualWidth * dpiScale));
			int surfHeight = (int)(this->ActualHeight < 0 ? 0 : Math::Ceiling(this->ActualHeight * dpiScale));
			this->imageSource->SetPixelSize(surfWidth, surfHeight);
		}
	}
}
