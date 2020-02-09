#include <gtest/gtest.h>
#include "../source/tasks.h"


struct where_param {
    Matrix<int, 3, 3> m1;
    Matrix<int, 3, 3> m2;
    Matrix<int, 3, 3> ans;
};


class where_test : public ::testing::TestWithParam<where_param> {};


TEST_P(where_test, _) {
    const where_param& param = GetParam();
    Matrix<int, 3, 3> mat2{param.m2};
    Matrix<int, 3, 3> mat1{param.m1};
    Matrix<int, 3, 3> res = where(mat1 < mat2, mat1, mat2);
    EXPECT_TRUE(param.ans.data == res.data);
}


INSTANTIATE_TEST_CASE_P(
        _,
        where_test,
        ::testing::Values(
                where_param{
                        {1, 2, 5, 6, 9, 10, 13, 14, 17},
                        {0, 3, 4, 7, 8, 11, 12, 15, 16},
                        {0, 2, 4, 6, 8, 10, 12, 14, 16}
                },
                where_param{
                        {1, 11, 21, 31, 41, 51, 61, 71, 81},
                        {12, 13, 4, 100, 40, 56, 57, 17, 90},
                        {1, 11, 4, 31, 40, 51, 57, 17, 81}
                }
        )
);



//struct is_symmetric_param{
//    Matrix<int, 3, 3> m;
//    bool ans;
//};
//
//class is_symmetric_test: public ::testing::TestWithParam<is_symmetric_param> {};
//
//TEST_P(is_symmetric_test, _){
//    const is_symmetric_param& param = GetParam();
//    auto res = param.m.is_symmetric();
//    EXPECT_EQ(param.ans, res);
//}
//
//INSTANTIATE_TEST_CASE_P(
//        _,
//        is_symmetric_test,
//        ::testing::Values(
//                is_symmetric_param{
//                        {1, 0, 0, 0, 1, 0, 0, 0, 1},
//                        1
//                },
//                is_symmetric_param{
//                        {1, 2, 3, 4, 5, 6, 7, 8, 9},
//                        0
//                },
//                is_symmetric_param{
//                        {1, 2, 3, 2, 4, 5, 3, 5, 0},
//                        1
//                },
//        )
//);

