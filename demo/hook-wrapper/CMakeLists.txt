add_subdirectory(minhook)

add_executable(htk_hook_wrapper main.cpp)
target_link_libraries(htk_hook_wrapper
    PRIVATE
        hackertoolkit
        minhook
)
