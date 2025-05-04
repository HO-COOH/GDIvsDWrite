#pragma once
#include "ITextDisplay.h"
#include "IslandWindow.h"
#include <winrt/Windows.UI.Xaml.Controls.h>

class UWPWindow : public IslandWindow, public ITextDisplay
{
	winrt::Windows::UI::Xaml::Controls::TextBlock textBlock{ nullptr };
public:
	UWPWindow(winrt::hstring const& text);

	// Inherited via ITextDisplay
	void SetText(winrt::hstring const& text) override;
	void SetFontSize(int fontSize) override;
	void SetFontFamily(winrt::hstring const& fontFamily) override;
};

