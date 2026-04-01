// 后序中序求层序 https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=5385
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define int long long
#define pb push_back

int n;
vector<int> post;
vector<int> inorder;
unordered_map<int, int> mp;

struct Node
{
  Node *left;
  Node *right;
  int val;
  Node(int val) : val(val), left(nullptr), right(nullptr) {}
};

Node *build(int postl, int postr, int inl, int inr)
{
  if (postl > postr || inl > inr) // 在这里栽了好几次
  {
    return nullptr;
  }
  int rootval = post[postr];
  Node *root = new Node(rootval);
  int rootpos = mp[rootval];
  int leftsize = rootpos - inl;
  root->left = build(postl, postl + leftsize - 1, inl, rootpos - 1);
  root->right = build(postl + leftsize, postr - 1, rootpos + 1, inr);
  return root;
}

void bfs(Node *root)
{
  queue<Node *> q;
  q.push(root);
  vector<int> res;
  while (!q.empty())
  {
    Node *r = q.front();
    q.pop();
    res.pb(r->val);
    if (r->left != nullptr)
    {
      q.push(r->left);
    }
    if (r->right != nullptr)
    {
      q.push(r->right);
    }
    // delete r;
  }
  for (int i = 0; i < res.size(); i++)
  {
    if (i != 0)
    {
      cout << ' ';
    }
    cout << res[i];
  }
}

signed main()
{
  IOS;
  cin >> n;
  post.resize(n + 1);
  inorder.resize(n + 1);
  for (int i = 1; i <= n; i++)
  {
    cin >> post[i];
  }
  for (int i = 1; i <= n; i++)
  {
    cin >> inorder[i];
    mp[inorder[i]] = i;
  }
  Node *root = build(1, n, 1, n);
  // mp.clear();
  bfs(root);
  return 0;
}