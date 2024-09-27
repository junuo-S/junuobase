#include "winfunc.h"

#include <TlHelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include <winver.h>
#include <sstream>

#include "src/utils/stringconvert.h"

#pragma comment(lib, "version")

JUNUO_BEGIN_NAMESPACE_(junuobase)
JUNUO_BEGIN_NAMESPACE_(utils)
JUNUO_BEGIN_NAMESPACE_(win)

using namespace junuobase::utils::str;

JUNUO_BASE_EXPORT DWORD GetProcessIdByName(const char* pName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
		return NULL;
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe))
	{
		std::unique_ptr<wchar_t[], void(*)(wchar_t*)> pNameW(CharToWChar(pName), [](wchar_t* ptr) { delete[] ptr; });
		if (wcscmp(CharToWChar(pe.szExeFile), pNameW.get()) == 0)
		{
			CloseHandle(hSnapshot);
			return pe.th32ProcessID;
		}
	}
	CloseHandle(hSnapshot);
	return NULL;
}

JUNUO_BASE_EXPORT DWORD_PTR GetModuleAddress(const char* processName, const char* dllName)
{
	DWORD targetProcessId = GetProcessIdByName(processName);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, targetProcessId);
	if (hProcess == NULL)
		return NULL;

	HMODULE hModules[1024];
	DWORD cbNeeded;
	EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded);
	for (int i = 0; i < cbNeeded / sizeof(HMODULE); i++)
	{
		TCHAR szModuleName[MAX_PATH];
		GetModuleBaseName(hProcess, hModules[i], szModuleName, sizeof(szModuleName) / sizeof(TCHAR));
		std::unique_ptr<wchar_t[], void(*)(wchar_t*)> dllNameW(CharToWChar(dllName), [](wchar_t* ptr) { delete[] ptr; });
		if (wcscmp(CharToWChar(szModuleName), dllNameW.get()) == 0)
		{
			DWORD_PTR baseAddress = (DWORD_PTR)hModules[i];
			return baseAddress;
		}
	}
	return NULL;
}

JUNUO_BASE_EXPORT std::wstring GetProcessName(DWORD processId)
{
	std::wstring processName;
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
	if (hProcess != NULL)
	{
		TCHAR buffer[MAX_PATH];
		if (GetModuleFileNameEx(hProcess, NULL, buffer, MAX_PATH))
			processName = TCHARToWString(buffer);
		CloseHandle(hProcess);
	}
	return processName;
}

JUNUO_BASE_EXPORT std::wstring GetExecutablePath(DWORD processId)
{
	std::wstring executablePath;
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
	if (hProcess == NULL)
		return executablePath;
	HMODULE hModule;
	DWORD cbNeeded;
	if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &cbNeeded))
	{
		WCHAR szProcessPath[MAX_PATH];
		if (GetModuleFileNameExW(hProcess, hModule, szProcessPath, MAX_PATH))
			executablePath = szProcessPath;
	}
	CloseHandle(hProcess);
	return executablePath;
}

JUNUO_BASE_EXPORT std::wstring GetExecutablePath(const char* processName)
{
	DWORD processId = GetProcessIdByName(processName);
	return GetExecutablePath(processId);
}

JUNUO_BASE_EXPORT std::string GetFileVersion(const wchar_t* fileName)
{
	std::string version;
	VS_FIXEDFILEINFO* pVsInfo;
	unsigned int iFileInfoSize = sizeof(VS_FIXEDFILEINFO);
	int iVerInfoSize = GetFileVersionInfoSizeW(fileName, NULL);
	if (iVerInfoSize == 0)
		return version;
	char* pBuf = new char[iVerInfoSize];
	if (!pBuf)
		return version;
	if (GetFileVersionInfoW(fileName, 0, iVerInfoSize, pBuf))
	{
		if (VerQueryValueA(pBuf, "\\", (void**)&pVsInfo, &iFileInfoSize))
		{
			sprintf(pBuf, "%d.%d.%d.%d", HIWORD(pVsInfo->dwFileVersionMS), LOWORD(pVsInfo->dwFileVersionMS), HIWORD(pVsInfo->dwFileVersionLS), LOWORD(pVsInfo->dwFileVersionLS));
			version = pBuf;
		}
	}
	delete[]pBuf;
	return version;
}

JUNUO_BASE_EXPORT std::wstring GetCurrentMoudlePath()
{
	HMODULE hModule = GetModuleHandle(NULL);
	std::wstring path;
	if (hModule != NULL)
	{
		WCHAR szPath[MAX_PATH];
		DWORD length = GetModuleFileNameW(hModule, szPath, MAX_PATH);
		if (length)
			path = szPath;
	}
	int index = path.find_last_of('\\');
	if (index == -1)
		index = path.find_last_of('/');
	if (index == -1)
		return std::wstring();
	return path.substr(0, index);
}

JUNUO_BASE_EXPORT BOOL IsWx64BitExecutable(const std::wstring& exePath)
{
	DWORD binaryType;
	if (GetBinaryTypeW(exePath.c_str(), &binaryType))
		return binaryType == SCS_64BIT_BINARY;
	return false;
}

JUNUO_BASE_EXPORT BOOL IsMemoryPageWritable(void* address)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQuery(address, &mbi, sizeof(mbi)))
	{
		return (mbi.Protect & PAGE_READWRITE) || (mbi.Protect & PAGE_WRITECOPY) ||
			(mbi.Protect & PAGE_EXECUTE_READWRITE) || (mbi.Protect & PAGE_EXECUTE_WRITECOPY);
	}
	return false;
}

JUNUO_BASE_EXPORT BOOL IsAddressInProcess(HANDLE hProcess, LPCVOID lpAddress)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQueryEx(hProcess, lpAddress, &mbi, sizeof(mbi)))
		return mbi.AllocationBase != nullptr;
	return FALSE;
}

JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
JUNUO_END_NAMESPACE
