### 模运算
```
17 % 3 = ？
-17 % 3 = ?
-17 % -3 = ?
```

#### 整数除法取整
模运算的结果，其实就是除法之后的余数。
$$a = b * q + r, |r| \le |b|$$
所以，基于不同的取整方式r总会有正负两种选择。

+ 向上取整
+ 向下取整
+ 向零取整（Truncate）

#### cpp中的模运算
cpp中采用向零取整方式。
$$17 \bmod 3 = 17 - (17 / 3) * 3 = 2$$
$$-17 \bmod 3 = -17 -(-17/3) * 3 = -2$$
$$-17 \bmod -3 = -17 - (-17/-3) * -3 = -2$$
