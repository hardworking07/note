# 二叉树
## 前序遍历
```cpp
void preOrder(Node* root)
{
    visit(root);
    preOrder(root->lchild);
    preOrder(root->right);
}

// Not Recursive
void preOrder(Node* root)
{
    // 访问栈顶元素，右子树入栈，左子树入栈
    stack<Node*> st;
    st.push(root);

    while (!st.empty())
    {
        Node* tmp = st.top();
        visit(tmp);
        st.pop();
        if (tmp->rchild) st.push(tmp->rchild);
        if (tmp->lchild) st.push(tmp->lchild);
    }
}
```

## 中序遍历
+ 从根节点开始，一直向左遍历入栈，直到左子树为空
+ 访问栈顶元素，栈顶元素出栈
+ 如果该元素存在右子树，针对右子树重复以上操作
+ 如果该元素不存在右子树，那么就可以访问其父节点了

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> st;
        TreeNode* p = root;
        while (p || !st.empty())
        {
            while (p)
            {
                st.push(p);
                p = p->left;
            }
            TreeNode* tmp = st.top();
            ans.push_back(tmp->val);
            st.pop();
            if (tmp->right)
            {
                p = tmp->right;
            }
        }
        return ans;
    }
};
```

## 后序遍历
1. 解法一
    后序遍历 = 根-右-左的先序遍历，然后逆序

2. 解法二
    后序遍历的关键：需要知道上一个访问的节点是左节点还是右节点，如果是左节点接下去就要访问右节点，如果是右节点，就访问当前节点

```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return vector<int> ();

        stack<TreeNode*> st;
        vector<int> ans;
        TreeNode* cur = root;
        TreeNode* pre = NULL;
        while (cur || !st.empty())
        {
            while (cur)
            {
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top();
            if (NULL == cur->right || cur->right == pre)
            {
                ans.push_back(cur->val);
                st.pop();
                pre = cur;
                cur = NULL;
            }
            else
            {
                cur = cur->right;
            }
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return vector<int> ();

        vector<int> ans;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty())
        {
            TreeNode* tmp = st.top();
            ans.push_back(tmp->val);
            st.pop();
            if (tmp->left) st.push(tmp->left);
            if (tmp->right) st.push(tmp->right);
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

## 层次遍历
```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return vector<vector<int>> ();

        vector<vector<int>> ans;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            int len = q.size();
            vector<int> vec(len, 0);
            for (int i = 0; i < len; ++i)
            {
                TreeNode* tmp = q.front();
                vec[i] = tmp->val;
                q.pop();
                if (tmp->left) q.push(tmp->left);
                if (tmp->right) q.push(tmp->right);
            }
            ans.push_back(vec);
        }
        return ans;
    }
};
```

## 根据中序和后序确定树
+ 对于一棵树来讲，后序遍历的最后一个节点就是根节点
+ 在前序遍历中，找到根节点，就可以得到左子树和右子树的前序遍历列表了，同时左子树和右子树的节点数也知道了
+ 再到后序遍历中，根据左右子树的节点数量，就可以得到左右子树的后序遍历列表
+ 如此，只要递归左右子树
```cpp
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty() || postorder.empty())
        {
            return NULL;
        }

        int rootVal = postorder.back();
        TreeNode* root = new TreeNode(rootVal);
        vector<int>::iterator vit = inorder.begin();
        while (vit != inorder.end() && *vit != rootVal)
        {
            ++vit;
        }
        vector<int> leftInorder(inorder.begin(), vit);
        vector<int> rightInorder(vit+1, inorder.end());
        vector<int> leftPost(postorder.begin(), postorder.begin() + leftInorder.size());
        vector<int> rightPost(postorder.begin()+leftInorder.size(), postorder.end()-1);
        root->left = buildTree(leftInorder, leftPost);
        root->right = buildTree(rightInorder, rightPost);

        return root;
    }
};
```

## 二叉树的公共最近祖先
1. 解法一
    + 如果一个节点的左节点有p，右节点有q, 肯定是最近公共祖先
    + 还有一种情况是，p或q本身就是最近公共祖先

2. 解法二
    + 深度遍历找到p和q，并记录遇到的每一个节点的祖先节点到一张hashmap
    + p向上遍历找出自己的所有祖先保存到hashset中
    + q向上遍历，如果祖先存在于hashset，结束，这就是最近的公共祖先

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        m_ans = NULL;
        recursiveAncestor(root, p, q);
        return m_ans;
    }

private:
    TreeNode* m_ans;


    bool recursiveAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!root)
        {
            return false;
        }
        int left = recursiveAncestor(root->left, p, q);
        int right = recursiveAncestor(root->right, p, q);
        int mid = ((root == p || root == q) ? 1 : 0);

        if (left + right + mid >= 2)
        {
            m_ans = root;
        }

        return (left + right + mid > 0);
    }
};
```
