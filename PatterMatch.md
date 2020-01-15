# 模式匹配
在字符串TXT中寻找模式字符串pat，返回其位置；如果失败，返回-1.

类似题目：[28 Implement strStr()](https://leetcode-cn.com/problems/implement-strstr/)

## 几种匹配算法的比较
模式匹配的问题，很依赖于输入。

| Name       | 一般时间复杂度                 | 最坏时间复杂度 | 空间复杂度      |
| ---------- | ------------------------------ | -------------- | --------------- |
| 暴力匹配   | 1.1N，一般第一个字符就不匹配了 | O(MN)          | O(1)            |
| BM         | N/M                            | MN             | O(R),字符表大小 |
| Rabin-Karp | O(N),概率上保证                | O(N)           | O(1)            |
|            |                                |                |                 |



## 暴力匹配
### 算法解析
+ 比较成功，文本字符串和模式字符串都移动到下一个
+ 比较失败，文本字符串和模式字符串都需要回退
+ 一般时间复杂度：1.1N，因为大多数在比较第一个字符时就失败了
+ 最坏时间复杂度：MN
+ 空间复杂度:O(1)
+ 适用场景：一般情况可以直接用暴力算法，实际上strstr()就是这么实现的

### 代码实现
```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty())
        return 0;

        int N = haystack.size();
        int M = needle.size();
        int i = 0, j = 0;
        while (i <= N - M && j < M)
        {
            if (haystack[i+j] == needle[j])
            {
                j++;
            }
            else
            {
                i = i + 1;
                j = 0;
            }
        }
        if (M == j)
        return i;
        else
        return -1;
    }
};
```
## KMP

## BM
### 算法解析
+ 暴力算法中每次匹配失败，文本字符串只向右移动一个字符，BM就是在这一块进行优化
+ 建立right表，存放每一个字符在模式字符串pat中的最右位置，对于pat中不存在的字符位置是-1
+ 从模式字符串的最后位置开始比较，成功，模式字符串指针j向左移动一位
+ 比较失败，文本字符串指针i向右移动j - right[pat[i+j]],模式字符串指针j退到最后一位
+ 一般时间复杂度：O(N/M)
+ 最坏时间复杂度:O(MN)
+ 空间复杂度：O(R)
+ 适用场景：

### 代码实现
```cpp
// 建立right数组：字符表每一个字符在模式字符串中的最右位置，不存在就是-1
void buildNext(const string& pat, char* right, int len)
{
    for (int i = 0; i < len; ++i)
    {
        right[i] = -1;
    }
    for (int i = 0; i < pat.size();++i)
    {
        right[pat[i]] = i;
    }
}

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty())
        return 0;

        // 建立right数组
        const int R = 128;
        char right[R];
        buildNext(needle, right, R);

        int N = haystack.size();
        int M = needle.size();
        int i = 0;
        int j = M - 1;
        while (i <= N-M && j >= 0)
        {
            if (haystack[i+j] == needle[j])
            {
                j--;
            }
            else
            {
                int skip = j - right[haystack[i+j]];
                i = (skip > 0 ? i + skip : i+1);
                j = M - 1;
            }
        }
        if (j < 0)
        return i;
        else
        return -1;
    }
};
```

## Rabin-Karp
### 算法解析
+ 暴力算法之所以消耗时间，是因为需要对模式字符串的M个字符挨个比较，有一个不一致就要回退。
+ 如果能够不用进行M次比较，直接判断是否相等，那么复杂度就可以大大降低。
+ Rabin-Karp算法，首先计算模式字符串的散列值；然后在遍历文本字符串的时候，依次计算M个字符的散列值
+ 如果散列值不等，字符串就不匹配；
+ 如果散列值相等，再比较两个字符串
+ 一般时间复杂度：O(N)
+ 最坏时间复杂度：O(N)
+ 空间复杂度：O(1)

### 代码实现
```cpp
// 字符串的hash值计算
// 将M长度的字符串看做一个R进制M位数，用一个大小为Q的散列表来保存
// 除留余数法, Q取一个很大的素数，减小不同字符串hash值相同的概率
// 注意数字太大可能会越界

const int R = 128;
const long long unsigned int Q = 2*3*5*7*11*13*17*19*23+1;

long long int getHash(const string& key, int M)
{
    long long unsigned int hashValue = 0;
    for (int i = 0; i < M; ++i)
    {
        // R是字符表的大小
        hashValue = (hashValue * R + key[i]) % Q;
    }
    return hashValue;
}

// hash值相同时，检查字符串是否相等
bool checkStr(const string& str1, const string& str2)
{
    // Q取很大，就可以用概率来保证
    return true;
}

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty())
            return 0;

        int M = needle.size();
        int N = haystack.size();
        if (N < M) return -1;

        // 计算needle的hash值
        long long unsigned int patHash = getHash(needle, M);

        // 计算RM，用于计算M个字符的hash值
        long long unsigned int RM = 1; // R^(M-1) % Q
        for (int i = 0; i < M - 1; ++i)
        {
            RM = (RM * R) % Q;
        }

        long long unsigned int txtHash = getHash(haystack, M);
        if (txtHash == patHash && haystack.substr(0,M) == needle)
            return 0;


        for (int i = 1; i <= N-M; ++i)
        {
            // hash值计算方法要注意一下
            txtHash = (txtHash - RM * haystack[i-1]%Q + Q) % Q;
            txtHash = (txtHash * R + haystack[i+M-1]) % Q;

            if (txtHash == patHash && haystack.substr(i,M) == needle)
            {
                return i;
            }
        }
        return -1;
    }
};
```
