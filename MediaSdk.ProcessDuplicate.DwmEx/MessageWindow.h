#pragma once
 
public ref class MessageWindow:System::Windows::Forms::NativeWindow
{
private:
	void OnTargetSizeChanged();
public:
	event System::EventHandler<System::EventArgs^>^ TargetSizeChanged;
	MessageWindow();
	void WndProc(System::Windows::Forms::Message% m) override;
};

