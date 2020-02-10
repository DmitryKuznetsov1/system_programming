#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
#include <gtest/gtest.h>
#include "../../source/5/tasks.h"


TEST(unordered_map, test) {
    std::unordered_map<User, int> um;
    User u1(100, "name1"), u2(200, "name2");
    um[u1] = 100500;
    um[u2] = 1;
    EXPECT_EQ(um.at(u1), 100500);
    EXPECT_EQ(um.at(u2), 1);
}

TEST(map, test) {
    User u1 = {110, "A"}, u2 = {102, "B"}, u3 = {101, "C"}, u4 = {115, "D"};

    std::map<User, int> mp;
    mp[u1] = 1;
    mp[u2] = 2;
    mp[u3] = 3;
    mp[u4] = 4;

    int ans[4] = {101, 102, 110, 115};
    size_t i = 0;
    for (auto x : mp) {
        EXPECT_EQ(x.first.get_id(), *(ans + i));
        ++i;
    }
}


// unordered set
TEST(unordered_set, test) {
    User u1 = {110, "A"}, u2 = {102, "B"};

    std::unordered_set<User> uset;
    uset.insert(u2);
    uset.insert(u1);
    EXPECT_TRUE(*uset.find(u1) == u1);
    EXPECT_TRUE(*uset.find(u2) == u2);
}

// set
TEST(set, test) {
    User u1 = {110, "A"}, u2 = {102, "B"};

    std::set<User> set;
    set.insert(u2);
    set.insert(u1);
    EXPECT_TRUE(*set.find(u1) == u1);
    EXPECT_TRUE(*set.find(u2) == u2);
}

TEST(mergeSort, test) {
    std::vector<int> vec{8, 4, 1, 2, 32, 16};
    std::vector<int> ans{1, 2, 4, 8, 16, 32};
    merge_sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i)
        EXPECT_EQ(vec[i], ans[i]);
}