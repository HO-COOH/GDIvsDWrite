#pragma once
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <string>

class WinUI3Window
{
	winrt::Microsoft::UI::Dispatching::DispatcherQueueController controller = 
		winrt::Microsoft::UI::Dispatching::DispatcherQueueController::CreateOnCurrentThread();
	winrt::Microsoft::UI::Xaml::Hosting::WindowsXamlManager xamlManager = 
		winrt::Microsoft::UI::Xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread();
	winrt::Microsoft::UI::Xaml::Window window;
public:
	WinUI3Window(std::wstring& text);
};

