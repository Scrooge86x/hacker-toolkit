#define WIN32_LEAN_AND_MEAN
#include <hackertoolkit/win32-process.h>

#include <iostream>

int main() {
    ::PROCESSENTRY32 explorerProcess{ htk::getProcessEntry("explorer.exe") };
    if (!explorerProcess.dwSize) {
        return 1;
    }

    std::cout << "explorer.exe pid: " << explorerProcess.th32ProcessID << '\n';

    ::MODULEENTRY32 user32Module{ htk::getModuleEntry("user32.dll", explorerProcess.th32ProcessID) };
    if (!user32Module.dwSize) {
        return 1;
    }

    std::cout << "user32.dll full path: " << user32Module.szExePath << '\n';

    return 0;
}
