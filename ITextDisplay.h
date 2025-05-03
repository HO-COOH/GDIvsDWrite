#pragma once
namespace winrt
{
	struct hstring;
}

struct ITextDisplay
{
	virtual void SetText(winrt::hstring const& text) = 0;
	virtual void SetFontSize(int fontSize) = 0;
	virtual void SetFontFamily(winrt::hstring const& fontFamily) = 0;
};
