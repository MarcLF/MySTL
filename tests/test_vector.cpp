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

BOOST_AUTO_TEST_CASE(test_vector_at_access)
{
    mystl::vector<int> v;
    v.push_back(100);
    v.push_back(200);

    // Test valid access
    BOOST_CHECK_EQUAL(v.at(0), 100);
    BOOST_CHECK_EQUAL(v.at(1), 200);

    // Test out-of-bounds access (should throw)
    BOOST_CHECK_THROW(v.at(2), std::out_of_range);
    BOOST_CHECK_THROW(v.at(999), std::out_of_range);

    // Test const version
    const mystl::vector<int>& const_v = v;
    BOOST_CHECK_EQUAL(const_v.at(0), 100);
}

BOOST_AUTO_TEST_CASE(test_vector_iterators)
{
    mystl::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    // Test range-based for loop (uses begin/end under the hood)
    int sum = 0;
    for (int x : v) {
        sum += x;
    }
    BOOST_CHECK_EQUAL(sum, 60);

    // Test iterator arithmetic
    auto it = v.begin();
    BOOST_CHECK_EQUAL(*it, 10);
    ++it;
    BOOST_CHECK_EQUAL(*it, 20);

    // Test end() boundary
    BOOST_CHECK(v.begin() + v.size() == v.end());

    // Test modification through iterator
    *v.begin() = 50;
    BOOST_CHECK_EQUAL(v[0], 50);
}

BOOST_AUTO_TEST_SUITE_END()
