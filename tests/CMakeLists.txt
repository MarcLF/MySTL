find_package(boost_unit_test_framework CONFIG REQUIRED)

add_executable(unit_tests test_vector.cpp)

target_link_libraries(unit_tests 
    PRIVATE 
    MySTL 
    Boost::unit_test_framework
)

add_dependencies(unit_tests MySTL)

set_target_properties(unit_tests PROPERTIES CXX_SCAN_FOR_MODULES ON)

add_test(NAME VectorTests COMMAND unit_tests)