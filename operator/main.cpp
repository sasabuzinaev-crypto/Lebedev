#include "operator.h"

int main() {

    TextFile<string> f1(
        "file1.txt"
    );

    TextFile<string> f2(
        "file2.txt"
    );

    cout << "===== FILE1 ====="
         << endl;

    f1.print();

    cout << endl;

    cout << "===== FILE2 ====="
         << endl;

    f2.print();

    // ===== += =====

    f1 += f2;

    cout << endl;

    cout << "===== += ====="
         << endl;

    f1.print();

    // ===== + =====

    TextFile<string> f3 =
    f1 + f2;

    cout << endl;

    cout << "===== + ====="
         << endl;

    f3.print();

    // ===== -= =====

    f1 -= f2;

    cout << endl;

    cout << "===== -= ====="
         << endl;

    f1.print();

    // ===== - =====

    TextFile<string> f4 =
    f1 - f2;

    cout << endl;

    cout << "===== - ====="
         << endl;

    f4.print();

    // ===== sort =====

    f2.sortAsc();

    cout << endl;

    cout << "===== SORT ====="
         << endl;

    f2.print();

    // ===== sum =====

    cout << endl;

    cout << "SUM = "
         << f2.sumNumbers()
         << endl;

    return 0;
}