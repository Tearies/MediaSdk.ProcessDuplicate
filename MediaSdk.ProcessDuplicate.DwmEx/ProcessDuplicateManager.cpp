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
	//this->process_configuration->Render->Cube->Render(dwm_ex_manager->SharedResource, false);
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
	 //process_configuration->ImageSource->
	media_context->ClockTick += gcnew System::EventHandler(this, &ProcessDuplicateManager::OnClockTick);
	media_context->Start();
}

void ProcessDuplicateManager::End()
{
	targetProcess->Kill();
}
