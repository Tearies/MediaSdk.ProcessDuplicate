#include "pch.h"
#include "ProcessRender.h"
 

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
	cCube = new CCube();
	duplicate_manager = gcnew ProcessDuplicateManager();
	const auto control = gcnew Image();
	control->Stretch = Stretch::Fill;
	this->Child = control;
	ProcessConfiguration^ config = gcnew ProcessConfiguration;
	OpenFileDialog^ file_dialog = gcnew OpenFileDialog;
	file_dialog->AddExtension = true;
	file_dialog->Multiselect = false;
	file_dialog->CheckFileExists = true;
	file_dialog->CheckPathExists = true;
	file_dialog->ReadOnlyChecked = true;
	 
	file_dialog->Filter = "运行程序|*.exe";
	if (file_dialog->ShowDialog())
	{
		config->AppPath = file_dialog->FileName;
		//config->AppPath = "D:\\支持\\冀北\\日志+沙盘\\NinthLayer1112\\NinthLayer_New.exe";
		//config->AppPath = "C:\\Program Files\\Windows NT\\Accessories\\wordpad.exe";
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

}
