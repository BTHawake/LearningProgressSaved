// https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=3018 dijkstra解法 求所有路的比例即(1-C)的最大值
// 这道题还可以用floyd算法解决
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define int long long
#define eb emplace_back
// const int EPS = 1e-12;
int n, m;
void solve()
{
  vector<int> w(n + 1);
  vector<pair<int, double>> adj[n + 1];
  vector<double> d(n + 1);
  for (int i = 1; i <= n - 1; i++)
  {
    cin >> w[i];
    // d[i] = EPS;
  }
  for (int i = 1; i <= m; i++)
  {
    int u, v;
    double w;
    cin >> u >> v >> w;
    adj[u].eb(v, 1.0 - w);
    adj[v].eb(u, 1.0 - w);
  }
  d[n] = 1.0;
  priority_queue<pair<double, int>> pq;
  pq.emplace(1.0, n);
  vector<bool> vis(n + 1, false);
  while (!pq.empty())
  {
    auto [cur, u] = pq.top();
    pq.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (auto [v, fac] : adj[u])
    {
      if (vis[v])
        continue;
      if (cur * fac > d[v])
      {
        d[v] = cur * fac;
        pq.emplace(d[v], v);
      }
    }
  }
  double ans = 0.0;
  for (int i = 1; i <= n - 1; i++)
  {
    ans += w[i] * d[i];
  }
  cout << fixed << setprecision(2) << ans << "\n";
}

signed main()
{
  IOS;
  while (cin >> n >> m)
  {
    solve();
  }
  return 0;
}