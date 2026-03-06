// https://www.luogu.com.cn/problem/P2015 树形dp
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

const int N = 105;
const int INF = 1e9;

int dp[N][N];
vector<pair<int, int>> g[N];
int n, Q;

void dfs(int u, int fa)
{
  for (int i = 0; i <= Q; i++)
    dp[u][i] = -INF;
  dp[u][0] = 0;
  for (auto &[v, w] : g[u])
  {
    if (v == fa)
      continue;
    dfs(v, u);

    int tmp[N];
    for (int i = 0; i <= Q; i++)
    {
      tmp[i] = dp[u][i];
    }

    for (int i = 0; i <= Q; i++)
    {
      if (dp[u][i] < 0)
        continue;
      for (int j = 0; j <= Q; j++)
      {
        if (dp[v][j] < 0)
          continue;
        if (i + j + 1 > Q)
          continue;
        tmp[i + j + 1] = max(tmp[i + j + 1], dp[u][i] + dp[v][j] + w);
      }
    }

    for (int i = 0; i <= Q; i++)
    {
      dp[u][i] = tmp[i];
    }
  }
}

int main()
{
  IOS;
  cin >> n >> Q;
  for (int i = 0; i < n - 1; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  dfs(1, 0);
  cout << dp[1][Q] << '\n';

  return 0;
}