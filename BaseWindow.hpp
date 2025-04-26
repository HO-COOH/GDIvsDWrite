#pragma once
#include <wil/resource.h>
#include <string_view>

template<typename T>
class BaseWindow
{
	static void OnPaint(HWND) {}
	constexpr static auto className = L"MyWindow";
protected:
	wil::unique_hwnd m_hwnd;

	static auto getSelfFromHwnd(HWND const window)
	{
		return reinterpret_cast<T*>(GetWindowLongPtr(window, GWLP_USERDATA));
	}

	static void OnNCCreate(HWND hwnd, CREATESTRUCT* lparam)
	{
		auto self = reinterpret_cast<T*>(lparam->lpCreateParams);
		self->m_hwnd.reset(hwnd);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(static_cast<T*>(self)));
	}

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
			case WM_NCCREATE: 
				OnNCCreate(hwnd, reinterpret_cast<CREATESTRUCT*>(lparam));
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_PAINT:
				T::OnPaint(hwnd);
				return 0;
			default:
				break;
		}
		return DefWindowProcW(hwnd, msg, wparam, lparam);
	}

public:
	BaseWindow(std::wstring_view windowName)
	{
		static auto windowClass = [] {
			WNDCLASS wc
			{
				.style = CS_HREDRAW | CS_VREDRAW,
				.lpfnWndProc = WndProc,
				.cbWndExtra = sizeof(void*),
				.lpszClassName = className,
			};
			RegisterClass(&wc);
			return wc;
			}();

		CreateWindowW(
			className,
			windowName.data(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			nullptr,
			this
		);

		ShowWindow(m_hwnd.get(), SW_SHOW);
	}
};
