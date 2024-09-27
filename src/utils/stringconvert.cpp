#include "stringconvert.h"

JUNUO_BEGIN_NAMESPACE_(junuobase)
JUNUO_BEGIN_NAMESPACE_(utils)
JUNUO_BEGIN_NAMESPACE_(str)

JUNUO_BASE_EXPORT std::wstring TCHARToWString(const TCHAR* tchar)
{
	std::wstringstream wss;
	wss << tchar;
	return wss.str();
}

JUNUO_BASE_EXPORT wchar_t* CharToWChar(const char* charArray)
{
	if (!charArray)
		return nullptr;
	size_t size_needed = std::mbstowcs(nullptr, charArray, 0) + 1;
	wchar_t* wCharArray = new wchar_t[size_needed];
	std::mbstowcs(wCharArray, charArray, size_needed);
	return wCharArray;
}

JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
