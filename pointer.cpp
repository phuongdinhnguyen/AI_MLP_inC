#include <iostream>

using namespace std;

int* returnPointer(int &x)
{
    return &x;
}

void printArr(int *arr, int len)
{  
    for (int i = 0 ; i < len ; i++)
    cout << arr[i] << " ";
    cout << endl;
}

int* returnAP(int *arr)
{
    return arr+2;
}

int main()
{
    int a = 3;

    int *arr = new int [5] {1,2,99,55,5};

    int *b;
    b = &a;
    cout << a << endl;
    cout << b << endl;
    cout << *b << endl;

    *b = 9;

    cout << a << endl;

    cout << *returnPointer(a) << endl;
    
    cout << "array elm: " << arr[2] << endl;
    printArr(arr,5);

    cout << "return AP: " << *returnAP(arr);

    *returnAP(arr) = 10;

    cout << "changed AP: "; printArr(arr, 5);
    delete arr;
    return 0;
}