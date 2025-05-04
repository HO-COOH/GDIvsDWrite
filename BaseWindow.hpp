#pragma once
#include <wil/resource.h>
#include <string_view>

template<size_t N>
struct StringLiteral {
	constexpr StringLiteral(const wchar_t(&str)[N]) {
		std::copy_n(str, N, value);
	}

	wchar_t value[N];
};

template<typename T, StringLiteral className>
class BaseWindow
{
	static void OnPaint(HWND) {}
protected:
	wil::unique_hwnd m_hwnd;

	[[nodiscard]] static auto getSelfFromHwnd(HWND const window)
	{
		return reinterpret_cast<T*>(GetWindowLongPtr(window, GWLP_USERDATA));
	}

	static void OnNCCreate(HWND hwnd, CREATESTRUCT* lparam)
	{
	}

	static void OnSize(HWND hwnd, WPARAM wparam, UINT width, UINT height)
	{
	}

	static void OnDpiChanged(HWND, WORD dpiX, WORD dpiY, RECT* suggestPosition)
	{
	}

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
			//Methods that have default (no-op) implementation
			case WM_DPICHANGED:
				OnDpiChanged(hwnd, LOWORD(wparam), HIWORD(wparam), reinterpret_cast<RECT*>(lparam));
				break;
			case WM_NCCREATE: 
				OnNCCreate(hwnd, reinterpret_cast<CREATESTRUCT*>(lparam));
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			
			//Methods that must be implemented by derived class 
			case WM_PAINT:
				T::OnPaint(hwnd);
				return 0;
			case WM_SIZE:
				T::OnSize(hwnd, wparam, LOWORD(lparam), HIWORD(lparam));
				return 0;
			default:
				break;
		}
		return DefWindowProcW(hwnd, msg, wparam, lparam);
	}

public:
	BaseWindow(std::wstring_view windowName, DWORD exStyle = 0, DWORD style = WS_OVERLAPPEDWINDOW, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT)
	{
		static auto windowClass = [] {
			WNDCLASS wc
			{
				.style = CS_HREDRAW | CS_VREDRAW,
				.lpfnWndProc = WndProc,
				.cbWndExtra = sizeof(void*),
				.lpszClassName = className.value,
			};
			RegisterClass(&wc);
			return wc;
		}();

		auto const hwnd = CreateWindowExW(
			exStyle,
			className.value,
			windowName.data(),
			style,
			x,
			y,
			cx,
			cy,
			nullptr,
			nullptr,
			nullptr,
			static_cast<T*>(this)
		);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(static_cast<T*>(this)));

		ShowWindow(hwnd, SW_SHOW);
		m_hwnd.reset(hwnd);
	}

	RECT ClientRect() const
	{
		RECT clientRect;
		THROW_IF_WIN32_BOOL_FALSE(GetClientRect(m_hwnd.get(), &clientRect));
		return clientRect;
	}

	UINT GetDpi() const
	{
		return GetDpiForWindow(m_hwnd.get());
	}

	auto SetPosition(int x, int y, int cx, int cy, UINT flags) const
	{
		auto const result = SetWindowPos(m_hwnd.get(), HWND_TOP, x, y, cx, cy, flags);
		InvalidateRect(m_hwnd.get(), nullptr, true);
		UpdateWindow(m_hwnd.get());
		return result;
	}
};
