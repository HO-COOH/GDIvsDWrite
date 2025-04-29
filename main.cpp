#include <Windows.h>
#include "GDIWindow.h"
#include "DWriteWindow.h"
#include "UWPWindow.h"
#include <wil/result_macros.h>

int main()
{
	THROW_IF_WIN32_BOOL_FALSE(SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2));
	
	std::wstring text{ L"微软雅黑" };

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
