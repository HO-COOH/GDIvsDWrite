#pragma once
#include <string>
#include <wil/com.h>
#include "BaseWindow.hpp"

struct ID2D1HwndRenderTarget;

class DWriteWindow : public BaseWindow<DWriteWindow>
{
	std::wstring& m_text;
	wil::com_ptr<ID2D1HwndRenderTarget> m_renderTarget;
public:
	DWriteWindow(std::wstring& text);
};

