#include "pch.h"
#include "MessageWindow.h"
 


MessageWindow::MessageWindow()
{
	MessageID = ::RegisterWindowMessageA("MediaSdk.ProcessDuplicate_BROADCAST_MESSAGE");
}

 

void MessageWindow::WndProc(System::Windows::Forms::Message% m)
{
	if(m.Msg==MessageID)
	{
		try
		{
		/*	auto message = Marshal::PtrToStructure<BROADCAST_MESSAGE>(m.WParam);
			if (message.ProcessID != 0)
			{
				System::Windows::Forms::MessageBox::Show(message.ProcessID.ToString());
			}*/

		}
		catch (System::Exception ^ e)
		{

		}

		
	}
	
}

 