#pragma once
#include <string>
#include "IslandWindow.h"

class UWPWindow : public IslandWindow
{
	std::wstring& m_text;
	wil::unique_hwnd islandHwmd;

public:
	UWPWindow(std::wstring& text);
};

