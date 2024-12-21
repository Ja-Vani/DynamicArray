//
// Created by Ja_Vani on 2.12.2024.
//
#include "gtest/gtest.h"
#include "my_array.hpp"

TEST(MyArray_test, Array_base_tesst) {
    MyArray<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    for (int i = 0; i < a.size(); ++i)
        a[i] *= 2;
    ASSERT_TRUE(a.size() == 10);
    for (int i = 0; i < a.size(); ++i)
        ASSERT_TRUE(a[i] == (i+1)*2);
}

TEST(MyArray_test, Iterator_test) {
    MyArray<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    int count = 1;
    for (auto it = a.iterator(); it.hasNext(); it.next())
        ASSERT_TRUE(it.get() == count++);
}

TEST(MyArray_test, const_Iterator_test) {
    MyArray<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    const MyArray<int> b(a);
    int count = 1;
    for (auto it = b.iterator(); it.hasNext(); it.next())
        ASSERT_TRUE(it.get() == count++);
}

TEST(MyArray_test, Array_add_test) {
    MyArray<int> a;
    for (int i = 0; i < 100; ++i)
        a.insert(i + 1);
    ASSERT_TRUE(a.size() == 100);
    for (int i = 0; i < a.size(); ++i)
        ASSERT_TRUE(a[i] == (i+1));
}

TEST(MyArray_test, Array_remove_test) {
    MyArray<int> a;
    for (int i = 0; i < 100; ++i)
        a.insert(i + 1);
    for (int i = 0; i < 80; ++i)
        a.remove(1);
    ASSERT_TRUE(a[0] == 1);
    ASSERT_TRUE(a.size() == 20);
    for (int i = 1; i < a.size(); ++i)
        ASSERT_TRUE(a[i] == (i+81));
}

TEST(MyArray_test, Array_copy_test) {
    MyArray<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    for (int i = 0; i < a.size(); ++i)
        a[i] *= 2;
    MyArray<int> b(a);
    ASSERT_TRUE(b.size() == 10);
    for (int i = 0; i < b.size(); ++i)
        ASSERT_TRUE(b[i] == (i+1)*2);
}

TEST(MyArray_test, Array_swap_test) {
    MyArray<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    for (int i = 0; i < a.size(); ++i)
        a[i] *= 2;
    MyArray<int> b(std::move(a));
    ASSERT_TRUE(b.size() == 10);
    for (int i = 0; i < b.size(); ++i)
        ASSERT_TRUE(b[i] == (i+1)*2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
