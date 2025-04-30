#include <Windows.h>
#include "GDIWindow.h"
#include "DWriteWindow.h"
#include "UWPWindow.h"
#include <wil/result_macros.h>
#include "WinUI3Window.h"

int main()
{
	THROW_IF_WIN32_BOOL_FALSE(SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2));
	winrt::init_apartment(winrt::apartment_type::single_threaded);
	
	std::wstring text{ L"微软雅黑" };


	//WinUI3 window must be created before UWP window
	WinUI3Window winui3Window{ text };
	GDIWindow gdiWindow{ text };
	DWriteWindow dwriteWindow{ text };
	UWPWindow uwpWindow{ text };

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
