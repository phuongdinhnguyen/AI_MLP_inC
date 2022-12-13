#include "MultiDimArray.h"

template <class T>
MultiDimArray::MultiDimArray(int _numOfDim, initializer_list<T> list)
{
    if (list.size() != _numOfDim)
    {
        cout << "Error in declare size of dim!" << endl;
    }
    else
    {
        dim = _numOfDim;
        //cout << "Num of dim = " << _numOfDim << endl;
        
        cout << "MultiDimArr created! Shape of arr: ( ";
        for( auto elem : list )
        {
            std::cout << elem << " ";
            sub.push_back(elem);
            initLength *= elem;
            // cout << "aa" << endl;
        }
        cout <<") -> " << initLength << "; " << "size: "<< sub.size() << "\n";
        if (dim == 1) sub.push_back(1);

        arr = new double[initLength];
        
    }

}

// MultiDimArray::~MultiDimArray()
// {
//     delete arr;
// }

void MultiDimArray::initArray()
{
    //cout << "size of arr: " << sizeof(arr) << endl;
    memset(arr,0,sizeof(arr)*initLength);
}

void MultiDimArray::printArr()
{
    for (int i = 0 ; i < initLength ; i++)
    {
        cout << arr[i] << " ";
        if (dim != 1 && i % sub[1] == (sub[1]-1)) cout << endl;
    }
    cout << endl;
}

template <typename T>
int MultiDimArray::INDEX(initializer_list<T> list)
{
    /*
        usage: calculate position of array element
        example:
            find index of element which position in multidimarray (3,2,3) is (2,0,2)
            -> index = 2*2*3 + 0*3 + 2 = 14 
        formula: 
            multidimarray (d1,d2,d3,...,dn), element(x1,x2,x3,...,xn)
            -> index = x1*(d2*d3*...*dn) + x2*(d3*d4*...*dn) +... + xn-1 * dn + xn 
    */

    int idx = 0;
    int arrIdx = 0;

    for( auto elem : list )
    {
        if (dim == 1) return elem;
        if (elem > sub[idx] - 1)
        {
            cout << "Element out of range!" << endl;
            break;
        }
        else
        {
            if (idx == dim - 1) arrIdx += elem;
            else
            {
                arrIdx += elem*sub[idx+1];
            }
        }
        idx++;
    }
    return arrIdx;
}

double* MultiDimArray::operator()(initializer_list<int> list)
{
    //cout << "arr+this->INDEX(list) = " << arr+this->INDEX(list) << endl;
    //cout << "INDEX(list) = " << INDEX(list) << endl;
    return arr+this->INDEX(list);
}

MultiDimArray MultiDimArray::operator+(MultiDimArray &other)
{
    if (this->sub[1] != other.sub[0])
    {
        cout << "Cannot do plus operator!" << endl;
    }
    else
    {
        MultiDimArray tmp = *this;
        for (int i = 0 ; i < this->sub[0] ; i++)
        {
            for (int j = 0 ; j < this->sub[1] ; j++)
            *tmp({i,j}) += *other({j});
        }
        return tmp;
    }
    // return MultiDimArray();
}

MultiDimArray MultiDimArray::reshapeTo2Dim()
{
    MultiDimArray tmp = *this;
    int rowLength = 1;
    if (tmp.dim < 3)
    {
        cout << "Cannot reshape this!" << endl;
    }
    while (tmp.dim > 1){
        //cout << tmp.dim << endl;
        //cout << "reshaping...\n";
        rowLength *= tmp.sub[tmp.dim-1];
        tmp.sub.pop_back();
        tmp.dim--; 
    }
    tmp.dim++;
    //cout << "row length = " << rowLength << endl;
    tmp.sub.push_back(rowLength);
    //cout << "dim = " << tmp.dim << ", " << tmp.sub[0] << " " << tmp.sub[1] << endl;

    return tmp;
}

MultiDimArray MultiDimArray::operator*(MultiDimArray &other)
{
    if ((this->dim !=2) && (other.dim != 2))
    {
        cout << "Cannot multiply matrix! Dim is not equal to 2!";
    }
    else
    {
        if (this->sub[1] != other.sub[0])
        {
            cout << "Cannot multiply. First matrix column is not equal to second matrix row!" << endl;
        }
        else
        {
            //if (other.dim == 1) other.sub.push_back(1);
            //if (this->dim == 1) this->sub.push_back(1);
            MultiDimArray res = MultiDimArray(2,{this->sub[0],other.sub[1]});
            MultiDimArray cur = *this;
            // multiply (N,D) * (D,M) = (N,M)
            int N = this->sub[0];
            int D = this->sub[1];
            int M = other.sub[1];
            res.initArray();
            for (int i = 0 ; i < N ; i++)
            {
                for (int j = 0 ; j < M ; j++)
                {
                    for (int k = 0 ; k < D ; k++)
                    *res({i,j}) += (*cur({i,k})) * (*other({k,j}));
                }
            }
            return res;
        }
    }
}

void MultiDimArray::operator=(MultiDimArray &other)
{
    arr = new double [initLength];
    
    for (int i = 0 ; i < other.initLength ; i++)
    {   
        *(arr+i) = *(other.arr+i);
    }
    *arr = *other.arr;

    initLength = other.initLength;
    dim = other.dim;
    sub = other.sub;
}

void MultiDimArray::readFromFile(string _dir)
{
    ifstream file(_dir);
    double tmp;
    for (int i = 0 ; i < initLength ; i++)
    {
        file >> tmp;
        arr[i] = tmp;
    }
}