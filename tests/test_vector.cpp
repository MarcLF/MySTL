#define BOOST_TEST_MODULE VectorTests
#include <boost/test/unit_test.hpp>

import std;
import mystl;

BOOST_AUTO_TEST_SUITE(VectorBasicTests)

BOOST_AUTO_TEST_CASE(test_vector_initialization)
{
    mystl::vector<int> v;
    BOOST_TEST(v.size() == 0);
    BOOST_TEST(v.empty() == true);
}

BOOST_AUTO_TEST_CASE(test_vector_push_back)
{
    mystl::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    BOOST_TEST(v.size() == 3);
    BOOST_TEST(v.empty() == false);

    BOOST_TEST(v[0] == 10);
    BOOST_TEST(v[1] == 20);
    BOOST_TEST(v[2] == 30);
}

BOOST_AUTO_TEST_CASE(test_vector_emplace_back)
{
    // Testing with std::string to ensure it handles constructor arguments
    mystl::vector<std::string> v;
    v.emplace_back(5, 'a');

    BOOST_TEST(v.size() == 1);
    BOOST_TEST(v[0] == "aaaaa");
}

BOOST_AUTO_TEST_CASE(test_vector_reallocation)
{
    mystl::vector<int> v;

    // Force multiple reallocations
    // Initially capacity 0 -> 1 -> 2 -> 4 -> 8 -> 16
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }

    BOOST_TEST(v.size() == 10);
    BOOST_TEST(v[9] == 9);
}

BOOST_AUTO_TEST_CASE(test_vector_clear)
{
    mystl::vector<int> v;
    v.push_back(1);
    v.push_back(2);

    v.clear();

    BOOST_TEST(v.size() == 0);
    BOOST_TEST(v.empty() == true);

    // Adding again after clear to ensure memory is still valid
    v.push_back(100);
    BOOST_TEST(v.size() == 1);
    BOOST_TEST(v[0] == 100);
}

BOOST_AUTO_TEST_SUITE_END()
