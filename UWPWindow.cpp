#include "UWPWindow.h"
#include <winrt/Windows.UI.Xaml.Controls.h>

UWPWindow::UWPWindow(std::wstring& text) : m_text{text}
{

	winrt::Windows::UI::Xaml::Controls::TextBlock textBlock;
	textBlock.FontSize(56);
	textBlock.Text(text);
	SetContent(textBlock);
}
