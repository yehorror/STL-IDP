#include <gtest/gtest.h>

#include <algorithm>

#include <vector>

TEST(STL, Find)
{
    // std::find returns first element from some range
    // that equals to searchable element
    // complexity is O(n) (even for std::map or std::set)
    // so it is better to use container<T>::find() method sometimes
    std::vector<int> vec{ 1, 4, 8, 3, 3, 6, 9 };

    auto foundItem = std::find(vec.begin(), vec.end(), 3);

    EXPECT_NE(foundItem, vec.end());
    EXPECT_EQ(*foundItem, 3);
}

TEST(STL, FindIf)
{
    // std::find_if similar to std::find, but it performs search with predicate
    // returns first element from range that satisfies the predicate (it returns true)
    // it is better to use std::map instead of vector of pairs - the following code is just for an example
    // of predicate usage in "complicated" structures
    std::vector<std::pair<std::string, int>> vec;

    vec.emplace_back("One", 1);
    vec.emplace_back("Second", 2);
    vec.emplace_back("Three", 3);
    vec.emplace_back("Four", 4);

    auto foundItem = std::find_if(
        vec.begin(), 
        vec.end(), 
        [] (const auto& element)
        {
            return element.second == 3;
        }
    );

    EXPECT_NE(foundItem, vec.end());
    EXPECT_EQ(foundItem->first, "Three");
    EXPECT_EQ(foundItem->second, 3);
}

TEST(STL, LowerBound)
{
    // std::lower_bound is one of binary search implementation
    // it returns first element from range, that is NOT less than passed value
    // complexity is O(log(n))
    // requires the sequence to be sorted in a passed range
    std::vector<int> vec{ 2,4,8,16,32,64,128 };

    auto foundItem = std::lower_bound(vec.begin(), vec.end(), 8);

    EXPECT_NE(foundItem, vec.end());
    EXPECT_EQ(*foundItem, 8);

    foundItem = std::lower_bound(vec.begin(), vec.end(), 9);

    EXPECT_NE(foundItem, vec.end());
    EXPECT_EQ(*foundItem, 16);  // next value after 8 in vector
}

TEST(STL, UpperBound)
{
    // std::upper_bound is other binary search implementation
    // returns first element from range, that is GREATER than passed value
    // complexity is similar to lower_bound - O(log(n))
    std::vector<int> vec{ 2,4,8,16,32,64,128 };

    auto foundItem = std::upper_bound(vec.begin(), vec.end(), 8);

    EXPECT_NE(foundItem, vec.end());
    EXPECT_EQ(*foundItem, 16);

    // lower_bound and upper_bound both returns the lowest and the highest positions
    // where the value could be inserted without breaking the ordering
}

TEST(STL, BinarySearch)
{
    // std::binary_search just returns boolean value - if an element is present in sorted sequence
    std::vector<int> vec{ 1, 2, 4, 5, 6 };

    bool isThreePresent = std::binary_search(vec.begin(), vec.end(), 3);
    EXPECT_FALSE(isThreePresent);

    bool isFivePresent = std::binary_search(vec.begin(), vec.end(), 5);
    EXPECT_TRUE(isFivePresent);
}

TEST(STL, Search)
{
    // std::search performs search of subsequence in sequence
    // returns iterator pointing to a first element ob the subsequence in sequence
    // complexity is O(n*m) comparisons, where n is lenght of first sequence
    // and m is the length of the subsequence
    std::vector<int> vec{ 1,2,3,4,5,6,7,8,9,10 };

    std::vector<int> subSeq{ 4,5,6 };

    auto firstSeqIterator = std::search(vec.begin(), vec.end(), subSeq.begin(), subSeq.end());

    EXPECT_NE(firstSeqIterator, vec.end());
    EXPECT_EQ(*firstSeqIterator, 4);
}
