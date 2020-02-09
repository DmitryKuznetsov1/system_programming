#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <string>
#include "myVector.cpp"
#include <initializer_list>


int main()
{
    myVector<std::ofstream> vector;
    for (size_t i = 0; i < 10; i++) {
        std::string name = "f" + std::to_string(i) + ".txt";
        vector.push_back(std::ofstream(name));
    }
    std::shuffle(vector.begin(), vector.end(), std::random_device());
    int num = 0;
    for (auto &stream: vector) {
        stream << num;
        stream.close();
        ++num;
    }
//    myVector<int> vect(1, 0);
//    for (int i = 1; i < 6; ++i) {
//        vect.push_back(i);
//    }
//    vect.push_back(10);
//    vect.show();
//    myVector<int> vect1 = vect;
//    vect1.erase(vect1.begin() + 1, vect1.begin() + 3);
//    vect.erase(vect.begin() + 3, vect.begin() + 6);
//    cout << "vect" << endl;
//    vect.show();
//    cout << "vect1" << endl;
//    vect1.show();
    return 0;
}