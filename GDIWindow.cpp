#include "GDIWindow.h"
#include <Windows.h>
#include <winrt/base.h>

void GDIWindow::recreateFont()
{
	m_font.reset(CreateFontW(
		m_fontSize * GetDpi() / 96.0,
		0,
		0,
		0,
		FW_REGULAR,
		false,
		false,
		false,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH,
		m_fontFamily.data()
	));
}

GDIWindow::GDIWindow(winrt::hstring const& text) :
	m_backgroundBrush{reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH))},
	m_text{text},
	BaseWindow{ L"GDI window" }
{
	recreateFont();
}

void GDIWindow::OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	auto hdc = BeginPaint(hwnd, &ps);

	auto self = getSelfFromHwnd(hwnd);
	auto oldFont = reinterpret_cast<HFONT>(SelectObject(hdc, self->m_font.get()));

	SetTextColor(hdc, RGB(0, 0, 0));
	FillRect(hdc, &ps.rcPaint, self->m_backgroundBrush);
	DrawText(hdc, self->m_text.data(), -1, &ps.rcPaint, DT_LEFT | DT_WORDBREAK);

	SelectObject(hdc, oldFont);
	EndPaint(hwnd, &ps);
}

void GDIWindow::OnDpiChanged(HWND hwnd, WORD dpiX, WORD dpiY, RECT* suggestPosition)
{
	auto self = getSelfFromHwnd(hwnd); 
	self->m_font.reset(
		CreateFontW(
		self->m_fontSize * dpiX / 96.0,
		0,
		0,
		0,
		FW_REGULAR,
		false,
		false,
		false,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH,
		self->m_fontFamily.data()
	));
}

void GDIWindow::SetText(winrt::hstring const& text)
{
	m_text = text.data();
	InvalidateRect(m_hwnd.get(), nullptr, true);
}

void GDIWindow::SetFontSize(int fontSize)
{
	m_fontSize = fontSize * 1.5;
	recreateFont();
	InvalidateRect(m_hwnd.get(), nullptr, true);
}

void GDIWindow::SetFontFamily(winrt::hstring const& fontFamily)
{
	m_fontFamily = fontFamily;
	recreateFont();
	InvalidateRect(m_hwnd.get(), nullptr, true);
}
