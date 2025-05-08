#include "UWPWindow.h"
#include <winrt/Windows.UI.Xaml.Media.h>

UWPWindow::UWPWindow(winrt::hstring const& text)
{ 
	textBlock = {};
	textBlock.FontSize(56);
	textBlock.Text(text);
	SetContent(textBlock);
	textBlock.TextWrapping(winrt::Windows::UI::Xaml::TextWrapping::Wrap);
}

void UWPWindow::SetText(winrt::hstring const& text)
{
	textBlock.Text(text);
}

void UWPWindow::SetFontSize(int fontSize)
{
	textBlock.FontSize(fontSize);
}

void UWPWindow::SetFontFamily(winrt::hstring const& fontFamily)
{
	textBlock.FontFamily(winrt::Windows::UI::Xaml::Media::FontFamily{ fontFamily });
}
