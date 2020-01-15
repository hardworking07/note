# Hash Table
## 哈希表的特性
+ 哈希表插入、删除、查找都是常数时间
+ 哈希表内的元素并不按照顺序排列

## 创建哈希表
+ 哈希表的大小如何选择
+ 理想的散列函数：计算简单，能够均匀分配各个关键字，没有冲突
+ 但实际上理想散列函数不存在。所以，如何处理冲突也是必须要考虑的

## 散列函数
1. Integer

tableSize is a prime
$$ key \bmod tableSize $$

2. String
```cpp
Index hash(const char* key, int tableSize)
{
    unsigned int hashVal = 0;
    while (*key != '\0')
    {
        hashVal = (hashVal << 5) + *key++;
    }
    return hashVal % tableSize;
}
```

## 冲突处理
### 分离链接法
+ 具有相同index的key保存在一个同一个链表中
+ 当新的元素插入时，把这个新元素插入表头（或表尾）
+ 查找的平均时间复杂度：$1+\lambda/2$, $\lambda$是表的平均长度
+ 因此，把tableSize取一个和预计的元素个数接近的素数值($\lambda \approx 1$)

```cpp
class HashTable
{
public:
    HashTable(int size);
    bool find(const string& key);
    bool insert(const string& key);

private:
    bool find(const string& key, int tableSize);
    bool insert(const string& key, int tableSize);
private:
    int m_size;
    vector<ListNode*> m_table;
};

HashTable::HashTable(int size)
:m_size(size)
{
    m_table.reserve(m_size);
    // header,
    ListNode* tmp = new ListNode();
    for (int i = 0; i < m_size; ++i)
    {
        m_table.push_back(tmp);
    }
}

bool HashTable::insert(const string& key, int tableSize)
{
    int index = hash(key, tableSize);
    ListNode* tmp = new ListNode(key);
    tmp->next = m_table[index]->next;
    m_table[index]->next = tmp;
    return true;
}
```

### 开放定址法
分离链表法，需要给新的元素分配空间，算法较慢

#### 平方探测法
$$ H(x) + F(i)$$
$$F(i) = i^2$$
