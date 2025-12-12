#include <hackertoolkit/hook-wrapper.h>
#include <minhook.h>
#include <cstdio>
#include <iostream>

HookWrapper<decltype(std::puts)> g_putsHook{
    [](const char*) -> int {
        return g_putsHook.original("Hooked!");
    }
};

static int demoPutsHook() {
    if (MH_CreateHook(&std::puts, g_putsHook.hooked,
                      reinterpret_cast<LPVOID*>(&g_putsHook.original)) != MH_OK) {
        return 1;
    }

    std::puts("[1] Hello World!");

    if (MH_EnableHook(&std::puts) != MH_OK) {
        return 1;
    }

    std::puts("[2] Hello World!");

    if (MH_DisableHook(&std::puts) != MH_OK) {
        return 1;
    }

    std::puts("[3] Hello World!");
    return 0;
}

static int get10() {
    std::cout << "Returning 10...\n";
    return 10;
}

static int demoGet10Hook() {
    static HookWrapper<int()> getValueHook{
        []() -> int {
            getValueHook.original();
            return 999;
        }
    };

    if (MH_CreateHook(&get10, getValueHook.hooked,
                      reinterpret_cast<LPVOID*>(&getValueHook.original)) != MH_OK) {
        return 1;
    }

    std::cout << get10() << '\n';

    if (MH_EnableHook(&get10) != MH_OK) {
        return 1;
    }

    std::cout << get10() << '\n';

    if (MH_DisableHook(&get10) != MH_OK) {
        return 1;
    }

    std::cout << get10() << '\n';
    return 0;
}

int main() {
    if (MH_Initialize() != MH_OK) {
        return 1;
    }

    if (demoPutsHook()) {
        return 1;
    }

    std::cout << "\n-----\n\n";

    if (demoGet10Hook()) {
        return 1;
    }

    if (MH_Uninitialize() != MH_OK) {
        return 1;
    }

    return 0;
}
