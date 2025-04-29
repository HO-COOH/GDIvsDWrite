#include "UWPWindow.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/base.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

UWPWindow::UWPWindow(std::wstring& text) : BaseWindow{L"UWPWindow"}, m_text{text}
{
	winrt::init_apartment(winrt::apartment_type::single_threaded);
	xamlManager = winrt::Windows::UI::Xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread();
	xamlSource = {};

	auto interop = xamlSource.as<IDesktopWindowXamlSourceNative>();
	winrt::check_hresult(interop->AttachToWindow(m_hwnd.get()));
	winrt::check_hresult(interop->get_WindowHandle(islandHwmd.put()));

	auto const clientRect = ClientRect();
	SetWindowPos(islandHwmd.get(), 0, 0, 0, clientRect.right, clientRect.bottom, SWP_SHOWWINDOW);

	winrt::Windows::UI::Xaml::Controls::TextBlock textBlock;
	textBlock.FontSize(56);
	textBlock.Text(text);
	//textBlock.RequestedTheme(winrt::Windows::UI::Xaml::ElementTheme::Light);
	xamlSource.Content(textBlock);
	//auto name = winrt::get_class_name(textBlock.XamlRoot().Content());
}
