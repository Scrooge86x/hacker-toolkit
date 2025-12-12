#pragma once

#ifndef HTK_CONSOLE
#define HTK_CONSOLE

#pragma once

#include <cstdio>
#include <utility>

namespace htk {

class Win32Console {
public:
    Win32Console() {
        ::AllocConsole();
        freopen_s(&m_stdoutFile, "CONOUT$", "w", stdout);
    }

    ~Win32Console() {
        if (m_stdoutFile) {
            fclose(m_stdoutFile);
        }
        ::FreeConsole();
    }

    Win32Console(const Win32Console&) = delete;
    Win32Console& operator=(const Win32Console&) = delete;

    Win32Console(Win32Console&& other) noexcept
        : m_stdoutFile{ std::exchange(other.m_stdoutFile, nullptr) } {}

    Win32Console& operator=(Win32Console&& other) noexcept {
        m_stdoutFile = std::exchange(other.m_stdoutFile, nullptr);
    }

private:
    FILE* m_stdoutFile{};
};

}

#endif // HTK_CONSOLE
