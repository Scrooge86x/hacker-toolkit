#pragma once

#ifndef HTK_DEFER

#include <type_traits>

#define DEFER_NAME2(x, y) x##y
#define DEFER_NAME(x, y) DEFER_NAME2(x, y)
#define HTK_DEFER const htk::detail::Defer DEFER_NAME(deferBlock, __COUNTER__) = [&]() -> void

namespace htk {
namespace detail {

template <typename Lambda>
requires (
    std::is_class_v<Lambda>
    && requires { &Lambda::operator(); }
    && std::is_same_v<void, std::invoke_result_t<Lambda>>
    && !std::is_default_constructible_v<Lambda>
)
class Defer {
public:
    Defer(const Lambda lambda)
        : m_lambda{ lambda } {}

    ~Defer() {
        m_lambda();
    }

    Defer(const Defer&) = delete;
    Defer& operator=(const Defer&) = delete;
    Defer(Defer&&) = delete;
    Defer& operator=(Defer&&) = delete;

private:
    const Lambda m_lambda{};
};

}
}

#endif // HTK_DEFER
