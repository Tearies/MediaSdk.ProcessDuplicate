#pragma once
#include "windows.h"
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

 
public ref class MessageWindow:System::Windows::Forms::NativeWindow
{
private:
	int MessageID;
	void OnTargetSizeChanged();
public:
	event System::EventHandler<System::EventArgs^>^ TargetSizeChanged;
	MessageWindow();
	void WndProc(System::Windows::Forms::Message% m) override;
};

