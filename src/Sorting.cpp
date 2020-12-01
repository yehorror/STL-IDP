#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

TEST(STL, SortAsc)
{
    // std::sort is O(n*log(n))
    // sorts range of elements
    std::vector<int> vector {5, 2, 3, 7, 5, 1, 3};
    
    std::sort(vector.begin(), vector.end());
    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);
    EXPECT_EQ(vector[2], 3);
    EXPECT_EQ(vector[3], 3);
    EXPECT_EQ(vector[4], 5);
    EXPECT_EQ(vector[5], 5);
    EXPECT_EQ(vector[6], 7);

    // or just
    
    EXPECT_TRUE(std::is_sorted(vector.begin(), vector.end()));
}

TEST(STL, SortCustomComparator)
{
    std::vector<int> vector {5, 2, 3, 7, 5, 1, 3};

    // with use of custom comparator we may specify order (ascending or descending)
    // or even use them to compare some structures by their fields
    auto comparator = 
        [] (int a, int b)
        {
            return a > b;
        };

    std::sort(vector.begin(), vector.end(), comparator);
    // default comparator is for ascending order
    EXPECT_FALSE(std::is_sorted(vector.begin(), vector.end()));
    // our comparator is for descending order
    EXPECT_TRUE(std::is_sorted(vector.begin(), vector.end(), comparator));
}

TEST(STL, PartialSort)
{
    // partial_sort sorts container partially
    // elements in specified range (starting from beginning) is guaranteed to be sorted
    // O(n * log(middle - begin))
    std::vector<int> vector {5, 2, 3, 1, 1, 7, 3};

    std::partial_sort(vector.begin(), vector.begin() + 3, vector.end());

    EXPECT_TRUE(std::is_sorted(vector.begin(), vector.begin() + 3));
    EXPECT_FALSE(std::is_sorted(vector.begin(), vector.end()));
}

TEST(STL, NthElement)
{
    // nth_element places only one element where it would be placed if container was sorted
    std::vector<int> vector {5, 2, 3, 1, 1, 7, 3};

    // make copy of container and sort it to compare with result of nth_element
    std::vector<int> sortedCopy(vector);
    std::sort(sortedCopy.begin(), sortedCopy.end());

    const size_t nthIndex = 0;

    std::nth_element(vector.begin(), vector.begin() + nthIndex, vector.end());

    EXPECT_EQ(vector[nthIndex], sortedCopy[nthIndex]);
}
