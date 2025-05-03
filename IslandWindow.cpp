#include "IslandWindow.h"
#include <windows.ui.xaml.interop.h>

winrt::Windows::UI::Xaml::Hosting::WindowsXamlManager IslandWindow::xamlManager{ nullptr };

IslandWindow::IslandWindow() : BaseWindow{L"UWPWindow"}
{
	if(!xamlManager)
		xamlManager = winrt::Windows::UI::Xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread();

	xamlSource = {};
	
	interop = xamlSource.as<IDesktopWindowXamlSourceNative>();
	winrt::check_hresult(interop->AttachToWindow(m_hwnd.get()));
	winrt::check_hresult(interop->get_WindowHandle(&m_islandHwnd));

	auto const clientRect = ClientRect();
	SetWindowPos(m_islandHwnd, 0, 0, 0, clientRect.right, clientRect.bottom, SWP_SHOWWINDOW);

}

void IslandWindow::SetContent(winrt::Windows::UI::Xaml::UIElement const& content)
{
	xamlSource.Content(content);
}

void IslandWindow::OnSize(HWND hwnd, WPARAM wparam, UINT width, UINT height)
{
	auto self = getSelfFromHwnd(hwnd);
	SetWindowPos(self->m_islandHwnd, 0, 0, 0, width, height, SWP_SHOWWINDOW);
}
