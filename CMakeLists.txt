cmake_minimum_required(VERSION 3.30)

project(hackertoolkit)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(hackertoolkit INTERFACE)
target_include_directories(hackertoolkit INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(HACKERTOOLKIT_BUILD_ALL_DEMOS "Build all demos" OFF)
option(HACKERTOOLKIT_BUILD_XOR_LITERAL "Build xor-literal demo" OFF)

if (HACKERTOOLKIT_BUILD_ALL_DEMOS)
    set(HACKERTOOLKIT_BUILD_XOR_LITERAL ON CACHE BOOL "Build hello-world demo" FORCE)
endif ()

if (HACKERTOOLKIT_BUILD_XOR_LITERAL)
    add_subdirectory(demo/xor-literal)
endif ()
