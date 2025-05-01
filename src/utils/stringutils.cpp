#include "stringutils.h"

JUNUO_BEGIN_NAMESPACE_(junuobase)
JUNUO_BEGIN_NAMESPACE_(utils)

JUNUO_BASE_EXPORT std::wstring TCHARToWString(const TCHAR* tchar)
{
	std::wstringstream wss;
	wss << tchar;
	return wss.str();
}

JUNUO_BASE_EXPORT bool CharToWChar(const char* charArray, wchar_t* wcharArray, size_t length)
{
	if (!charArray || !wcharArray || length <= 0)
		return false;
	const char* charBegin = charArray;
	for (size_t current = 0; current < length && *charArray != 0; current++, charArray++, wcharArray++)
		*wcharArray = *charArray;
	*wcharArray = 0;
	return true;
}

JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
