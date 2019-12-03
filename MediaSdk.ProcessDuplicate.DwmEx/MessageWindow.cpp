#include "pch.h"
#include "MessageWindow.h"


void MessageWindow::OnTargetSizeChanged()
{
	this->TargetSizeChanged(this, System::EventArgs::Empty);
}

MessageWindow::MessageWindow()
{
	this->CreateHandle(gcnew System::Windows::Forms::CreateParams);
}

void MessageWindow::WndProc(System::Windows::Forms::Message% m)
{
	System::Console::WriteLine(m.Msg);
	switch (m.Msg)
	{
	case WM_ACTIVATEAPP:
		this->OnTargetSizeChanged();
		break;
	}
	NativeWindow::WndProc(m);
}

