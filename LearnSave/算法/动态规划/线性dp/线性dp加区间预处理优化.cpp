// 线性dp加区间预处理优化https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=5942
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long
using ll = long long;
const int INF = 0x3f3f3f3f;
const int N = 1005;
int cost[N][N]; // l到r的最小代价
int pos[N];
int pre[N];
int dp[N][N]; // 前 i 个村庄建 k 所小学的最小代价
signed main()
{
  IOS;
  int m, n;
  cin >> m >> n;
  for (int i = 2; i <= m; i++)
  {
    cin >> pos[i];
    pos[i] = pos[i] + pos[i - 1];
  }
  for (int i = 1; i <= m; i++)
  {
    pre[i] = pre[i - 1] + pos[i];
  }
  for (int l = 1; l <= m; l++)
  {
    for (int r = l; r <= m; r++)
    {
      int mid = (l + r) / 2;
      int left = pos[mid] * (mid - l) - (pre[mid - 1] - pre[l - 1]);
      int right = (pre[r] - pre[mid]) - pos[mid] * (r - mid);
      cost[l][r] = left + right;
    }
  }
  memset(dp, INF, sizeof dp);
  for (int i = 1; i <= m; i++)
  {
    dp[i][1] = cost[1][i];
  }
  for (int k = 2; k <= n; ++k) // 建 k 所小学
  {
    for (int i = k; i <= m; ++i) // 前 i 个村庄
    {
      for (int j = k - 1; j < i; ++j) // 定义最后一所小学放在 j 到 i 之间 来 实现状态转移
      {
        if (dp[j][k - 1] != INF)
        {
          ll val = dp[j][k - 1] + cost[j + 1][i];
          dp[i][k] = min(dp[i][k], val);
        }
      }
    }
  }
  cout << dp[m][n] << '\n';

  return 0;
}