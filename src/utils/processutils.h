#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <string>

#include <junuobase/junuoglobal.h>

#include "global.h"

JUNUO_BEGIN_NAMESPACE_(junuobase)
JUNUO_BEGIN_NAMESPACE_(utils)

JUNUO_BASE_EXPORT DWORD GetProcessIdByName(const wchar_t* pName);
JUNUO_BASE_EXPORT DWORD_PTR GetModuleAddress(const wchar_t* processName, const wchar_t* dllName);
JUNUO_BASE_EXPORT std::wstring GetProcessName(DWORD processId);
JUNUO_BASE_EXPORT std::wstring GetExecutablePath(DWORD processId);
JUNUO_BASE_EXPORT std::wstring GetExecutablePath(const wchar_t* processName);
JUNUO_BASE_EXPORT std::string GetFileVersion(const wchar_t* fileName);
JUNUO_BASE_EXPORT std::wstring GetCurrentMoudlePath();
JUNUO_BASE_EXPORT BOOL IsWx64BitExecutable(const std::wstring& exePath);
JUNUO_BASE_EXPORT BOOL IsMemoryPageWritable(void* address);
JUNUO_BASE_EXPORT BOOL IsAddressInProcess(HANDLE hProcess, LPCVOID lpAddress);

JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
