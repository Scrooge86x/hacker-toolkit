#pragma once

#ifndef HTK_WIN32_CONSOLE
#define HTK_WIN32_CONSOLE

#pragma once

#include <Windows.h>
#include <cstdio>
#include <utility>

namespace htk {

class Win32Console {
public:
    Win32Console() {
        if (!::AllocConsole()) {
            return;
        }

#ifdef _MSC_VER
#pragma warning(push)
// Disable the warning because as of c++20 freopen_s is not a part of <cstdio>
#pragma warning(disable : 4996) // 'freopen': This function or variable may be unsafe. Consider using freopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif
        m_stdoutFile = std::freopen("CONOUT$", "w", stdout);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    }

    ~Win32Console() {
        if (m_stdoutFile) {
            std::fclose(m_stdoutFile);
            ::FreeConsole();
        }
    }

    Win32Console(const Win32Console&) = delete;
    Win32Console& operator=(const Win32Console&) = delete;

    Win32Console(Win32Console&& other) noexcept
        : m_stdoutFile{ std::exchange(other.m_stdoutFile, nullptr) }
    {}

    Win32Console& operator=(Win32Console&& other) noexcept {
        if (m_stdoutFile) {
            std::fclose(m_stdoutFile);
        }
        m_stdoutFile = std::exchange(other.m_stdoutFile, nullptr);
    }

private:
    FILE* m_stdoutFile{};
};

}

#endif // HTK_WIN32_CONSOLE
