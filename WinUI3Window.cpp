#include "WinUI3Window.h"
#include <winrt/Microsoft.UI.Xaml.Controls.h>

WinUI3Window::WinUI3Window(std::wstring& text)
{
	winrt::Microsoft::UI::Xaml::Controls::TextBlock textBlock;
	textBlock.Text(text);
	textBlock.FontSize(56);
	window.Content(textBlock);
	window.Activate();
}
