#include <gtest/gtest.h>
#include <array>
#include <sstream>
#include "../source/c_m_t.h"


//message
TEST(message, number_of_args) {
    std::string  str = "a + b = 10";
    std::stringstream ss;
    message(ss, "% + %% = %", "a", "b", 10.0);
    EXPECT_NE(str, ss.str());
}


TEST(message, string) {
    std::string  str = "a + b = 10";
    std::stringstream ss;
    message(ss, "% + % = %", "a", "b", 10.0);
    EXPECT_EQ(str, ss.str());
}



// cat
TEST(cat, arrays){
    std::array<float, 3> vec1{1.0f, 2.0f, 3.0f};
    std::array<float, 3> vec2{4.0f, 5.0f, 6.0f};
    std::array<float, 6> res = cat(vec1, vec2);

    std::array<float, 6> ans{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
    for (size_t i = 0; i < ans.size(); ++i) {
        EXPECT_EQ(ans[i], res[i]);
    }

}

// tie
TEST(tie, arrays) {
    std::array<int, 6> vec1{1, 2, 3, 4, 5, 6};
    std::array<int, 3> vec2{0, 0, 0};
    std::array<int, 3> vec3{1, 1, 1};
    tie(vec2, vec3) = vec1;

    std::array<int, 3> ans1{1, 2, 3};
    std::array<int, 3> ans2{4, 5, 6};

    for (size_t i = 0; i < ans1.size(); ++i) {
        EXPECT_EQ(ans1[i], vec2[i]);
        EXPECT_EQ(ans2[i], vec3[i]);
    }
}