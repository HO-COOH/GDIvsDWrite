#include "DWriteWindow.h"
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

wil::com_ptr<ID2D1Factory> d2dFactory;
wil::com_ptr<IDWriteFactory> dwriteFactory;

DWriteWindow::DWriteWindow(std::wstring& text) : m_text{text}, BaseWindow{ L"DWrite window" }
{
	THROW_IF_FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, d2dFactory.put()));
	THROW_IF_FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE::DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory), dwriteFactory.put_unknown()));


	THROW_IF_FAILED(dwriteFactory->CreateTextFormat(
		TEXT("Microsoft YaHei"),
		nullptr,
		DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL,
		56.f,
		L"",
		textFormat.put()
	));
	THROW_IF_FAILED(textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER));

	auto const clientRect = ClientRect();
	THROW_IF_FAILED(d2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hwnd.get(), D2D1::SizeU(clientRect.right, clientRect.bottom)),
		m_renderTarget.put()
	));
	THROW_IF_FAILED(m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), m_textBrush.put()));
}

void DWriteWindow::OnSize(HWND hwnd, WPARAM wparam, UINT width, UINT height)
{
	if (auto renderTarget = getSelfFromHwnd(hwnd)->m_renderTarget)
	{
		THROW_IF_FAILED(renderTarget->Resize(D2D1::SizeU(width, height)));
	}
}

void DWriteWindow::OnPaint(HWND hwnd)
{

	auto self = getSelfFromHwnd(hwnd);
	//auto const clientRect = self->ClientRect();

	auto renderTargetSize = self->m_renderTarget->GetSize();

	self->m_renderTarget->BeginDraw();
	self->m_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	self->m_renderTarget->DrawTextW(
		self->m_text.data(),
		self->m_text.size(),
		self->textFormat.get(),
		//D2D1::RectF(0, 0, clientRect.right, clientRect.bottom),
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		self->m_textBrush.get()
	);

	THROW_IF_FAILED(self->m_renderTarget->EndDraw());
	THROW_IF_WIN32_BOOL_FALSE(ValidateRect(hwnd, nullptr));
}
