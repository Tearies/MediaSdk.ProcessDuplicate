#pragma once
#include "windows.h"
using namespace System::Runtime::InteropServices;
ref class MessageWindow:System::Windows::Forms::NativeWindow
{
private:
	int MessageID;
public:
	MessageWindow();
	void WndProc(System::Windows::Forms::Message% m) override;
};

