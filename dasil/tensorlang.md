# Ideas for a forntend for tensor expressions

Lets look at a concoreate example of writing a tensor expression to implement convolution kernel.

```
def conv( 
  X : Tensor<float, n, ci, h, w>,  // 4D input, batch_size, input_channels, height and width
  W : Tensor<float, co, ci, kernel_h, kernel_w> // 4D input filter 
  b : Tensor<float, co>) : Tensor<float, n, co, ho, wo> {
 conv(n, co, ho, wo) = Sum(X(n, kci, stride_h * ho + kh, strid_h * w + kw) * W(co, kci, kh, kw), kh = {0, kernel_h}, kw = {0, kernel_w});
 conv_with_bias(_, co, :) = conv + b(co);
 return conv_with_bias;
} 
```

- `(n, ci, h, w) , (co, kci, kh, kw), (n, co, ho, wo)` are the domain acessors for the input tensor, they are created implicitly (left -> right).

- Tensor expressions assigments on the r.h.hs are going to define the l.h.s values e.g at the above example algebrically :

```
ho = ci - kh / stride_h + 1;
```

- Assume tensor expressions are SSA. and with reduction functions we can do what we want.
