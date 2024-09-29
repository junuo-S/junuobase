#pragma once

#ifndef JUNUO_BASE_EXPORT
#	ifdef JUNUO_BASE_MODULE
#		define JUNUO_BASE_EXPORT __declspec(dllexport)
#	else
#		define JUNUO_BASE_EXPORT __declspec(dllimport)
#	endif
#endif

#include <windows.h>
#include <string>

#include <junuobase/junuoglobal.h>

JUNUO_BEGIN_NAMESPACE_(junuobase)
JUNUO_BEGIN_NAMESPACE_(utils)
JUNUO_BEGIN_NAMESPACE_(win)

JUNUO_BASE_EXPORT DWORD GetProcessIdByName(const char* pName);
JUNUO_BASE_EXPORT DWORD_PTR GetModuleAddress(const char* processName, const char* dllName);
JUNUO_BASE_EXPORT std::wstring GetProcessName(DWORD processId);
JUNUO_BASE_EXPORT std::wstring GetExecutablePath(DWORD processId);
JUNUO_BASE_EXPORT std::wstring GetExecutablePath(const char* processName);
JUNUO_BASE_EXPORT std::string GetFileVersion(const wchar_t* fileName);
JUNUO_BASE_EXPORT std::wstring GetCurrentMoudlePath();
JUNUO_BASE_EXPORT BOOL IsWx64BitExecutable(const std::wstring& exePath);
JUNUO_BASE_EXPORT BOOL IsMemoryPageWritable(void* address);
JUNUO_BASE_EXPORT BOOL IsAddressInProcess(HANDLE hProcess, LPCVOID lpAddress);

JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
