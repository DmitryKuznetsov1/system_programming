#include "tasks.h"


int main() {
    Matrix<int, 3, 3> m1 = {1, 2, 5, 6, 9, 10, 13, 14, 17};
    Matrix<int, 3, 3> c = {1, 2, 3, 2, 4, 5, 3, 5, 0};
//    m1.show();
//    std::cout << m1.is_symmetric(1);
//    (c < d).show();
//    c.show();
//    c.transposed().show();
//    (c - c.transposed()).show();
//    absMat(c - c.transposed()).show();
//    (absMat(c - c.transposed()) < 1).show();
//    cout << all(absMat(c - c.transposed()) < 1) << endl;
    cout << m1.is_symmetric() << '\n';
    cout << c.is_symmetric() << '\n';
//    Matrix<int, 2, 2> d {2, 0, 3, 5};
//    std::vector<bool> z = c < d;
//    Matrix<int, 2, 2> min = where(c < d, c, d);
//    for (int i = 0; i < z.size(); ++i) {
//        cout << z[i] << ' ';
//    }
//    min.show();
//    (absMat(c - c.transposed()) < 10e-5).show();
    return 0;
}