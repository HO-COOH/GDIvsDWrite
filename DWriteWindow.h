#pragma once
#include <string>
#include <wil/com.h>
#include "BaseWindow.hpp"
#include <d2d1.h>
#include <dwrite.h>

struct ID2D1HwndRenderTarget;

class DWriteWindow : public BaseWindow<DWriteWindow, L"DWriteWindowClass">
{
	std::wstring& m_text;
	wil::com_ptr<ID2D1HwndRenderTarget> m_renderTarget;
	wil::com_ptr<IDWriteTextFormat> textFormat;
	wil::com_ptr<ID2D1SolidColorBrush> m_textBrush;
public:
	DWriteWindow(std::wstring& text);

	static void OnPaint(HWND hwnd);
	static void OnSize(HWND hwnd, WPARAM wparam, UINT width, UINT height);
};

