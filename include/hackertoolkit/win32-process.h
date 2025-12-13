#pragma once

#ifndef HTK_WIN32_PROCESS
#define HTK_WIN32_PROCESS

#include <TlHelp32.h>
#include <string_view>

namespace htk {

::PROCESSENTRY32 getProcessEntry(const std::string_view processName) {
    ::PROCESSENTRY32 processEntry{ .dwSize{ sizeof(::PROCESSENTRY32) } };
    ::HANDLE hProcessSnapshot{ ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL) };
    if (hProcessSnapshot == INVALID_HANDLE_VALUE) {
        return {};
    }

    if (!::Process32First(hProcessSnapshot, &processEntry)) {
        ::CloseHandle(hProcessSnapshot);
        return {};
    }

    do {
        if (processName == processEntry.szExeFile) {
            ::CloseHandle(hProcessSnapshot);
            return processEntry;
        }
    } while (::Process32Next(hProcessSnapshot, &processEntry));

    ::CloseHandle(hProcessSnapshot);
    return {};
}

::MODULEENTRY32 getModuleEntry(const std::string_view moduleName, const ::DWORD processId) {
    ::MODULEENTRY32 moduleEntry{ .dwSize{ sizeof(::MODULEENTRY32) } };
    ::HANDLE hModuleSnapshot{ ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId) };
    if (hModuleSnapshot == INVALID_HANDLE_VALUE) {
        return {};
    }

    if (!::Module32First(hModuleSnapshot, &moduleEntry)) {
        ::CloseHandle(hModuleSnapshot);
        return {};
    }

    do {
        if (moduleName == moduleEntry.szModule) {
            ::CloseHandle(hModuleSnapshot);
            return moduleEntry;
        }
    } while (::Module32Next(hModuleSnapshot, &moduleEntry));

    ::CloseHandle(hModuleSnapshot);
    return {};
}

}

#endif // HTK_WIN32_PROCESS
