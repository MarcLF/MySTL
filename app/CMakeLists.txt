add_executable(MySTLApp main.cpp)

set_target_properties(MySTLApp PROPERTIES CXX_SCAN_FOR_MODULES ON)
target_link_libraries(MySTLApp PRIVATE MySTL)

add_dependencies(MySTLApp MySTL)

if(MSVC)
    target_compile_options(MySTLApp PRIVATE /std:c++23 /EHsc)
endif()