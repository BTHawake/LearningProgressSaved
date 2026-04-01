// https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=9560
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long
#define all(x) (x).begin(), (x).end()
struct node
{
  int id;
  int sum;
  bool operator>(const node &a) const
  {
    return sum > a.sum;
  }
};

signed main()
{
  IOS;
  int n, m;
  cin >> n >> m;
  vector<int> p(n + 1, 0);
  vector<int> adj[n + 1];
  vector<int> sum(n + 1, 0);
  for (int i = 1; i <= n; i++)
  {
    cin >> p[i];
  }
  for (int i = 1; i <= m; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    sum[u] += p[v];
    sum[v] += p[u];
  }
  priority_queue<node, vector<node>, greater<node>> que;
  for (int i = 1; i <= n; i++)
  {
    que.push({i, sum[i]});
  }
  vector<int> vis(n + 1, 0);
  int mx = 0;
  while (que.size())
  {
    auto [idx, val] = que.top();
    que.pop();
    if (vis[idx])
    {
      continue;
    }
    vis[idx] = 1;
    mx = max(mx, val);
    for (int i : adj[idx])
    {
      if (!vis[i])
      {
        sum[i] -= p[idx];
        que.push({i, sum[i]}); // 小的节点会比之前老的节点先出现，所以与没更新之前的数据不冲突
      }
    }
  }
  cout << mx << "\n";
  return 0;
}