#include "GDIWindow.h"
#include <Windows.h>

GDIWindow::GDIWindow(std::wstring& text) : m_font{
	CreateFontW(
		72 * GetDpi() / 96.0,
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
		TEXT("Microsoft YaHei")
	) },
	m_backgroundBrush{reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH))},
	m_text{text},
	BaseWindow{ L"GDI window" }
{

}

void GDIWindow::OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	auto hdc = BeginPaint(hwnd, &ps);

	auto self = getSelfFromHwnd(hwnd);
	auto oldFont = reinterpret_cast<HFONT>(SelectObject(hdc, self->m_font.get()));

	SetTextColor(hdc, RGB(0, 0, 0));
	FillRect(hdc, &ps.rcPaint, self->m_backgroundBrush);
	DrawText(hdc, self->m_text.data(), -1, &ps.rcPaint, DT_CENTER | DT_VCENTER);

	SelectObject(hdc, oldFont);
	EndPaint(hwnd, &ps);
}

void GDIWindow::OnDpiChanged(HWND hwnd, WORD dpiX, WORD dpiY, RECT* suggestPosition)
{
	getSelfFromHwnd(hwnd)->m_font.reset(
		CreateFontW(
		72 * dpiX / 96.0,
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
		TEXT("Microsoft YaHei")
	));
}
