#define WIN32_LEAN_AND_MEAN
#include <hackertoolkit/win32-console.h>

#include <thread>
#include <chrono>
#include <iostream>

int WINAPI WinMain(
    _In_ ::HINSTANCE hInstance, _In_opt_ ::HINSTANCE hPrevInstance,
    _In_ ::LPSTR lpCmdLine, _In_ int nCmdShow
) {
    using namespace std::chrono_literals;
    {
        htk::Win32Console console{};
        std::cout << "Console #1\n";
        std::this_thread::sleep_for(2s);
    }
    std::this_thread::sleep_for(1s);
    {
        htk::Win32Console console{};
        std::cout << "Console #2\n";
        std::this_thread::sleep_for(2s);
    }
    return 0;
}
