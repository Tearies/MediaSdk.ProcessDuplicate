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

ProcessDuplicateManager::ProcessDuplicateManager(int surfWidth, int surfHeight) :
	messageWindow(gcnew  MessageWindow()),
	media_context(gcnew MediaContext()),
	currentUIDistpatcher(Application::Current->Dispatcher), m_surfWidth(surfWidth), m_surfHeight(surfHeight)
{
	currentUIDistpatcher->ShutdownStarted += gcnew System::EventHandler(this, &MediaSdk::Common::ProcessDuplicateManager::OnShutdownStarted);
	messageWindow->TargetSizeChanged += gcnew System::EventHandler<System::EventArgs^>(this, &MediaSdk::Common::ProcessDuplicateManager::OnTargetSizeChanged);
}

ProcessDuplicateManager::~ProcessDuplicateManager()
{
	media_context->ClockTick -= gcnew System::EventHandler(this, &ProcessDuplicateManager::OnClockTick);
	media_context->Stop();
	delete media_context;
}

void ProcessDuplicateManager::SetPixelSize()
{
	auto mainhwnd = reinterpret_cast<HWND>(targetProcess->MainWindowHandle.ToInt32());
	process_configuration->Application->Initialize(mainhwnd);
	auto width = process_configuration->Application->Remoting_DESC->Width;
	auto height = process_configuration->Application->Remoting_DESC->Height;
	if (mainhwnd == NULL)
	{
		width = this->m_surfWidth;
		height = this->m_surfHeight;
	}
	process_configuration->ImageSource->SetPixelSize(width, height);

	if(mainhwnd!=NULL)
	{
		media_context->ClockTick += gcnew System::EventHandler(this, &ProcessDuplicateManager::OnClockTick);
		media_context->Start();
	}
}

void ProcessDuplicateManager::OnDelayStart()
{
	HWND mainhwnd = NULL;
	do {
		mainhwnd = reinterpret_cast<HWND>(targetProcess->MainWindowHandle.ToInt32());
		Thread::Sleep(30);
	} while (mainhwnd == NULL);

	Action^ action = gcnew Action(this, &ProcessDuplicateManager::SetPixelSize);
	currentUIDistpatcher->Invoke(DispatcherPriority::Normal,
		action);


}

void ProcessDuplicateManager::Start(ProcessConfiguration^ configuration)
{
	process_configuration = configuration;
	ProcessStartInfo^ startInfo = gcnew ProcessStartInfo();
	startInfo->FileName = configuration->AppPath;
	auto handle = this->RemottingHandle;
	System::Console::WriteLine(handle.ToString());
	Environment::SetEnvironmentVariable(RemottingSharedHandle, handle.ToString(), EnvironmentVariableTarget::Process);
	startInfo->UseShellExecute = false;
	targetProcess = Process::Start(startInfo);
	targetProcess->EnableRaisingEvents = true;
	targetProcess->Exited += gcnew System::EventHandler(this, &MediaSdk::Common::ProcessDuplicateManager::OnExited);
	targetProcess->WaitForInputIdle();
	auto action = gcnew Action(this, &ProcessDuplicateManager::OnDelayStart);
	Tasks::Task::Factory->StartNew(action);
	this->SetPixelSize();
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
