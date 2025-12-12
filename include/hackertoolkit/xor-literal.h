#pragma once

#ifndef XOR_LITERAL
#define XOR_LITERAL

#include <cstddef>

namespace htk {

template <std::size_t t_size>
class XorString {
public:
    std::size_t size{ t_size };
    char data[t_size]{};

    consteval XorString(const char(&text)[t_size]) {
        for (std::size_t i{}; i < t_size; ++i) {
            data[i] = text[i] ^ s_xorKey[i % sizeof(s_xorKey)];
        }
    }

    operator const char* () noexcept {
        for (std::size_t i{}; i < t_size; ++i) {
            data[i] = data[i] ^ s_xorKey[i % sizeof(s_xorKey)];
        }
        return data;
    }

private:
    static constexpr char s_xorKey[]{
        __TIME__[3], __TIME__[7],
        __TIME__[6], __TIME__[0],
        __TIME__[4], __TIME__[1],
    };
};

}

template <htk::XorString t_xorStr>
[[nodiscard]] htk::XorString<t_xorStr.size> operator""_xor() {
    return t_xorStr;
}

#endif // XOR_LITERAL
