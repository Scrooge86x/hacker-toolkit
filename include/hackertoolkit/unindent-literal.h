#pragma once

#ifndef HTK_UNINDENT_LITERAL
#define HTK_UNINDENT_LITERAL

#include <cstddef>

namespace htk {

template <std::size_t t_size>
class UnindentedString {
public:
    std::size_t size{};
    char data[t_size]{};

    consteval UnindentedString(const char(&text)[t_size]) {
        const std::size_t minIndentation{ getMinIndentation(text) };

        std::size_t charactersToSkip{ minIndentation };
        char* pData{ data };
        const char* pText{ text[0] == '\n' ? text + 1 : text };

        while (*pText) {
            switch (*pText) {
            case '\n':
                charactersToSkip = minIndentation;
                *pData++ = *pText++;
                ++size;
                break;
            case ' ':
            case '\t':
                if (!charactersToSkip) {
                    *pData++ = *pText++;
                    ++size;
                } else {
                    ++pText;
                    --charactersToSkip;
                }
                break;
            default:
                charactersToSkip = 0;
                *pData++ = *pText++;
                ++size;
                break;
            }
        }

        if (pData[-1] == '\n') {
            pData[-1] = '\0';
        } else {
            *pData = '\0';
            ++size;
        }
    }

    template <std::size_t OtherN>
    constexpr UnindentedString(const UnindentedString<OtherN>& other)
        : size{ other.size } {
        for (std::size_t i{}; i < t_size; ++i) {
            data[i] = other[i];
        }
    }

    constexpr operator const char* () const noexcept {
        return data;
    }

    consteval std::size_t getMinIndentation(const char* text) noexcept {
        std::size_t minIndentation{ static_cast<std::size_t>(-1) };
        std::size_t currentIndentation{};

        bool isIndentation{ true };
        while (*text) {
            switch (*text++) {
            case '\n':
                isIndentation = true;
                currentIndentation = 0;
                break;
            case ' ':
            case '\t':
                ++currentIndentation;
                break;
            default:
                if (!isIndentation) {
                    break;
                }

                isIndentation = false;
                if (currentIndentation <= minIndentation) {
                    minIndentation = currentIndentation;
                }
                break;
            }
        }
        return minIndentation;
    }
};

}

template <htk::UnindentedString Str>
[[nodiscard]] constexpr htk::UnindentedString<Str.size> operator""_unindent() {
    return Str;
}

#endif // HTK_UNINDENT_LITERAL
