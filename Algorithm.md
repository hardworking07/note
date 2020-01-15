## Introduction
1. Euclid's Algorithm for computing gcd(m,n)
$$m = p * n + q \quad \text{$0 \le q < n$}$$
$$gcd(m,n) = gcd(n, m \mod n)$$

```cpp
int gcd(int m, int n)
{
   while (n > 0)
   {
       m = n;
       n = m % n;
   }
   return m;
}
```

2. Sieve for prime numbers
+ prepare an array num[n+1], 0 if it's prime number, 1 if it's composite number
+ 质数的p(p > 1)倍，都是合数
+ 2p(p > 1) is prime number
+ 3p(p > 1) is
+ 对于4，由于已经被标记为合数，所以不用考虑
+ 重复以上操作，直到n
+ 优化点：对于一个质数 p，只要从 p*p 开始标记就可以了，前面的数其实都已经被标记过了

```cpp
// count the number of all prime numbers <= n
int sieve(int n)
{
   int* arr = new int[n+1]();
   for (int i = 2; i * i <= n; ++i)
   {
       if (arr[i]) continue;
       for (int j = i; i * j <= n; ++j)
       {
           arr[i*j] = 1;
       }
   }
   int ans = 0;
   for (int i = 2; i <= n; ++i)
   {
       if (0 == arr[i])
       {
           ++ans;
       }
   }
   return ans;
}
```

3.
## Dynamic Programming
动态规划是对递归计算的优化，用来解决递归计算中重复计算的问题。

有2种思路：
+ 找到递推关系，并从底向上计算，这样所有问题都只会被计算一次。缺点是每一个较小的子问题都会被计算，即使是不需要的
+ 找到递推关系，带记忆表的自顶向下计算。

用动态规划求解最优化问题有个一般性法则：**最优化法则**。即问题的最优解，是由其子问题的最优解构成。这个法则为求解此类问题提供了非常好的思路。这个法则并不总是正确，需要检验一下。
