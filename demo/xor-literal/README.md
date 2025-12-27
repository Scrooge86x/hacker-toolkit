# xor-literal

Obfuscation of string literals during compile time.
It can make reverse engineering your program harder.

You can check yourself that it works on [compiler explorer](https://godbolt.org/z/5nx4MWM1E).

I've only seen implementations that use macros for this, 
so I've decided to make a better version that makes use of c++20 
[string literal operator template](https://en.cppreference.com/w/cpp/language/user_literal.html)
without any macros involved.
