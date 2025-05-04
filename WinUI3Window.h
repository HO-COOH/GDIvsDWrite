#pragma once
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include "ITextDisplay.h"
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <Windows.h>

class WinUI3Window : public ITextDisplay
{
	winrt::Microsoft::UI::Dispatching::DispatcherQueueController controller = 
		winrt::Microsoft::UI::Dispatching::DispatcherQueueController::CreateOnCurrentThread();
	winrt::Microsoft::UI::Xaml::Hosting::WindowsXamlManager xamlManager = 
		winrt::Microsoft::UI::Xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread();
	winrt::Microsoft::UI::Xaml::Window window;
	winrt::Microsoft::UI::Xaml::Controls::TextBlock textBlock{ nullptr };
public:
	WinUI3Window(winrt::hstring const& text);

	// Inherited via ITextDisplay
	void SetText(winrt::hstring const& text) override;
	void SetFontSize(int fontSize) override;
	void SetFontFamily(winrt::hstring const& fontFamily) override;

	BOOL SetPosition(int x, int y, int cx, int cy, UINT flags) const;
};

