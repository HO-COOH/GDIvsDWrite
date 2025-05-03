#pragma once
#include "IslandWindow.h"
#include <vector>
struct ITextDisplay;

class SettingsWindow : public IslandWindow
{
	void textChanged(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& args
	);

	void fontFamilyChanged(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args
	);

	void fontSizeChanged(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args
	);

	std::vector<ITextDisplay*> m_displays;
public:
	SettingsWindow();

	SettingsWindow& operator<<(ITextDisplay& window);
};

