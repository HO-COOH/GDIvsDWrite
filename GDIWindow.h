#pragma once
#include "BaseWindow.hpp"
#include <wil/resource.h>
#include <string>

class GDIWindow : public BaseWindow<GDIWindow, L"GDIWindowClass">
{
	wil::unique_hfont m_font;
	HBRUSH m_backgroundBrush;
	std::wstring& m_text;
public:
	GDIWindow(std::wstring& text);

	static void OnPaint(HWND hwnd);
};
