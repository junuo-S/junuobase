#pragma once

#include <string>
#include <sstream>
#include <tchar.h>

#include <src/global.h>
#include <junuobase/junuoglobal.h>

JUNUO_BEGIN_NAMESPACE_(junuobase)
JUNUO_BEGIN_NAMESPACE_(utils)
JUNUO_BEGIN_NAMESPACE_(str)

JUNUO_BASE_EXPORT std::wstring TCHARToWString(const TCHAR* tchar);
JUNUO_BASE_EXPORT wchar_t* CharToWChar(const char* charArray);

JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
