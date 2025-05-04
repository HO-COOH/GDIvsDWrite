#pragma once
#include <string>
#include <wil/com.h>
#include "BaseWindow.hpp"
#include <d2d1.h>
#include <dwrite.h>
#include "ITextDisplay.h"
#include <winrt/base.h>

struct ID2D1HwndRenderTarget;

//Draw text using DirectWrite
class DWriteWindow : public BaseWindow<DWriteWindow, L"DWriteWindowClass">, public ITextDisplay
{
	winrt::hstring m_text;
	winrt::hstring m_fontFamily{ TEXT("Microsoft YaHei") };
	int m_fontSize = 56;
	wil::com_ptr<ID2D1HwndRenderTarget> m_renderTarget;
	wil::com_ptr<IDWriteTextFormat> textFormat;
	wil::com_ptr<ID2D1SolidColorBrush> m_textBrush;

	void recreateFont();
public:
	DWriteWindow(winrt::hstring const& text);

	static void OnPaint(HWND hwnd);
	static void OnSize(HWND hwnd, WPARAM wparam, UINT width, UINT height);

	// Inherited via ITextDisplay
	void SetText(winrt::hstring const& text) override;
	void SetFontSize(int fontSize) override;
	void SetFontFamily(winrt::hstring const& fontFamily) override;
};

