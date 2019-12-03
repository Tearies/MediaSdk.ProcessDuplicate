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
	if (m.Msg == VBIDEFINEMSGCODE)
		this->OnTargetSizeChanged();
	NativeWindow::WndProc(m);
}

