#include <gtest/gtest.h>
#include "../source/tasks.h"
#include <ostream>


TEST(ln80c_buffer, 2Strings){
    std::stringbuf strBuf;
    ln80c_buffer buffer(&strBuf);
    std::ostream outStr(&buffer);

    outStr << "Hello";
    EXPECT_EQ("0       Hello", strBuf.str());
    outStr << '\n';
    outStr << "World";
    EXPECT_EQ("0       Hello\n1       World", strBuf.str());
}

TEST(ln80c_buffer, 72Chars){
    std::stringbuf strBuf;
    ln80c_buffer buffer(&strBuf);
    std::ostream outStr(&buffer);

    std::string str(72, '1');
    outStr << str;
    EXPECT_EQ("0       " + str + '\n', strBuf.str());
    outStr<<"123";
    EXPECT_EQ("0       " + str + "\n1       123", strBuf.str());
}

TEST(ln80c_buffer, 73Chars){
    std::stringbuf strBuf;
    ln80c_buffer buffer(&strBuf);
    std::ostream outStr(&buffer);

    std::string str(72, '1');
    outStr << str + "1111";
    EXPECT_EQ("0       " + str + "\n1       1111", strBuf.str());
}