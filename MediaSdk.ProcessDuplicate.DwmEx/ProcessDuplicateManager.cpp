#include "pch.h"
#include "ProcessDuplicateManager.h"


void ProcessDuplicateManager::OnClockTick(Object^ sender, EventArgs^ args)
{
	Action^ action = gcnew Action(this, &ProcessDuplicateManager::DoRender);
	currentUIDistpatcher->Invoke(DispatcherPriority::Normal,
		action);
}

void ProcessDuplicateManager::DoRender()
{
	process_configuration->ImageSource->RequestRender();
}

ProcessDuplicateManager::ProcessDuplicateManager() :

	media_context(gcnew MediaContext()),
	currentUIDistpatcher(Application::Current->Dispatcher)
{
	currentUIDistpatcher->ShutdownStarted += gcnew System::EventHandler(this, &MediaSdk::Common::ProcessDuplicateManager::OnShutdownStarted);
	messageWindow = gcnew  MessageWindow();
	messageWindow->TargetSizeChanged += gcnew System::EventHandler<System::EventArgs^>(this, &MediaSdk::Common::ProcessDuplicateManager::OnTargetSizeChanged);
}

ProcessDuplicateManager::~ProcessDuplicateManager()
{
	media_context->ClockTick -= gcnew System::EventHandler(this, &ProcessDuplicateManager::OnClockTick);
	media_context->Stop();
	delete media_context;
}

void ProcessDuplicateManager::Start(ProcessConfiguration^ configuration)
{
	process_configuration = configuration;
	ProcessStartInfo^ startInfo = gcnew ProcessStartInfo();
	startInfo->FileName = configuration->AppPath;
	System::Console::WriteLine(this->RemottingHandle->ToString());
	startInfo->Environment->Add(RemottingSharedHandle, this->RemottingHandle->ToString());
	startInfo->UseShellExecute = false;
	targetProcess = Process::Start(startInfo);
	targetProcess->EnableRaisingEvents = true;
	targetProcess->Exited += gcnew System::EventHandler(this, &MediaSdk::Common::ProcessDuplicateManager::OnExited);
	targetProcess->WaitForInputIdle();
	Thread::Sleep(1000);
	process_configuration->Application->Initialize(reinterpret_cast<HWND>(targetProcess->MainWindowHandle.ToInt32()));
	process_configuration->ImageSource->SetPixelSize(process_configuration->Application->Remoting_DESC->Width, process_configuration->Application->Remoting_DESC->Height);
	media_context->ClockTick += gcnew System::EventHandler(this, &ProcessDuplicateManager::OnClockTick);
	media_context->Start();
}

void ProcessDuplicateManager::End()
{
	process_configuration->Application->Stop();
	if (nullptr != targetProcess)
		targetProcess->Kill();
}


void ProcessDuplicateManager::OnTargetSizeChanged(System::Object^ sender, System::EventArgs^ e)
{
	process_configuration->Application->Resize();
	process_configuration->ImageSource->SetPixelSize(process_configuration->Application->Remoting_DESC->Width, process_configuration->Application->Remoting_DESC->Height);
}


void ProcessDuplicateManager::OnShutdownStarted(Object^ sender, EventArgs^ e)
{
	End();
}


void ProcessDuplicateManager::OnExited(System::Object^ sender, System::EventArgs^ e)
{
	targetProcess = nullptr;
}
