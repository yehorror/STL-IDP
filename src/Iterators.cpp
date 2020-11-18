#include <gtest/gtest.h>

#include <vector>
#include <memory>

TEST(STL, Iterator)
{
    std::vector<int> vector{ 228, 1337, 42 };

    auto iterator = vector.begin();
    EXPECT_EQ(*iterator, 228);

    // we may change the value of an element iterator pointing to
    *iterator = 156;
    EXPECT_EQ(*iterator, 156);
    EXPECT_EQ(vector[0], 156);  // since we changed first element with iterator, let's make sure that value also changed in vector itself

    ++iterator;
    EXPECT_EQ(*iterator, 1337);

    ++iterator;
    EXPECT_EQ(*iterator, 42);

    ++iterator;
    EXPECT_EQ(iterator, vector.end());
}

TEST(STL, ConstIterator)
{
    std::vector<int> vector{ 228, 1337, 42 };

    auto iterator = vector.cbegin();
    EXPECT_EQ(*iterator, 228);

    // next line just won't compile with C3892 'iterator': you cannot assign to a variable that is const
    // *iterator = 156;

    ++iterator;
    EXPECT_EQ(*iterator, 1337);

    ++iterator;
    EXPECT_EQ(*iterator, 42);

    ++iterator;
    EXPECT_EQ(iterator, vector.end());
}

TEST(STL, ReverseIterator)
{
    std::vector<int> vector{ 228, 1337, 42 };

    // reverse order of iterating
    auto iterator = vector.rbegin();
    EXPECT_EQ(*iterator, 42);

    *iterator = 156;
    EXPECT_EQ(*iterator, 156);
    EXPECT_EQ(vector[2], 156);  // last element was modified

    ++iterator;
    EXPECT_EQ(*iterator, 1337);

    ++iterator;
    EXPECT_EQ(*iterator, 228);

    ++iterator;
    EXPECT_EQ(iterator, vector.rend());
}
