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
	//System::Console::WriteLine(m.Msg+" "+m.WParam.ToInt32());
	if (m.Msg == VBIDEFINEMSGCODE)
	{
		this->OnTargetSizeChanged();
		/*	int msg = m.Msg - VBIDEFINEMSGCODE;
			System::Console::WriteLine(msg);
			switch (msg)
			{
			case EVENT_SYSTEM_MOVESIZESTART:
			case EVENT_SYSTEM_MOVESIZEEND:
			case EVENT_SYSTEM_MINIMIZESTART:
			case EVENT_SYSTEM_MINIMIZEEND:
				this->OnTargetSizeChanged();
				break;
			}*/
	}
	/*switch (m.Msg)
	{
	case WM_ACTIVATEAPP:
		this->OnTargetSizeChanged();
		break;
	}*/
	NativeWindow::WndProc(m);
}

