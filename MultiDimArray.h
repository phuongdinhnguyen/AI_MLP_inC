#include <iostream>
#include <cstring>
#include <vector>
#include <initializer_list>
#include <tuple>
#include <fstream>
#include <chrono>

#include <cstdarg>
#include <utility>

#include <math.h>
#include <random>

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
    int err[1] = {-99};
    double *arr = NULL;

public:
    template <typename T>
    MultiDimArray(int _numOfDim, initializer_list<T> list);
    MultiDimArray(){
        dim = 0;
    }
    // ~MultiDimArray();
    // khởi tạo giá trị 0 cho toàn mảng
    void initArray();

    // in ra mảng (chỉ áp dụng 2 chiều)
    void printArr();

    // read from files
    void readFromFile(string _dir);

    // tìm chỉ số so với array 1D
    // template <typename T>
    // int INDEX(T list);

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

    // nạp chồng toán tử () style numpy (testing) 
    template <class... Args>
    double& operator()(Args... args)
    {
        vector<int> list;
        (list.push_back(forward<Args>(args)),...);
        int idx = 0;
        int arrIdx = 0;

        // if (list.size() != dim) return err[0];
        for( auto elem : list )
        {
            // cout << "elem = " << elem << endl;
            if (dim == 1)
            {
                arrIdx = elem;
                break;
            }
            if (elem > sub[idx] - 1)
            {
                cout << "Element out of range!" << endl;
                // return err[0];
                break;
            }
            else
            {
                if (idx == dim - 1) 
                {
                    arrIdx += elem;
                }
                else
                {
                    arrIdx += elem*sub[idx+1];
                }
            }
            idx++;
        }
        return arr[arrIdx];
    }

    // nạp chồng toán tử + cho việc cộng từng hàng của ma trận 2 chiều với
    // một mảng một chiều cùng kích thước
    MultiDimArray operator+(MultiDimArray &other);

    // nạp chồng toán tử gán
    void operator=(const MultiDimArray &other);

    // tính ma trận chuyển vị
    MultiDimArray transpose();

    // tính standard deviation
    double std();

    // in ra shape của mảng
    void printShape();
};

tuple<MultiDimArray,tuple <MultiDimArray, MultiDimArray, MultiDimArray>> linear_forward();

// sinh ra mảng 1 chiều fill toàn số 1
MultiDimArray ones(int shape);

// hàm exp để.... e mũ tất cả các giá trị của mảng :))))
MultiDimArray expp(MultiDimArray _ma);

MultiDimArray sum(MultiDimArray _ma, int axis);

//below is my note for this project
/*
    https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

*/


namespace nc
{
    MultiDimArray linspace(double _start, double _stop, double _num);
    MultiDimArray zeros(vector <int> shape);
    MultiDimArray random_normal(double mean, double stddev, vector <int> shape);

}