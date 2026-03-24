// dfs序加树状数组 https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=2723
//  树状数组是维护一维线性数组的数据结构，dfs序把树形结构转换为线性结构从而能让树状数组维护树
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pb push_back

const int N = 100005;

int n, m;
vector<int> adj[N];
int in_time[N];
int out_time[N];
int timer = 0;
bool has_app[N];

void dfs(int u, int fa)
{
  in_time[u] = ++timer;
  for (int v : adj[u])
  {
    if (v != fa)
    {
      dfs(v, u);
    }
  }
  out_time[u] = timer;
}

int lowbit(int x)
{
  return x & -x;
}
int bit[N];

void add(int idx, int val)
{
  while (idx <= n)
  {
    bit[idx] += val;
    idx += lowbit(idx);
  }
}

int query(int idx)
{
  int sum = 0;
  while (idx > 0)
  {
    sum += bit[idx];
    idx -= lowbit(idx);
  }
  return sum;
}

signed main()
{
  IOS;
  cin >> n;
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; i++)
  {
    add(i, 1);
    has_app[i] = true;
  }
  cin >> m;
  for (int i = 0; i < m; i++)
  {
    char c;
    int x;
    cin >> c >> x;
    if (c == 'Q')
    {
      int y = query(out_time[x]) - query(in_time[x] - 1);
      cout << y << endl;
    }
    else
    {
      if (has_app[x])
      {
        add(in_time[x], -1);
        has_app[x] = false;
      }
      else
      {
        add(in_time[x], 1);
        has_app[x] = true;
      }
    }
  }
  return 0;
}