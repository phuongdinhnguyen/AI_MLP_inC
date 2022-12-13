#include "MultiDimMatrix.h"
#include <fstream>

tuple<MultiDimArray,tuple <MultiDimArray, MultiDimArray, MultiDimArray>> 
linear_foward(MultiDimArray x, MultiDimArray w, MultiDimArray b)
{
    MultiDimArray flattened_x = x.reshapeTo2Dim();
    MultiDimArray out = flattened_x * w + b;

    auto cache = make_tuple(x,w,b);

    return make_tuple(out, cache);
}

int main()
{
    // trying with 4-dim array
    //MultiDimArray a = MultiDimArray(4,{2,3,2,2});
    // a.reshapeTo2Dim();

    // cout << "Dimension of array a: " << a.dim << endl;
    // cout << a.INDEX({1,1,0,1}) << endl;

    // trying with 1-dim array
    // MultiDimArray b = MultiDimArray(1,{10});
    // cout << "Dimension of array b: " << b.dim << endl;
    // cout << b.INDEX({8}) << endl;

    // trying to assign
    // MultiDimArray c = MultiDimArray(2,{9,9});
    // c({2,2}) = 7;
    // c.initArray();
    // cout << "trying to assign: " << c.arr[8] << endl;


    // multiply matrix
    // MultiDimArray A = MultiDimArray(2,{4,2});
    
    // *A({0,0}) = 1; *A({0,1}) = 2; 
    // *A({1,0}) = 3; *A({1,1}) = 4;
    // *A({2,0}) = 1; *A({2,1}) = 2; 
    // *A({3,0}) = 3; *A({3,1}) = 4;
    
    // A.printArr();
    // MultiDimArray B = MultiDimArray(2,{2,2});
   
    // B.printArr();

    // *B({0,0}) = 1; *B({0,1}) = 2; 
    // *B({1,0}) = 3; *B({1,1}) = 4;

    // cout << "indexing: " << B.INDEX({1,0}) << " " << B.INDEX({0,1}) << endl;

    // B.printArr();

    // MultiDimArray C = A * B;
    // C.printArr();


    //multiply 2d array with 1d array
    // MultiDimArray A1 = MultiDimArray(2,{2,3});
    // MultiDimArray A2 = MultiDimArray(1,{3});
    
    // *A1({0,0}) = 1; *A1({0,1}) = 2; *A1({0,2}) = 3;
    // *A1({1,0}) = 4; *A1({1,1}) = 5; *A1({1,2}) = 6;

    // *A2({0}) = 3; *A2({1}) = 2; *A2({2}) = 1;
    // MultiDimArray A3 = A1 * A2;
    // A1.printArr();
    // A2.printArr();
    // A3.printArr();

    ifstream file("demofile2.txt");
    double *arr = new double [200];

    while (!file.eof()){
        double f;
        file >> f;
        cout << f << endl;
    }
    cout << "Program exited!" << endl;
    return 0;
}