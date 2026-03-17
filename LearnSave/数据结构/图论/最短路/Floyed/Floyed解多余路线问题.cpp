//Floyed算法  https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=8046

#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define eb emplace_back
const int INF = 0x3f3f3f3f;
const int N = 105;
int dp[N][N];
vector<tuple<int, int, int>> ed;
signed main()
{
  IOS;
  int n, m;
  cin >> n >> m;
  memset(dp, INF, sizeof dp);
  for (int i = 0; i <= n; i++)
    dp[i][i] = 0;

  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    dp[u][v] = min(dp[u][v], w);
    dp[v][u] = min(dp[v][u], w);
    ed.eb(u, v, w);
  }
  for (int k = 1; k <= n; k++)
  {
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (dp[i][k] < INF && dp[k][j] < INF)
          dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
      }
    }
  }
  vector<tuple<int, int, int>> ans;

  for (auto [u, v, w] : ed)
  {

    bool ned = false;
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (dp[i][j] == dp[i][u] + w + dp[v][j] || dp[i][j] == dp[i][v] + w + dp[u][j])
        {
          ned = true;
          break;
        }
      }
      if (ned)
        break;
    }
    if (!ned)
      ans.eb(u, v, w);
  }
  if (ans.empty())
  {
    cout << "None\n";
    return 0;
  }

  for (auto [u, v, w] : ans)
  {
    cout << u << " " << v << " " << w << '\n';
  }
  return 0;
}