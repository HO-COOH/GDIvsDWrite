#include <Windows.h>
#include "GDIWindow.h"
#include "DWriteWindow.h"
#include "UWPWindow.h"
#include <wil/result_macros.h>
#include "WinUI3Window.h"
#include "SettingsWindow.h"

static auto getPrimaryMonitorRect()
{
	MONITORINFO info{ .cbSize = sizeof(info) };
	winrt::check_bool(GetMonitorInfo(MonitorFromPoint({}, MONITOR_DEFAULTTOPRIMARY), &info));
	return info.rcWork;
}

int main()
{
	THROW_IF_WIN32_BOOL_FALSE(SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2));
	winrt::init_apartment(winrt::apartment_type::single_threaded);
	
	winrt::hstring text{ L"微软雅黑" };


	//WinUI3 window must be created before UWP window
	WinUI3Window winui3Window{ text };
	SettingsWindow settings;
	GDIWindow gdiWindow{ text };
	DWriteWindow dwriteWindow{ text};
	UWPWindow uwpWindow{ text };

	settings << gdiWindow << dwriteWindow << uwpWindow << winui3Window;

	//Set all display windows to 4 quadrants
	auto const monitorRect = getPrimaryMonitorRect();
	auto const halfWidth = (monitorRect.right - monitorRect.left) / 2;
	auto const halfHeight = (monitorRect.bottom - monitorRect.top) / 2;
	
	gdiWindow.SetPosition(0, 0, halfWidth, halfHeight, 0);
	dwriteWindow.SetPosition(halfWidth, 0, halfWidth, halfHeight, 0);
	uwpWindow.SetPosition(0, halfHeight, halfWidth, halfHeight, 0);
	winui3Window.SetPosition(halfWidth, halfHeight, halfWidth, halfHeight, 0);
	settings.SetPosition((monitorRect.right - monitorRect.left - halfWidth) / 2, (monitorRect.bottom - monitorRect.top) / 2 + 200, halfWidth, (monitorRect.bottom - monitorRect.top) / 3, 0);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
