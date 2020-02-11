#include <iostream>
#include "tasks.h"

int main() {
    std::streambuf* buff = std::cin.rdbuf();
    stat_buffer stat_buff(buff);
    std::cin.rdbuf(&stat_buff);

    std::cout << std::cin.rdbuf();
    std::cout << stat_buff.getLineCount() << '\n' << stat_buff.getWordCount() << '\n' << stat_buff.getCharCount() << '\n';
    std::cin.rdbuf(buff);
    return 0;
}