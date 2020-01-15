# Sort
## Selection Sort
+ 平均时间复杂度：O(N^2)
+ 最坏时间复杂度：O(N^2)
+ 空间复杂度：O(1)
+ 稳定性：不稳定(相同大小的元素，经过排序，原有的相对顺序没有改变, 就是稳定)
+ 使用场景：一般不用，效率一般，优点是实现简单。
```cpp
void selectionSort(vector<int>& a)
{
    int size = a.size();
    for (int i = 0; i < size; ++i)
    {
        int min = i;
        for (int j = i+1; j < size; ++j)
        {
            if (a[j] < a[min])
                min = j;
        }
        exch(a, min, i);
    }
}
```

## Insertion Sort
+ 平均时间复杂度：O(N^2)
+ 最坏时间复杂度：O(N^2)
+ 空间复杂度：O(1)
+ 稳定性：稳定
+ 使用场景：对部分有序、小数组效率很高
```cpp
void InsertionSort(std::vector<int>& a)
{
    int size = a.size();
    for (int i = 1; i < size; ++i)
    {
        for (int j = i; j > 0 && a[j] < a[j-1]; --j)
            exch(a, j, j-1);
    }
}
```

## Shell Sort
+ 平均时间复杂度：O(NlgN),取一个合适的h
+ 最坏时间复杂度：不超过O(N^2)
+ 空间复杂度：O(1)
+ 稳定性：不稳定
+ 使用场景：代码简单，适合中型数组。排序前每个序列规模小，排序后每个序列部分有序
```cpp
void shellSort(std::vector<int>& a)
{
    int N = a.size();
    int h = 1;
    while (h < N/3)
    {
        h = 3 * h + 1;
    }

    while (h > 0)
    {
        for (int i = h; i < N; ++i)
        {
            for (int j = i; j >= h && a[j] < a[j-h]; j = j - h)
                exch(a, j, j-h);
        }
        h = h / 3;
    }
}
```

## Merge Sort
+ 平均时间复杂度：O(NlgN), 比希尔排序要快
+ 最坏时间复杂度：O(NlgN)
+ 空间复杂度：O(N)
+ 稳定性：稳定
+ 使用场景：大型数组
```cpp
void mergSort(std::vector<int>& a)
{
    vector<int> aux;
    int N = a.size();
    aux.reserve(N);
    mergeSort(a, aux, 0, N-1);
}

void mergSort(std::vector<int>& a, vector<int>& aux,
                int lo, int hi)
{
    // 小数组用insertionSort
    if (hi <= lo + M)
    {
        insertionSort(a, lo, hi);
        return ;
    }

    int mid = lo + (hi - lo) / 2;
    mergeSort(a, aux, lo, mid);
    mergSort(a, aux, mid+1, hi);
    merge(a, aux, lo, mid, hi);
}

void merge(std::vector<int>& a, vector<int>& aux,
                int lo, int hi)
{
    if (a[mid] < a[mid+1])
        return ;

    // copy to aux
    for (int i = lo; i <= hi; ++i)
        aux[i] = a[i];

    int pa = lo;
    int pb = mid+1;
    for (int k = lo; k <= hi; ++k)
    {
        if (pb > hi) a[k] = aux[pb++];
        else if (pa > mid) a[k] = a[pa++];
        else if (aux[pa] < a[pb]) a[k] = aux[pa++];
      else a[k] = aux[pb++];
    }
}

// not recursive method
void mergeSort(std::vector<int>& a, vector<int>& aux,
                int lo, int hi)
{
    // sz is childArray's size,it is already ordered
    for (int sz = 1; sz < hi - lo + 1; sz = 2 * sz)
    {
        for (int j = lo; j + sz - 1 < hi; j = j + 2 * sz)
        {
            merge(a, aux, j, j+sz-1, min(j+2*sz-1, hi));
        }
    }
}
```

## 快速排序
+ 平均时间复杂度：O(NlgN)
+ 最坏时间复杂度：O(N^2)
+ 空间复杂度：O(NlgN),递归实现需要栈空间
+ 稳定性：不稳定
+ 使用场景：各种数组都可
```cpp
/*
|v|                |
|v| <= v|    | >=v |
|<=v     |v|   >=v |
*/

void quickSort(std::vector<int>& a, int lo, int hi)
{
    // 小数组用插入排序, M = 10
    if (hi <= lo + M)
    {
        return insertionSort(a, lo, hi);
    }

    // 消除对输入的依赖，取三数中值作为pivot
    // lo mid hi做如下安排，最小的放在lo处，中位数也就是pivot放在hi-1
    // 最大的数放在hi
    // 这样循环中可以不用对边界进行检查
    int pivot = median3(a, lo, hi);
    int i = lo, j = hi - 1;
    while (true)
    {
        while (a[++i] < pivot) ;
        while (a[--j] > pivot) ;
        if (i >= j) break;
        exch(a, i, j);
    }
    exch(a, i, hi-1);

    quickSort(a, lo, i-1);
    quickSort(a, i+1, hi);
}

int median3(std::vector<int>& a, int lo, int hi)
{
    int mid = lo + (hi - lo) / 2;
    if (a[lo] > a[mid])
    {
        exch(a, lo, mid);
    }
    if (a[mid] > a[hi])
    {
        exch(a, mid, hi);
    }
    if (a[lo] > a[mid])
    {
        exch(a, lo, mid);
    }
    exch(a, mid, hi-1);
    return a[hi-1];
}
```

## 堆排序
