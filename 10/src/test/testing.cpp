#include <gtest/gtest.h>
#include <vector>
#include <../source/tasks.h>


TEST(rotate, wrong_size){
    std::vector<int> vec = {1, 2, 3};
    EXPECT_FALSE(rotate(vec, 10));
}

TEST(rotate, wrong_number_of_size) {
    std::vector<int> vec = {3, 4};
    EXPECT_FALSE(rotate(vec, 3.3));
}


TEST(rotate, correct_answer_0) {
    std::vector<int> vec = {3, 4};
    rotate(vec, 4);
    EXPECT_EQ(3, vec[0]);
    EXPECT_EQ(4, vec[1]);
}

TEST(rotate, correct_answer_1) {
    std::vector<int> vec = {3, 4};
    rotate(vec, 1);
    EXPECT_EQ(-4, vec[0]);
    EXPECT_EQ(3, vec[1]);
}

TEST(rotate, correct_answer_2) {
    std::vector<int> vec = {3, 4};
    rotate(vec, 2);
    EXPECT_EQ(-3, vec[0]);
    EXPECT_EQ(-4, vec[1]);
}

TEST(rotate, correct_answer_3) {
    std::vector<int> vec = {3, 4};
    rotate(vec, 3);
    EXPECT_EQ(4, vec[0]);
    EXPECT_EQ(-3, vec[1]);
}


TEST(rotate, correct_answer_more_than_3) {
    std::vector<int> vec = {3, 4};
    rotate(vec, 10);
    EXPECT_EQ(-3, vec[0]);
    EXPECT_EQ(-4, vec[1]);
}

TEST(rotate, counterclock){
    std::vector<int> vec = {3, 4};
    std::vector<int> vec_copy(vec);
    rotate(vec, 3);
    rotate(vec_copy, -1);
    EXPECT_EQ(vec[0], vec_copy[0]);
    EXPECT_EQ(vec[1], vec_copy[1]);
}