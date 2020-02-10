#include <gtest/gtest.h>
#include "../../source/6/tasks.h"


TEST(gShapes, CircleTraits) {
    Circle<int> circle(1);
    EXPECT_EQ(sizeof(1), std::Trait<Circle<int>>::size(circle));
}

TEST(GEOMETRY, RECTANGLE_TRAIT) {
    Rectangle<double> rect(6, 9);
    EXPECT_EQ(sizeof(6) + sizeof(9), std::Trait<Rectangle<double>>::size(rect));
}