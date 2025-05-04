#include "WinUI3Window.h"
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <microsoft.ui.xaml.window.h>

WinUI3Window::WinUI3Window(winrt::hstring const& text)
{
	textBlock = {};
	textBlock.Text(text);
	textBlock.FontSize(56);
	textBlock.TextWrapping(winrt::Microsoft::UI::Xaml::TextWrapping::Wrap);
	window.Content(textBlock);
	window.Activate();
}

void WinUI3Window::SetText(winrt::hstring const& text)
{
	textBlock.Text(text);
}

void WinUI3Window::SetFontSize(int fontSize)
{
	textBlock.FontSize(fontSize);
}

void WinUI3Window::SetFontFamily(winrt::hstring const& fontFamily)
{
	textBlock.FontFamily(winrt::Microsoft::UI::Xaml::Media::FontFamily{ fontFamily });
}

BOOL WinUI3Window::SetPosition(int x, int y, int cx, int cy, UINT flags) const
{
	HWND hwnd{};
	winrt::check_hresult(window.as<IWindowNative>()->get_WindowHandle(&hwnd));
	return SetWindowPos(hwnd, nullptr, x, y, cx, cy, flags);
}
