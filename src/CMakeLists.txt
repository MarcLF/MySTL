add_library(MySTL)

set_target_properties(MySTL PROPERTIES CXX_SCAN_FOR_MODULES ON)

target_sources(MySTL
    PUBLIC
    FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
        "MySTL.ixx"             
        containers/vector.ixx  
)

if(MSVC)
    target_compile_options(MySTL PRIVATE 
        /std:c++latest
        /EHsc 
        /W4 
        /permissive-
        /Zc:preprocessor
    )
endif()