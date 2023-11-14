#include "List.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <utility>

using namespace std;

// Add your test cases here
TEST(test_empty) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}

TEST(test_push_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    ASSERT_EQUAL(list.front(), 2);
}

TEST(test_push_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    ASSERT_EQUAL(list.back(), 3);
}

TEST(test_front) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    ASSERT_EQUAL(list.front(), 1);
}

TEST(test_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    ASSERT_EQUAL(list.back(), 2);
}

TEST(test_pop_front) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.size(), 3);
    list.pop_front();
    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_pop_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_EQUAL(list.back(), 3);
    ASSERT_EQUAL(list.size(), 3);
    list.pop_back();
    ASSERT_EQUAL(list.back(), 2);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();
    ASSERT_EQUAL(list.size(), 0);
}

TEST(test_clear2) {
    List<int> list;
    list.push_back(1);

    list.clear();
    ASSERT_EQUAL(list.size(), 0);
}

TEST(test_default_constructor) {
    List<int> my_list;
    ASSERT_TRUE(my_list.empty());
    ASSERT_EQUAL(my_list.size(), 0);
}

TEST(test_copy_constructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);

    List<int> copy = original;
    ASSERT_EQUAL(copy.size(), original.size());
    ASSERT_EQUAL(copy.front(), original.front());
    ASSERT_EQUAL(copy.back(), original.back());
}

TEST(test_assignment_operator) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2 = list1;
    ASSERT_EQUAL(list2.size(), 2);
    ASSERT_EQUAL(list2.front(), 1);
    ASSERT_EQUAL(list2.back(), 2);
}

TEST(test_assignment_operator2) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);

    // Indirect self-assignment
    List<int>& ref_list = my_list;
    my_list = ref_list;

    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 2);
}

TEST(insert_and_erase1) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(3);

    List<int>::Iterator iter = my_list.begin();
    ++iter;  // Point to second element (3)

    my_list.insert(iter, 2); // List should be 1, 2, 3
    ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 3);
    ASSERT_EQUAL(my_list.size(), 3);

    iter = my_list.begin();
    ++iter;
    my_list.erase(iter); // List should be 1, 3
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(*my_list.begin(), 1);
    iter = my_list.begin();
    ++iter;
    ASSERT_EQUAL(*iter, 3);
}

TEST(insert_and_erase2) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(3);

    List<int>::Iterator iter = my_list.begin();

    my_list.insert(iter, 2); // List should be 2, 1, 3
    ASSERT_EQUAL(my_list.front(), 2);
    ASSERT_EQUAL(my_list.back(), 3);
    ASSERT_EQUAL(my_list.size(), 3);

    iter = my_list.begin();
    my_list.erase(iter); // List should be 1, 3
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(*my_list.begin(), 1);
    iter = my_list.begin();
    ++iter;
    ASSERT_EQUAL(*iter, 3);
}

TEST(insert_and_erase3) {
    List<int> my_list;
    my_list.push_back(1);
    my_list.push_back(3);

    List<int>::Iterator iter = my_list.begin();
    ++iter;  // Point to second element (3)
    ++iter;  // Point to third element (outside of list scope)

    my_list.insert(iter, 2); // List should be 1, 3, 2
    // ASSERT_EQUAL(my_list.front(), 1);
    ASSERT_EQUAL(my_list.back(), 2);
    ASSERT_EQUAL(my_list.size(), 3);

    iter = my_list.begin();
    ++iter;
    ++iter;
    my_list.erase(iter); // List should be 1, 3
    ASSERT_EQUAL(my_list.size(), 2);
    ASSERT_EQUAL(*my_list.begin(), 1);
    iter = my_list.begin();
    ++iter;
    ASSERT_EQUAL(*iter, 3);
}

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST_MAIN()
