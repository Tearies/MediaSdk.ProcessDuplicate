#include "pch.h"
#include "ProcessDuplicateManager.h"
#include "ProcessConfiguration.h"

using namespace MediaSdk::DwmEx;
using namespace MediaSdk::Clock;
using namespace MediaSdk::Common;

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

ProcessDuplicateManager::ProcessDuplicateManager():
	dwm_ex_manager(gcnew DwmExManager()),
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
	delete dwm_ex_manager;
}

void ProcessDuplicateManager::Start(ProcessConfiguration^ configuration)
{
	process_configuration = configuration;
	ProcessStartInfo^ startInfo = gcnew ProcessStartInfo();
	startInfo->FileName = configuration->AppPath;
	startInfo->Environment->Add(RemottingSharedHandle, this->RemottingHandle->ToInt32().ToString());
	startInfo->UseShellExecute = false;
	targetProcess = Process::Start(startInfo);
	targetProcess->WaitForInputIdle();
	Thread::Sleep(1000);
	dwm_ex_manager->Initialize(reinterpret_cast<HWND>(targetProcess->MainWindowHandle.ToInt32()));
	process_configuration->Application->Manager = dwm_ex_manager;
	process_configuration->ImageSource->SetPixelSize(dwm_ex_manager->TEXTURE2D_DESC->Width, dwm_ex_manager->TEXTURE2D_DESC->Height);
	media_context->ClockTick += gcnew System::EventHandler(this, &ProcessDuplicateManager::OnClockTick);
	media_context->Start();
}

void ProcessDuplicateManager::End()
{
	dwm_ex_manager->Stop();
	targetProcess->Kill();
}


void ProcessDuplicateManager::OnTargetSizeChanged(System::Object^ sender, System::EventArgs^ e)
{
	dwm_ex_manager->InternalInitailize();
	process_configuration->ImageSource->SetPixelSize(dwm_ex_manager->TEXTURE2D_DESC->Width, dwm_ex_manager->TEXTURE2D_DESC->Height);
}


void ProcessDuplicateManager::OnShutdownStarted(Object^ sender, EventArgs^ e)
{
	End();
}
