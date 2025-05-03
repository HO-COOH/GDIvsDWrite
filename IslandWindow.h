#pragma once
#include "BaseWindow.hpp"
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>

class IslandWindow : public BaseWindow<IslandWindow, L"IslandWindow">
{
	static winrt::Windows::UI::Xaml::Hosting::WindowsXamlManager xamlManager;
	winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource xamlSource{ nullptr };
	winrt::com_ptr<IDesktopWindowXamlSourceNative> interop{ nullptr };
	HWND m_islandHwnd;
public:
	IslandWindow();

	void SetContent(winrt::Windows::UI::Xaml::UIElement const& content);

	static void OnSize(HWND hwnd, WPARAM wparam, UINT width, UINT height);
};

