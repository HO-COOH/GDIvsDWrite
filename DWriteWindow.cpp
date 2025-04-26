#include "DWriteWindow.h"

DWriteWindow::DWriteWindow(std::wstring& text) : m_text{text}, BaseWindow{L"DWrite Window"}
{
}
