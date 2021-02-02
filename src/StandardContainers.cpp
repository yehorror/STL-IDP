#include <gtest/gtest.h>

#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>

TEST(STL, Vector)
{
    // std::vector is just like dynamic array in C
    // elements stored continuously in a single chunk of allocated memory
    std::vector<int> vec;

    vec.push_back(1); // back insertion is O(1) in case if there are no re-allocations
    // if container has no available memory to push new element, it reallocates memory
    // and moving all objects into new place in memory, which makes complexity O(n)
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    // insertion inside of vector (beginning or middle) is O(n)
    // because before insertion it moves elements forward
    vec.insert(vec.begin(), 0);

    // access is O(1)
    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 3);
    EXPECT_EQ(vec[4], 4);

    // vector<T>::at(index) throws an "out of range" exception in case index is out of bounds
    EXPECT_THROW(vec.at(5), std::out_of_range);

    // vector::data() may be used to read the data by pointer
    // in case you need to pass it to some C-API
    int* ptr = vec.data();

    EXPECT_EQ(ptr[0], 0);
    EXPECT_EQ(ptr[1], 1);
    EXPECT_EQ(ptr[2], 2);
    EXPECT_EQ(ptr[3], 3);
    EXPECT_EQ(ptr[4], 4);

    // search is O(n) in case vector is unsorted and std::find() is used
    auto foundItem = std::find(vec.begin(), vec.end(), 3);
    EXPECT_NE(foundItem, vec.end());
    EXPECT_EQ(*foundItem, 3);

    // search is O(log(n)) if vector is sorted, and binary search is used
    // std::lower_bound returns first element that are NOT LESS than element we're looking for
    auto foundItem2 = std::lower_bound(vec.begin(), vec.end(), 4);
    EXPECT_NE(foundItem2, vec.end());
    EXPECT_EQ(*foundItem2, 4);
}

TEST(STL, Deque)
{
    // deque is like list of vectors
    std::deque<int> deque;

    // back and front insertions are O(1)
    deque.push_back(2);
    deque.push_front(0);

    // middle-insertions are O(n)
    deque.insert(deque.begin() + 1, 1);

    EXPECT_EQ(deque[0], 0);
    EXPECT_EQ(deque[1], 1);
    EXPECT_EQ(deque[2], 2);

    // search is O(n), just like in vector...
    auto foundItem = std::find(deque.begin(), deque.end(), 1);
    EXPECT_NE(foundItem, deque.end());
    EXPECT_EQ(*foundItem, 1);

    // ...and O(log(n)) if deque is sorted & binary search is used
    auto foundItem2 = std::lower_bound(deque.begin(), deque.end(), 2);
    EXPECT_NE(foundItem2, deque.end());
    EXPECT_EQ(*foundItem2, 2);
}

TEST(STL, List)
{
    // elements in list stored as a separated nodes
    // each node consists of value, pointers to next and previous nodes
    std::list<int> list;

    // insertion is O(1) (you just need to know where to insert)
    auto first = list.insert(list.end(), 13);
    auto second = list.insert(list.end(), 42);
    auto third = list.insert(list.end(), 54);

    EXPECT_EQ(*first, 13);
    EXPECT_EQ(*second, 42);
    EXPECT_EQ(*third, 54);

    // search is O(n)
    auto foundItem = std::find(list.begin(), list.end(), 42);
    EXPECT_NE(foundItem, list.end());
    EXPECT_EQ(*foundItem, 42);

    // binary search is O(log(n))
    auto foundItem2 = std::lower_bound(list.begin(), list.end(), 13);
    EXPECT_NE(foundItem2, list.end());
    EXPECT_EQ(*foundItem2, 13);
}

TEST(STL, Set)
{
    // std::set provides container for set of some values
    // you need to provide operator '<' (less) to store elements in set
    // or provide std::less<Type> (and pass it as a template parameter)
    std::set<int> set;

    // insertion is O(log(n))
    set.insert(456);
    set.insert(123);

    // even though 456 was inserted earlier than 123
    // 123 will be the first element in a set
    EXPECT_EQ(*set.begin(), 123);
    EXPECT_EQ(*(++set.begin()), 456);   // check second element in set

    set.insert(52375);
    set.insert(789);

    // search is also O(log(n))
    auto found = set.find(52375);
    EXPECT_NE(found, set.end());
    EXPECT_EQ(*found, 52375);
    // it's better not to use std::lower_bound on sets
    // it provides log(n) time complexity ONLY IF RandomAccessIterator is passed
    // and std::set doesn't provide ones
    // so it's better to use find() or std::set<T>::lower_bound()
}

TEST(STL, Map)
{
    // std::map provides container for set of values with access by some key
    std::map<int, int> map;

    // insertion is O(log(n))
    map.insert({22, 8});
    map[13] = 37;
    map.emplace(52, 375);

    // access (by key) is O(log(n))
    EXPECT_EQ(map[22], 8);
    EXPECT_EQ(map[13], 37);
    EXPECT_EQ(map[52], 375);

    // search by key is also O(log(n)) (because access is a search basically)
    auto foundItem = map.find(52);
    EXPECT_NE(foundItem, map.end());
    EXPECT_EQ(foundItem->first, 52);    // key
    EXPECT_EQ(foundItem->second, 375);  // value
}

TEST(STL, MultiSet)
{
    // std::multiset is like a std::set, but is able to contain multiple equal elements
    std::multiset<int> set;

    // insertion is O(log(n))
    set.insert(456);
    set.insert(123);
    set.insert(123);

    auto range = set.equal_range(123);

    EXPECT_EQ(*range.first, 123);
    EXPECT_EQ(*++range.first, 123);
}

TEST(STL, MultiMap)
{
    // similar to multiset
    std::multimap<int, int> map;

    map.emplace(12, 34);
    map.emplace(12, 56);
    map.emplace(13, 23);

    // returns range of elements with specified key
    // pair.first is first element 
    // pair.second is the element that follows after last element of range
    auto range = map.equal_range(12);

    EXPECT_EQ(range.first->second, 34);
    EXPECT_EQ((++range.first)->second, 56); // next element
}
