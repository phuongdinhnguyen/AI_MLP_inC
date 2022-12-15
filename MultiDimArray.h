#include <iostream>
#include <cstring>
#include <vector>
#include <initializer_list>
#include <tuple>
#include <fstream>

#include <cstdarg>
#include <utility>

template<class... Args>
void func3(Args... args);

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
    MultiDimArray reshape(initializer_list<int> list);
    template<class... Args>
    MultiDimArray reshape(Args... args)
    {   
        MultiDimArray tmp = *this;
    
        vector <int> list;
        //(cout << ... << args) << endl;
        (list.push_back(forward<Args>(args)),...);
        //cout << list.size();

        vector <int> shape;
        int length = 1;
        tmp.dim = list.size();
        for (int d : list)
        {
            length *= d;
            shape.push_back(d);
        }
        tmp.initLength = length;
        tmp.sub = shape;

        return tmp;
    }
    vector<int> shape();
    MultiDimArray reshape(vector<int> list);
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

    // tính ma trận chuyển vị
    MultiDimArray transpose();
};

tuple<MultiDimArray,tuple <MultiDimArray, MultiDimArray, MultiDimArray>> linear_foward();

// sinh ra mảng 1 chiều fill toàn số 1
MultiDimArray ones(int shape);

template<class... Args>
MultiDimArray reshape4(Args... args);



//below is my note for this project
/*
    https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

*/