# List
## SinglelyList
### 链表数据结构
```cpp
typedef struct SinglelyListNode
{
    int val;
    struct SinglelyListNode* next;
    SinglelyListNode(int x): val(x), next(NULL){}
}SinglelyListNode;

class SinglelyList
{
public:
    SinglelyList():header(NULL),m_size(0) {}
    SinglelyListNode* header;

    int front();
    int back();
    int size();
    bool empty();
    void clear();
    SinglelyListNode* insert(SinglelyListNode* pos, int val);
    SinglelyListNode* erase(SinglelyListNode* pos);
    void merge(SinglelyList* other);

    }

private:
    int m_size;
};
```

### 单链表数据结构图
header---> L1 ---> L2 ---> L3 ...LN ---> NULL

### 基本操作
```cpp
// 初始化
SinglelyList l = SinglelyList();
l.header = new SinglelyListNode(0);

int SinglelyList::front()
{
    if (header->next)
    {
        return header->next->val;
    }
    return -1;
}

int SinglelyList::back()
{
    SinglelyListNode* p = header;
    while (p->next)
    {
        p = p->next;
    }
    return p->val;
}

int SinglelyList::size()
{
    return m_size;
}

bool SinglelyListNode::empty()
{
    return (0 == m_size);
}

void SinglelyList::clear()
{
    while (header->next)
    {
        SinglelyListNode* p = header->next;
        header->next = header->next->next;
        delete p;
    }
    m_size = 0;
}

// insert before pos
// if pos==NULL, insert at the end
SinglelyListNode* SinglelyList::insert(SinglelyListNode* pos, int val)
{
    SinglelyListNode* p = header;
    while (p && p->next != pos)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        return NULL;
    }
    SinglelyListNode* tmp = new SinglelyListNode(val);
    tmp->next = pos;
    p->next = tmp;
    ++m_size;
    return tmp;
}

// erase pos, and return the next pointer
SinglelyListNode* SinglelyList::erase(SinglelyListNode* pos)
{
    if (!pos)
    {
        return NULL;
    }
    SinglelyListNode* p = header;
    while (p && p->next != pos)
    {
       p = p->next;
    }
    if (!p)
    {
        return NULL;
    }
    p->next = p->next->next;
    delete pos;
    --m_size;
    return p->next;
}

void SinglelyList::push_back(int val)
{
    insert(NULL, val);
}

void SinglelyList::pop_back()
{

}

void SinglelyList::push_front(int val)
{
    insert(header->next, val);
}

void SinglelyList::pop_front()
{
    erase(header->next);
}

void SinglelyList::merge(SinglelyList* other)
{

}
```
