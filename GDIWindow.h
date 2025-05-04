#pragma once
#include "BaseWindow.hpp"
#include <wil/resource.h>
#include <string>
#include <winrt/base.h>
#include "ITextDisplay.h"

//Draw text using GDI
class GDIWindow : public BaseWindow<GDIWindow, L"GDIWindowClass">, public ITextDisplay
{
	int m_fontSize = 72;
	winrt::hstring m_fontFamily{ TEXT("Microsoft YaHei") };
	wil::unique_hfont m_font;
	HBRUSH m_backgroundBrush;
	winrt::hstring m_text;

	void recreateFont();
public:
	GDIWindow(winrt::hstring const& text);

	static void OnPaint(HWND hwnd);
	static void OnDpiChanged(HWND hwnd, WORD dpiX, WORD dpiY, RECT* suggestPosition);

	// Inherited via ITextDisplay
	void SetText(winrt::hstring const& text) override;
	void SetFontSize(int fontSize) override;
	void SetFontFamily(winrt::hstring const& fontFamily) override;
};
