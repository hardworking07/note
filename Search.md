# Search
## 有序数组的二分查找
+ 平均时间复杂度：O(lgN)
+ 最坏时间复杂度：O(lgN)
+ 空间复杂度:递归涉及栈空间, 若无递归则是O(1)
+ 适用场景：有序表
```cpp
// 返回的是小于key的数量
// [0 2 4 6 8 10]  key = 7, return 4(8)
int biSearch(int key, int lo, int hi)
{
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (key > vec[mid])  lo = mid+1;
        else if (key < vec[mid]) hi = mid-1;
        else return mid;
    }
    return lo;
}
```

## 平衡二叉查找树
+ 平均时间复杂度
+ 最坏时间复杂度
+ 空间复杂度
+ 适用场景

```cpp
class BST {
public:
    int size()
    {
        return (m_root ? m_root->N : 0);
    }

    int get(int key)
    {
        TreeNode* ptr = m_root;
        while (ptr)
        {
            if (ptr->key == key)
            {
                return ptr->val;
            }
            else if (key > ptr->key)
            {
                ptr = ptr->right;
            }
            else
            {
                ptr = ptr->left;
            }
        }
        return -1;
    }

    int minKey()
    {
        TreeNode* ptr = m_root;
        while (ptr && ptr->left)
        {
            ptr = ptr->left;
        }
        return ptr;
    }

    int maxKey()
    {
        TreeNode* ptr= m_root;
        while (ptr && prt->right)
        {
            ptr = ptr->right;
        }
        return ptr;
    }

    // 返回 小于等于key 的健
    int floor(int key)
    {
        
    }


private:
    typedef struct TreeNode {
        int key;
        int val;
        struct TreeNode* left;
        struct TreeNode* right;
        int N;
    } TreeNode;

    TreeNode* m_root;
};


```

## 广度优先搜索
+ 平均时间复杂度：
+ 最坏时间复杂度：
+ 空间复杂度：O(V)
+ 适用场景：求解最短路径的问题，而且要深度小，因为深度太大会占用一个很大的数组。
```cpp
unordered_set<Node> used;
queue<Node> q;
q.push(root);
used.insert(root);

int steps = 0;
while (!q.empty())
{
    ++steps;
    int len = q.size();
    for (int i = 0; i < size; ++i)
    {
        if (q.front() == target)
        {
            return steps;
        }
        // get child Node
        Node child = getChild();
        if (used.find(child) == used.end())
        {
            used.insert(child);
            q.push(child);
        }
        q.pop();
    }
}
```

## 深度优先搜索
+ 平均时间复杂度：
+ 最坏时间复杂度：
+ 空间复杂度：
+ 适用场景：用于求多个解，先找到的不一定是最优解，空间效率比广搜高。深度太大，效率也不高,需要高效剪枝。

```cpp
bool DFS(Node cur, Node target, unordered_set<Node>& visited)
{
    if (cur == target)
    {
        return true;
    }
    for (Node next : each child of cur)
    {
        if (next is not in visited)
        {
            add next to visted;
            return true if DFS(next, target, visited) == true;
        }
    }
    return false;
}

// Not Recursive
bool DFS(Node cur, Node target, unordered_set<Node>& visited)
{
    stack<Node> st;
    st.push(cur);
    visited.insert(cur);

    while (!st.empty())
    {
        Node tmp = st.front();
        if (tmp == target) return true;
        st.pop();

        for (Node next : each child of cur)
        {
            if (visited.find(next) == visited.end())
            {
                st.push(next);
                visited.insert(next);
            }
        }
    }
    return false;
}
```
