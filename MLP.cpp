#include "MultiDimArray.h"

tuple<MultiDimArray,tuple <MultiDimArray, MultiDimArray, MultiDimArray>> 
linear_forward(MultiDimArray x, MultiDimArray w, MultiDimArray b);

template <typename T>
tuple <MultiDimArray,MultiDimArray,MultiDimArray> 
linear_backward(MultiDimArray dout, T cache);

tuple <MultiDimArray, MultiDimArray> relu_forward(MultiDimArray x);

MultiDimArray relu_backward(MultiDimArray dout, MultiDimArray cache);

tuple <MultiDimArray, tuple<tuple<MultiDimArray, MultiDimArray,MultiDimArray>,MultiDimArray>> 
linear_relu_forward(MultiDimArray x, MultiDimArray w, MultiDimArray b);

template <typename T>
tuple <MultiDimArray, MultiDimArray, MultiDimArray> 
linear_relu_backward(MultiDimArray dout, T cache);

tuple <MultiDimArray, MultiDimArray> 
softmax_loss(MultiDimArray _logits, MultiDimArray y);

class TwoLayerNet
{
public:
    int input_dim = 3*32*32;
    int hidden_dim = 100;
    int num_classes = 10;
    double weight_scale = 1e-3;
    typedef struct TLN
    {
        MultiDimArray W1;
        MultiDimArray W2;
        MultiDimArray b1;
        MultiDimArray b2;
    } TLN;
    
    TLN params;

    TwoLayerNet(){
        cout << "hello MLP \n";
        vector <int> W1_shape = {input_dim, hidden_dim};
        MultiDimArray W1 = nc::random_normal(0, weight_scale, {input_dim, hidden_dim});
        MultiDimArray b1 = nc::zeros({hidden_dim});
        MultiDimArray W2 = nc::random_normal(0, weight_scale, {hidden_dim, num_classes});
        MultiDimArray b2 = nc::zeros({num_classes});

        params.W1 = W1;
        params.W2 = W2;
        params.b1 = b1;
        params.b2 = b2;
    };

    TwoLayerNet(int _input_dim, int _hidden_dim, int _num_classes, double _weight_scale){
        
        input_dim = _input_dim;
        hidden_dim = _hidden_dim;
        num_classes = _num_classes;
        weight_scale = _weight_scale;
        
        vector <int> W1_shape = {input_dim, hidden_dim};
        MultiDimArray W1 = nc::random_normal(0, weight_scale, {input_dim, hidden_dim});
        MultiDimArray b1 = nc::zeros({hidden_dim});
        MultiDimArray W2 = nc::random_normal(0, weight_scale, {hidden_dim, num_classes});
        MultiDimArray b2 = nc::zeros({num_classes});

        cout << "create W1\n" ;
        // W1.printArr();

        params.W1 = W1;
        params.W2 = W2;
        params.b1 = b1;
        params.b2 = b2;
    };

        MultiDimArray loss(MultiDimArray _X, MultiDimArray _y){
            auto lrf = linear_relu_forward(_X, params.W1, params.b1);
            auto X = get<0>(lrf);
            auto cache1 = get<1>(lrf);
            
            // cout << "model.params.W2 = " << endl;
            // params.W2.printShape();

            // cout << "linear forward:\n";
            auto lf = linear_forward(X, params.W2, params.b2);
            auto scores = get<0>(lf);
            auto cache2 = get<1>(lf);

            // if (_y.dim == 0) 
            return scores;

            // auto sl = softmax_loss(scores, _y);
            // auto loss = get<0>(sl);
            // auto dout = get<1>(sl);

            // auto lb = linear_backward(dout, cache2);
            // dout = get<0>(lb);
            // auto dW2 = get<1>(lb);
            // auto db2 = get<2>(lb);

            // auto lrb = linear_backward(dout, cache1);
            // dout = get<0>(lb);
            // auto dW1 = get<1>(lb);
            // auto db1 = get<2>(lb);

            // TLN grads;
            // grads.W1 = dW1;
            // grads.W2 = dW2;
            // grads.b1 = db1;
            // grads.b2 = db2;

            // return make_tuple(loss, grads);
    }

};
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
    // READ FROM TEXT
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


    /*-------Test the linear_backward() function!-------*/
    // cout << "Start debugging linear_backward()\n";
    // MultiDimArray x = MultiDimArray(3,{10,2,3});
    // MultiDimArray w = MultiDimArray(2,{6,5});
    // MultiDimArray b = MultiDimArray(1,{5});
    // MultiDimArray dout = MultiDimArray(2,{10,5});

    // x.readFromFile("data_x_lb.txt");
    // w.readFromFile("data_w_lb.txt");
    // b.readFromFile("data_b_lb.txt");
    // dout.readFromFile("data_dout_lb.txt");

    // MultiDimArray dx = MultiDimArray(3,{10,2,3});
    // MultiDimArray dw = MultiDimArray(2,{6,5});
    // MultiDimArray db = MultiDimArray(1,{5});

    // auto lf = linear_forward(x, w, b);
    // auto cache = get<1>(lf);
    // auto lb = linear_backward(dout, cache);
    // dx = get<0>(lb);
    // dw = get<1>(lb);
    // db = get<2>(lb);
    // cout << "dx = " << endl;
    // dx.printArr();
    // cout << "dw = " << endl;
    // dw.printArr();
    // cout << "db = " << endl;
    // db.printArr();

    /*-------Test the relu_forward() function!-------*/
    // MultiDimArray z = nc::linspace(-0.5,0.5,12).reshape({3,4});
    // auto reluf = relu_forward(z);
    // auto out = get<0>(reluf);
    // out.printArr();

    /*-------Test the relu_backward() function!-------*/
    // MultiDimArray x = MultiDimArray(2,{10,10});
    // x.readFromFile("data_x_relub.txt");
    // MultiDimArray dout = MultiDimArray(2,{10,10});
    // dout.readFromFile("data_dout_relub.txt");
    // //dout.printArr();
    // auto reluf = relu_forward(x);
    // auto cache = get<0>(reluf);
    // auto dx = relu_backward(dout,cache);
    // dx.printArr();

    /*-------Test full forward implementation function!-------*/
    int N = 3, D = 5, H = 50, C = 7;
    MultiDimArray X = MultiDimArray(2,{N, D});
    MultiDimArray y = MultiDimArray(1,{C});

    X.readFromFile("data_x_ff.txt");
    y.readFromFile("data_y_ff.txt");
    double std = 1e-3;

    TwoLayerNet model = TwoLayerNet(D,H,C,std);

    cout << "Testing initialization..." << endl;
    auto W1_std = abs(model.params.W1.std() - std);
    auto b1 = model.params.b1;
    auto W2_std = abs(model.params.W2.std() - std);
    auto b2 = model.params.b2;

    if (W1_std > std/10) cout << "First layer weights do not seem right \n";
    if (W2_std > std/10) cout << "Second layer weights do not seem right \n";
    cout << "W1_std = " << W1_std << endl;
    cout << "W2_std = " << W2_std << endl;

    cout << "Testing test-time forward pass..." << endl;
    model.params.W1 = nc::linspace(-0.7,0.3,D*H).reshape({D,H});
    model.params.b1 = nc::linspace(-0.1,0.9,H);
    model.params.W2 = nc::linspace(-0.3,0.4,H*C).reshape({H,C});
    model.params.b2 = nc::linspace(-0.9,0.1,C);
    X = nc::linspace(-5.5,4.5,N*D);
    X = X.reshape({D,N});
    X = X.transpose();
    // cout << "-> X shape:\n";
    // X.printShape();

    cout << "--------Calculating scores:----------\n";
    auto scores = model.loss(X, y);
    scores.printArr();


    //-------Test std() function--------//
    // MultiDimArray x = MultiDimArray(2,{2,2});
    // x(0,0) = 1; x(0,1) = 2; 
    // x(1,0) = 3; x(1,1) = 4;
    // cout << "x std = " << x.std() << endl; // result should be 1.1180339887498949

    // dx.readFromFile("data_dx_lb.txt");
    // dw.readFromFile("data_dw_lb.txt");
    // db.readFromFile("data_db_lb.txt");

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
    // MultiDimArray x = MultiDimArray(2,{3,4});
    // MultiDimArray y = MultiDimArray(1,{12});
    // x.readFromFile("data_test.txt");
    // y.readFromFile("data_test.txt");
    // x(1,1) = 4;
    // cout << x(1,1) << endl;
    // cout << y(9) << endl;

    //------Test linspace function ---//
    // nc::linspace(2.0,3.0,5).printArr();

    //--Test random normal distribution---//
    // vector <int> sub = {10,2,3};
    // MultiDimArray rand = nc::random_normal(0, 1,sub);
    // rand.printArr();

    cout << "Program exited!" << endl;
    return 0;
}

tuple<MultiDimArray,tuple <MultiDimArray, MultiDimArray, MultiDimArray>> 
linear_forward(MultiDimArray x, MultiDimArray w, MultiDimArray b)
{
    int num_examples = x.shape()[0];
    MultiDimArray flattened_x = x.reshape({num_examples, -1});
    
    // flattened_x.printShape();
    // w.printShape();
    MultiDimArray out = flattened_x * w + b;

    // out.printArr();
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

    MultiDimArray flattened_x_t = flattened_x.transpose();
    MultiDimArray dw = flattened_x_t * dout;
    MultiDimArray db = ones(num_examples) * dout;

    MultiDimArray w_t = w.transpose();
    MultiDimArray dx = dout * w_t;

    MultiDimArray dx_a = dx.reshape(x.shape());

    return make_tuple(dx_a,dw,db);
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

MultiDimArray relu_backward(MultiDimArray dout, MultiDimArray cache)
{
    auto x = cache;
    MultiDimArray mask = MultiDimArray(x.dim,{x.sub[0],x.sub[1]});

    cout << "dout before=" << endl;
    dout.printArr();

    // Implement: mask = (x > 0).astype(int)
    for (int i = 0 ; i < x.initLength ; i++)
    {
        if (x.arr[i] > 0) mask.arr[i] = 1;
        else mask.arr[i] = 0;
    }

    MultiDimArray dx = MultiDimArray(x.dim,{x.sub[0],x.sub[1]});

    for (int i = 0 ; i < dx.initLength ; i++)
    {
        if (mask.arr[i] == 1) dx.arr[i] = dout.arr[i];
        else dx.arr[i] = 0;
    }

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

tuple <MultiDimArray, MultiDimArray> 
softmax_loss(MultiDimArray _logits, MultiDimArray y)
{
    MultiDimArray logits = _logits;
    
    // Implement: logits -= np.max(logits,axis=1,keepdims=True)
    for (int i = 0 ; i < logits.sub[0] ; i++)
    {
        double row_max = logits(i,0);
        for (int j = 0 ; j < logits.sub[1] ; j++)
        {
            if (row_max < logits(i,j)) row_max = logits(i,j);
        }

        for (int j = 0 ; j < logits.sub[1] ; j++)
        {
            logits(i,j) = logits(i,j) - row_max;
        }
    }

    MultiDimArray exps = expp(logits);
    MultiDimArray sums = sum(exps, 1);
    MultiDimArray probs = exps;

    for (int i = 0 ; i < exps.sub[0] ; i++)
    {
        for (int j = 0 ; j < logits.sub[1] ; j++)
        {
            probs(i,j) = probs(i,j) / sums(i);
        }
    }

    for (int i = 0 ; i < probs.sub[0] ; i++)
    {
        for (int j = 0 ; j < probs.sub[1] ; j++)
        probs(i,j) = probs(i,j) / exp(i);
    }

    // Implement: loss = -np.log(probs[range(len(y)), y])
    auto loss = y;
    for (int i = 0 ; i < loss.sub[0] ; i++)
    {
        loss(i) = log(probs(i,y(i)));
    }

    // Implement: loss = np.mean(loss)
    double loss_sum = 0;
    for (int i = 0 ; i < loss.sub[0] ; i++)
    {
        loss_sum += loss(i);
    }

    for (int i = 0 ; i < loss.sub[0] ; i++)
    {
        loss(i) = loss(i) / loss_sum;
    }

    // Implement: probs[range(len(y)), y] -= 1
    for (int i = 0 ; i < y.sub[0] ; i++)
    {
        probs(i,y(i)) = probs(i,y(i)) - 1;
    }

    // Implement: dlogits = probs / len(y)
    auto dlogits = probs;
    for (int i = 0 ; i < y.initLength ; i++)
    {
        dlogits.arr[i] = probs.arr[i] / y.initLength;
    }

    return make_tuple(loss,dlogits);
}


