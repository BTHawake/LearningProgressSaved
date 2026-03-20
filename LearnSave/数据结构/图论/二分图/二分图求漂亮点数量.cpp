// 二分图求漂亮点数量 https://codeforces.com/contest/2204/problem/D
// 这道题难在要理解题目并联想到二分图
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pb push_back
void solve()
{
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  // 染色数组 -1未访问 0,1两个边
  vector<int> color(n + 1, -1);
  int mxans = 0;

  for (int i = 1; i <= n; i++)
  {
    if (color[i] != -1)
      continue;
    queue<int> q;
    q.push(i);
    color[i] = 0;

    int cnt[2] = {1, 0};  // 当前联通块的顶点数量
    bool is_valid = true; // 当前连通块是否为二分图

    while (!q.empty())
    {
      int cur = q.front();
      q.pop();

      for (auto v : adj[cur])
      {
        if (color[v] == -1)
        {
          color[v] = 1 - color[cur]; // 染上不同的颜色（归为不同类）
          cnt[color[v]]++;
          q.push(v);
        }
        else if (color[v] == color[cur])
        {
          is_valid = false;
        }
      }
    }
    if (is_valid)
    {
      mxans += max(cnt[0], cnt[1]);
    }
  }
  cout << mxans << '\n';
}

signed main()
{
  IOS;
  int T;
  // T=1;
  cin >> T;
  while (T--)
  {
    solve();
  }

  return 0;
}