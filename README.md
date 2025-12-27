# Hacker Toolkit

This is a collection of utilities that have been useful to me while writing cheats.

It's doesn't strictly contain only hacking related utilities, but ones that were useful for me multiples times.

## How to use

The easiest way is to just copy and paste the header you want into your project.
The headers don't depend on each other and can be used separately without any issues.

If you prefer using cmake you can just add the library directory
```cmake
add_subdirectory(hacker-toolkit)
```

and then link the `hackertoolkit` target, for example:
```cmake
target_link_libraries(your-project PRIVATE hackertoolkit)
```

This will allow you to include the libraries using `#include <hackertoolkit/*>`, for example
```cpp
#include <hackertoolkit/xor-literal.h>
```

### Warning

The headers that use <Windows.h> **DO NOT** define `WIN32_LEAN_AND_MEAN` you might want to do it yourself.

## Project Structure

This library is header only because it contains a lot of templated code.

The most important directory for you is [include/hackertoolkit](include/hackertoolkit) which contains the actual headers.
For every header there is a matching directory located in the [demo](demo/).

For example if you want to learn how to use [htk::HookWrapper](include/hackertoolkit/hook-wrapper.h)
you would go to [demo/hook-wrapper](demo/hook-wrapper) where you will find a standalone example.

By default no demos will get built, you can enable them all by setting:
```cmake
set(HACKERTOOLKIT_BUILD_ALL_DEMOS ON CACHE BOOL "" FORCE)
```

or a specific one, for example:
```cmake
set(HACKERTOOLKIT_BUILD_XOR_LITERAL ON CACHE BOOL "" FORCE)
```

they all follow the same naming conventions, so you'll figure it out,
otherwise you can find them in the [main CMakeLists.txt](CMakeLists.txt)
