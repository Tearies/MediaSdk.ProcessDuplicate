#pragma once

#include "CCube.h"
#include "D3D11Image.h"
using namespace System;
using namespace MediaSdk::DxRender;
using namespace MediaSdk::Controls;
namespace MediaSdk
{
	namespace Common
	{
		public ref class ProcessConfiguration :public Object
		{
		private:
			String^ appPath;
			String^ commandLine;
			CCube^ cApplication;
			D3D11Image^ imageSource;
		public:
			property String^ AppPath
			{
				String^ get()
				{
					return appPath;
				};

				void set(String^ path)
				{
					appPath = path;
				};
			};
			property String^ CommandLine
			{
				String^ get()
				{
					return commandLine;
				};
				void set(String^ _commandLine)
				{
					commandLine = _commandLine;
				};
			};

			property CCube^ Application
			{
				CCube^ get()
				{
					return cApplication;
				};
				void set(CCube^ commandLine)
				{
					cApplication = commandLine;
				};
			};

			property D3D11Image^ ImageSource
			{
				D3D11Image^ get()
				{
					return this->imageSource;
				}
				void set(D3D11Image^ commandLine)
				{
					imageSource = commandLine;
				};
			}

			ProcessConfiguration() :
				appPath(String::Empty),
				commandLine(String::Empty)

			{
			}
		};
	}
}
