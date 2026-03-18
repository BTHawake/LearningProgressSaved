// 最小生成树Kruskal算法 https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=5181
// 这道题因为有负边权，所以不能使用prim算法，但是可以用Kruskal算法通过负边权特判来解
// 这道题本质是求有虚拟点的和没有虚拟点的最小值
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()

using ll = long long;
const ll INF = LLONG_MAX;

struct node
{
  int u, v, w;
  bool operator<(const node &a) const
  {
    return w < a.w;
  }
};

int fa(int x, vector<int> &parent)
{
  if (parent[x] != x)
  {
    parent[x] = fa(parent[x], parent);
  }
  return parent[x];
}

bool unite(int x, int y, vector<int> &parent)
{
  int xx = fa(x, parent);
  int yy = fa(y, parent);
  if (xx == yy)
  {
    return false;
  }
  parent[xx] = yy;
  return true;
}

ll kruskal(int N, vector<node> &edge)
{
  sort(all(edge));
  vector<int> parent(N);
  for (int i = 0; i < N; i++)
  {
    parent[i] = i;
  }

  ll sum = 0;
  int cnt = 0;
  for (const auto &e : edge)
  {
    auto &[u, v, w] = e;
    if (w < 0)
    {
      sum += w;
      bool tmp = unite(u, v, parent);
    }
    else
    {
      if (unite(u, v, parent))
      {
        sum += w;
        cnt++;
      }
      if (cnt == N - 1)
      {
        break;
      }
    }
  }
  int root = fa(0, parent);
  for (int i = 1; i < N; ++i)
  {
    if (fa(i, parent) != root)
      return INF;
  }
  return sum;
}

signed main()
{
  IOS;
  int n, m;
  cin >> n >> m;
  vector<node> edge(m);
  for (int i = 0; i < m; ++i)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    edge[i] = {a, b, c};
  }
  vector<int> dock(n);
  bool has_dock = false;
  for (int i = 0; i < n; ++i)
  {
    cin >> dock[i];
    if (dock[i] != -1)
    {
      has_dock = true;
    }
  }

  // 只用道路
  ll ans1 = kruskal(n, edge);
  // 加上码头
  ll ans2 = INF;

  if (has_dock)
  {
    vector<node> edge2 = edge;
    for (int i = 0; i < n; i++)
    {
      if (dock[i] != -1)
      {
        edge2.pb({i, n, dock[i]});
      }
    }
    ans2 = kruskal(n + 1, edge2);
  }
  ll ans = min(ans1, ans2);
  cout << ans << '\n';

  return 0;
}