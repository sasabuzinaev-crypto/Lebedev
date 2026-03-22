#include <iostream>
#include "Array.h"
#include <ctime>
#include <fstream>

using namespace std;

Array IosifeFlaviya(Array* arr, int N, int k){
	Array a = *arr;
	int index = 0;
	while(a.getSize() > 0){
		index = (index + k - 1) % a.getSize();
		a.remove(index);
	}
	return a;
}

int main()
{
    
    int arr1[]= {1000,5000,10000,50000,100000,500000,1000000};
    
    
    ofstream csv("/Users/sashabuzinaevicloud.com/Desktop/qq/qq/josephus.csv");
    csv << "N,k,time\n";
    if(!csv){
        cout << "Ошибка открытия файла\n";
        return 1;
    }
    setlocale(LC_ALL, "Russian");
    Array arr(3);
   for (int i = 0; i < 4; i++)
       arr.insert(i + 1);
   cout << arr << endl;
   for (int i = 0; i < 8; i += 2)
       arr.insert(10 + i, i);
   cout << arr << endl;
   for (int i = 1; i < 8; i += 2)
       arr[i] = 20 + i;
   cout << arr << endl;
   for (int i = 6; i >= 0; i -= 3)
       arr.remove(i);
   cout << arr << endl;
ofstream csv("results.csv");
	csv << "N,k,Time\n";
	int arr1[]= {1000,5000,10000,50000,100000,500000,1000000};
	int size = sizeof(arr1)/sizeof(arr1[0]);

	for (int i = 0;i<size;i++){
		const int k =2;
		int N = arr1[i];
		Array arr(N);
		for (int j = 0; j < N-1; j++){
			arr.insert(j + 1);	
			
		}
		clock_t startTime = clock();
		IosifeFlaviya(&arr, N, k);
		clock_t endTime = clock();
		double elapsedTime = double(endTime - startTime) / CLOCKS_PER_SEC;
		csv << N << "," << k << "," << elapsedTime << "\n";
        cout<<i;

	}
	cout<<"Готово!"<<endl;
	return 0;

}



