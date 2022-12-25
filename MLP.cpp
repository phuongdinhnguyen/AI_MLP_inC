#include "MultiDimArray.h"
tuple<MultiDimArray,tuple <MultiDimArray, MultiDimArray, MultiDimArray>> linear_forward(MultiDimArray x, MultiDimArray w, MultiDimArray b);

int main()
{
    /*
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
    */


    /*-------Test the linear_forward() function!-------*/
    // // READ FROM TEXT
    // int num_inputs = 2;
    // int output_dim = 3;
    // MultiDimArray x = MultiDimArray(4, {2,4,5,6});
    // MultiDimArray w = MultiDimArray(2, {120,3});
    // MultiDimArray b = MultiDimArray(1, {3});

    // x.readFromFile("data_x.txt");
    // w.readFromFile("data_w.txt");
    // b.readFromFile("data_b.txt");

    // auto linear = linear_forward(x,w,b);
    // MultiDimArray out = MultiDimArray(2, {num_inputs, output_dim});
    // out = get<0>(linear);
    // out.printArr();

    //------Test reshape2-------//
    // MultiDimArray x = MultiDimArray(2,{10,6});
    // MultiDimArray x_r = x.reshape2({10,2,3});

    // cout << "After reshape: " << endl;
    // for (int i = 0 ; i <  x_r.sub.size() ; i++)
    // {
    //     cout << x_r.sub[i] << endl;
    // }

    //------Test reshape2 with array insert-------//
    // MultiDimArray x = MultiDimArray(2,{10,6});
    // vector <int> num_example{10,2,3};
    // cout << "Size of example: " << sizeof(num_example) << endl;
    // MultiDimArray y = MultiDimArray(3,{10,2,3});
    // MultiDimArray x_r = x.reshape(y.shape());
    // cout << "After reshape: " << endl;
    // for (int i = 0 ; i <  x_r.sub.size() ; i++)
    // {
    //     cout << x_r.sub[i] << endl;
    // }

    //------Test array access---------//
    MultiDimArray x = MultiDimArray(2,{3,4});
    x.readFromFile("data_test.txt");
    cout << x[1,3] << endl;

    cout << "Program exited!" << endl;
    return 0;
}

tuple<MultiDimArray,tuple <MultiDimArray, MultiDimArray, MultiDimArray>> 
linear_forward(MultiDimArray x, MultiDimArray w, MultiDimArray b)
{
    MultiDimArray flattened_x = x.reshapeTo2Dim();
    MultiDimArray out = flattened_x * w + b;

    out.printArr();
    auto cache = make_tuple(x,w,b);

    return make_tuple(out, cache);
}

template <typename T>
tuple <MultiDimArray,MultiDimArray,MultiDimArray> 
linear_backward(MultiDimArray dout, T cache)
{
    MultiDimArray x = get<0>(cache);
    MultiDimArray w = get<1>(cache);
    MultiDimArray b = get<2>(cache);

    int num_examples = x.sub[0];
    MultiDimArray flattened_x = x.reshapeTo2Dim();
    MultiDimArray dw = flattened_x.transpose() * dout;
    MultiDimArray db = ones(num_examples) * dout;

    MultiDimArray w_t = w.transpose();
    MultiDimArray dx = dout * w_t;
    dx = dx.reshape(x.shape());

    return make_tuple(dx,dw,db);
}

tuple <MultiDimArray, MultiDimArray> relu_forward(MultiDimArray x)
{
    MultiDimArray out = x;

    // Implement: out = np.where(x > 0, x, 0)
    for (int i = 0 ; i < out.initLength ; i++)
    {
        if (out.arr[i] < 0) out.arr[i] = 0;
    }

    auto cache = x;

    return make_tuple(out,cache);
}

template <typename T>
MultiDimArray relu_backward(MultiDimArray dout, MultiDimArray cache)
{
    auto x = cache;
    MultiDimArray mask = dout;

    // Implement: mask = (x > 0).astype(int)
    for (int i = 0 ; i < mask.initLength ; i++)
    {
        if (mask.arr[i] > 0) mask.arr[i] = 1;
        else mask.arr[i] = 0;
    }

    MultiDimArray dx = dout * mask;

    return dx;
}

tuple <MultiDimArray, tuple<tuple<MultiDimArray, MultiDimArray,MultiDimArray>,MultiDimArray>> 
linear_relu_forward(MultiDimArray x, MultiDimArray w, MultiDimArray b)
{
    auto a = get<0>(linear_forward(x,w,b));
    auto fc_cache = get<1>(linear_forward(x,w,b));

    auto out = get<0>(relu_forward(a));
    auto relu_cache = get<1>(relu_forward(a));

    auto cache = make_tuple(fc_cache, relu_cache);

    return make_tuple(out,cache);
}

template <typename T>
tuple <MultiDimArray, MultiDimArray, MultiDimArray> 
linear_relu_backward(MultiDimArray dout, T cache)
{
    auto fc_cache = get<0>(cache);
    auto relu_cache = get<1>(cache);
    
    auto da = relu_backward(dout, relu_cache);
    auto dx = get<0>(linear_backward(da, fc_cache));
    auto dw = get<1>(linear_backward(da, fc_cache));
    auto db = get<2>(linear_backward(da, fc_cache));

    return make_tuple(dx,dw,db);
}

template <typename T>
T softmax_loss(MultiDimArray _logits, MultiDimArray y)
{
    MultiDimArray logits = _logits;
    
    // Implement: logits -= np.max(logits,axis=1,keepdims=True)
    for (int i = 0 ; i < logits.sub[0] ; i++)
    {
        double row_max = *logits({i,0});
        for (int j = 0 ; j < logits.sub[1] ; j++)
        {
            if (row_max < (*logits({i,j}))) row_max = *logits({i,j});
        }

        for (int j = 0 ; j < logits.sub[1] ; j++)
        {
            *logits({i,j}) = *logits({i,j}) - row_max;
        }
    }

    MultiDimArray exps = expp(logits);
    MultiDimArray sums = sum(exps);
    MultiDimArray probs = exps;

    for (int i = 0 ; i < exps.sub[0] ; i++)
    {
        for (int j = 0 ; j < logits.sub[1] ; j++)
        {
            *probs({i,j}) = *probs({i,j}) / *sums({i});
        }
    }

}


