#pragma once
#include "BaseWindow.hpp"
#include <string>
#include <wil/resource.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>

class UWPWindow : public BaseWindow<UWPWindow, L"UWPWindow">
{
	std::wstring& m_text;
	wil::unique_hwnd islandHwmd;
	winrt::Windows::UI::Xaml::Hosting::WindowsXamlManager xamlManager{ nullptr };
	winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource xamlSource{ nullptr };
public:
	UWPWindow(std::wstring& text);
};

