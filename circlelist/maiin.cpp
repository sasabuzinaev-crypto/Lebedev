
#include "CircleList.h"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

int josephus(int N, int k) {
    if (N <= 0) return 0;
    
    CircleList<int> circle;
    for (int i = N; i >= 1; i--) {
        circle.insertFirst(i);
    }
    
    while (circle.getCount() > 1) {
        for (int i = 1; i < k; i++) {
            circle.moveToNext();
        }
        circle.removeCurrent();
    }
    
    return circle.getCurrent()->getData();
}

int main() {
    int testValues[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int numTests = 7;
    string desktopPath = "/Users/" + string(getenv("USER")) + "/Desktop/results.csv";
    ofstream csvFile(desktopPath);
    
    if (!csvFile.is_open()) {
        cerr << "Ошибка: не удалось создать файл" << endl;
        return 1;
    }
    
    csvFile << "N,Ответ,Время расчета (сек)" << endl;
    
    for (int i = 0; i < numTests; i++) {
        int N = testValues[i];
        
        clock_t start = clock();
        int result = josephus(N, 2);
        clock_t end = clock();
        
        double timeVal = double(end - start) / CLOCKS_PER_SEC;
        
        csvFile << N << "," << result << "," << timeVal << endl;
    }
    
    csvFile.close();
    
    return 0;
}
