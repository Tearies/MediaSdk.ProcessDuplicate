#include "pch.h"
#include "ProcessDuplicateManager.h"
#include "ProcessConfiguration.h"

using namespace MediaSdk::DwmEx;
using namespace MediaSdk::Clock;
using namespace MediaSdk::Common;

void ProcessDuplicateManager::OnClockTick(Object^ sender, EventArgs^ args)
{
	Action^ action = gcnew Action(this, &ProcessDuplicateManager::DoRender);
	currentUIDistpatcher->BeginInvoke(DispatcherPriority::Normal,
		action);
}

void ProcessDuplicateManager::DoRender()
{
	dwm_ex_manager->CopySource();
	process_configuration->Application->BackBuffer = dwm_ex_manager->SharedResource;
	process_configuration->ImageSource->RequestRender();
}

ProcessDuplicateManager::ProcessDuplicateManager() :
	dwm_ex_manager(gcnew DwmExManager()),
	media_context(gcnew MediaContext()),
	currentUIDistpatcher(Application::Current->Dispatcher)
{
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
	targetProcess = Process::Start(process_configuration->AppPath);
	targetProcess->WaitForInputIdle();
	dwm_ex_manager->Initialize(reinterpret_cast<HWND>(targetProcess->MainWindowHandle.ToInt32()));
	media_context->ClockTick += gcnew System::EventHandler(this, &ProcessDuplicateManager::OnClockTick);
	media_context->Start();
}

void ProcessDuplicateManager::End()
{
	targetProcess->Kill();
}
