#include <iostream>
#include <cstring>
#include <vector>
#include <initializer_list>
#include <tuple>
#include <fstream>

using namespace std;

#define ROW_COL_IDX(row, col, num_cols) (row*num_cols + col)

class MultiDimArray
{
public:
    vector <int> sub;
    int dim = 0;
    int initLength = 1;
    double *arr = NULL;

public:
    template <typename T>
    MultiDimArray(int _numOfDim, initializer_list<T> list);
    // ~MultiDimArray();
    // khởi tạo giá trị 0 cho toàn mảng
    void initArray();

    // in ra mảng (chỉ áp dụng 2 chiều)
    void printArr();

    // read from files
    void readFromFile(string _dir);

    // tìm chỉ số so với array 1D
    template <typename T>
    int INDEX(initializer_list<T> list);

    // hàm thay đổi giá trị

    // hàm reshape để duỗi mảng(?)
    void reshape(int _dim);
    MultiDimArray reshapeTo2Dim();
    
    // nạp chồng toán tử * cho việc nhân ma trận (2 mảng 2 chiều)
    MultiDimArray operator*(MultiDimArray &other);

    // nạp chồng toán tử () cho việc truy cập chỉ số mảng nhanh hơn 
    double* operator()(initializer_list<int> list);

    // nạp chồng toán tử + cho việc cộng từng hàng của ma trận 2 chiều với
    // một mảng một chiều cùng kích thước
    MultiDimArray operator+(MultiDimArray &other);

    // nạp chồng toán tử gán
    void operator=(MultiDimArray &other);

};

tuple<MultiDimArray,tuple <MultiDimArray, MultiDimArray, MultiDimArray>> linear_foward();


//below is my note for this project
/*
    https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

*/