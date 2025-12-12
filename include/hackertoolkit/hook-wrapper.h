#pragma once

#ifndef HOOK_WRAPPER
#define HOOK_WRAPPER

// Remember that HookWrapper must be defined globally
// or as a static variable in order to call its methods
// inside of lambdas

namespace htk {

template <typename T>
struct HookWrapper {
    static_assert(
        sizeof(T) == 0,
        "HookWrapper requires a function type as a template parameter. "
        "For example HookWrapper<void(int, double)> or HookWrapper<int()>."
        );
};

template <typename ReturnType, typename... Args>
struct HookWrapper<ReturnType(Args...)> {
public:
    using FnType = ReturnType(*)(Args...);

    FnType hooked{};
    FnType original{};
};

}

#endif // HOOK_WRAPPER
