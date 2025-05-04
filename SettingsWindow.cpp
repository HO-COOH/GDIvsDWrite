#include "SettingsWindow.h"
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <Windows.h>
#include <unordered_set>
#include <string>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <microsoft.ui.xaml.window.h>
#include <ranges>
#include "ITextDisplay.h"

static auto GetFonts(HDC hdc)
{
	LOGFONT font{ .lfCharSet = DEFAULT_CHARSET };
	std::unordered_set<std::wstring> fonts;
	EnumFontFamiliesExW(
		hdc,
		&font,
		+[](LOGFONT const* font, TEXTMETRIC const* lpntme, DWORD fontType, LPARAM param)
		{
			//OutputDebugString(font->lfFaceName);
			reinterpret_cast<std::unordered_set<std::wstring>*>(param)->insert(font->lfFaceName);
			//OutputDebugString(std::format(L"{}\n", font->lfFaceName).data());
			return 1;
		},
		reinterpret_cast<LPARAM>(&fonts),
		0
	);
	std::vector<winrt::Windows::Foundation::IInspectable> retItems;
	retItems.reserve(fonts.size());
	std::ranges::transform(fonts, std::back_inserter(retItems), [](std::wstring const& fontName) {return winrt::box_value(fontName); });
	return retItems;
}

void SettingsWindow::textChanged(
	winrt::Windows::Foundation::IInspectable const& sender, 
	winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const&)
{
	auto newText = sender.as<winrt::Windows::UI::Xaml::Controls::TextBox>().Text();
	for (auto display : m_displays)
		display->SetText(newText);
}

void SettingsWindow::fontFamilyChanged(
	winrt::Windows::Foundation::IInspectable const& sender, 
	winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args)
{
	auto fontFamily = args.AddedItems().GetAt(0).as<winrt::hstring>();
	for (auto display : m_displays)
		display->SetFontFamily(fontFamily);
}

void SettingsWindow::fontSizeChanged(
	winrt::Windows::Foundation::IInspectable const& sender, 
	winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args)
{
	auto fontSize = winrt::unbox_value<int>(args.AddedItems().GetAt(0));
	for (auto display : m_displays)
		display->SetFontSize(fontSize);
}

SettingsWindow::SettingsWindow()
{
	auto fonts = GetFonts(GetDC(m_hwnd.get()));
	winrt::Windows::UI::Xaml::Controls::Grid rootGrid;
	{
		winrt::Windows::UI::Xaml::Controls::RowDefinition rows[2];
		rows[0].Height(winrt::Windows::UI::Xaml::GridLength{
			.GridUnitType = winrt::Windows::UI::Xaml::GridUnitType::Auto 
		});
		rows[1].Height(winrt::Windows::UI::Xaml::GridLength{
			.Value = 1.0,
			.GridUnitType = winrt::Windows::UI::Xaml::GridUnitType::Star 
		});

		rootGrid.RowDefinitions().ReplaceAll(rows);
	}
	{
		winrt::Windows::UI::Xaml::Controls::ColumnDefinition columns[2];
		for (auto& column : columns)
		{
			column.Width(winrt::Windows::UI::Xaml::GridLength{
				.Value = 1.0,
				.GridUnitType = winrt::Windows::UI::Xaml::GridUnitType::Star
			});
		}

		rootGrid.ColumnDefinitions().ReplaceAll(columns);
	}

	winrt::Windows::UI::Xaml::Controls::ComboBox fontFamilyComboBox;
	{
		fontFamilyComboBox.Header(winrt::box_value(L"Font family"));
		winrt::Windows::UI::Xaml::Controls::Grid::SetColumn(fontFamilyComboBox, 1);
		fontFamilyComboBox.Items().ReplaceAll(fonts);
		fontFamilyComboBox.SelectionChanged({ this, &SettingsWindow::fontFamilyChanged });
	}

	winrt::Windows::UI::Xaml::Controls::ComboBox fontSizeComboBox;
	{
		fontSizeComboBox.Header(winrt::box_value(L"Font size"));
		fontSizeComboBox.Items().ReplaceAll({
			winrt::box_value(8),
			winrt::box_value(9),
			winrt::box_value(10),
			winrt::box_value(11),
			winrt::box_value(12),
			winrt::box_value(14),
			winrt::box_value(16),
			winrt::box_value(18),
			winrt::box_value(20),
			winrt::box_value(24),
			winrt::box_value(28),
			winrt::box_value(36),
			winrt::box_value(48),
			winrt::box_value(56),
			winrt::box_value(72)
		});
		fontSizeComboBox.SelectedIndex(13);
		fontSizeComboBox.SelectionChanged({ this, &SettingsWindow::fontSizeChanged });
	}

	winrt::Windows::UI::Xaml::Controls::TextBox inputText;
	{
		inputText.Header(winrt::box_value(L"Input here to test font:"));
		inputText.Text(L"微软雅黑");
		winrt::Windows::UI::Xaml::Controls::Grid::SetRow(inputText, 1);
		winrt::Windows::UI::Xaml::Controls::Grid::SetColumnSpan(inputText, 2);
		inputText.TextChanged({ this, &SettingsWindow::textChanged });
		inputText.AcceptsReturn(true);
		inputText.TextWrapping(winrt::Windows::UI::Xaml::TextWrapping::Wrap);
	}

	rootGrid.Children().ReplaceAll({ fontFamilyComboBox, fontSizeComboBox, inputText });
	SetContent(rootGrid);
}

SettingsWindow& SettingsWindow::operator<<(ITextDisplay& window)
{
	m_displays.push_back(&window);
	return *this;
}

