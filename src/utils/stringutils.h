#pragma once

#include <string>
#include <sstream>

#ifdef _WIN32
#include <tchar.h>
#endif

#include <junuobase/junuoglobal.h>

#ifndef JUNUO_BASE_EXPORT
#	ifdef JUNUO_BASE_MODULE
#		define JUNUO_BASE_EXPORT __declspec(dllexport)
#	else
#		define JUNUO_BASE_EXPORT __declspec(dllimport)
#	endif
#endif

JUNUO_BEGIN_NAMESPACE_(junuobase)
JUNUO_BEGIN_NAMESPACE_(utils)

JUNUO_BASE_EXPORT std::wstring TCHARToWString(const TCHAR* tchar);
JUNUO_BASE_EXPORT bool CharToWChar(const char* charArray, wchar_t* wcharArray, size_t length);

JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
