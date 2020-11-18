#include <gtest/gtest.h>

#include <vector>
#include <memory>

template <class Type>
using unique_ptr_vt = std::vector< std::unique_ptr<Type> >;  // vector of unique_ptrs

TEST(STL, SmartPointersInVector)
{
    unique_ptr_vt<int> vector;

    vector.emplace_back(
        std::make_unique<int>(42)
    );

    EXPECT_EQ(*vector.back(), 42);
}

TEST(STL, SmartPointersMove)
{
    unique_ptr_vt<int> vector;

    auto ptr = std::make_unique<int>(228);

    // Unique pointer owns its resource, and it cannot make copies of it
    // so we need to move it into vector, not copy
    // std::move makes rvalue from lvalue reference
    vector.push_back(
        std::move(ptr)
    );

    EXPECT_EQ(ptr, nullptr);
    EXPECT_EQ(*vector.back(), 228);
}