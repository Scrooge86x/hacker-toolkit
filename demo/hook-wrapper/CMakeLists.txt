add_executable(hook_wrapper main.cpp)
add_subdirectory(minhook)
target_link_libraries(hook_wrapper
    PRIVATE
        hackertoolkit
        minhook
)
