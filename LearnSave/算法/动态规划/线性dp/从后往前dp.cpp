// https://codeforces.com/contest/2078/problem/D
// 启发与性质
// 1从后往前dp
// 性质2，加法一定触发
// 性质3，每个小人都是独立的,所以每次dp单个小人

#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()

using ll = long long;
using pii = pair<int, int>;
using pil = pair<int, long long>;
const int INF = 0x3f3f3f3f;
const int N = 1000;

void solve()
{
  int n;
  cin >> n;
  vector<int> a(n + 1, 0);
  vector<vector<int>> multi(n + 1, vector<int>(2));
  // 1个人从i门后开始到结尾能涨到多少人
  vector<vector<int>> dp(n + 1, vector<int>(2));
  for (int i = 1; i <= n; i++)
  {
    char op;
    int x;
    for (int j = 0; j <= 1; j++)
    {
      cin >> op >> x;
      if (op == '+')
      {
        a[i] += x;
      }
      else
      {
        multi[i][j] = x - 1;
      }
    }
  }
  dp[n] = {1, 1};
  for (int i = n; i >= 1; i--)
  {
    for (int j = 0; j <= 1; j++)
    {
      dp[i - 1][j] = dp[i][j] + 1 * multi[i][j] * max(dp[i][0], dp[i][1]); // 每个人在i-1门后进入到第i门之后能生成的总人数
    }
  }
  ll ans = dp[0][1] + dp[0][0];
  for (int i = 1; i <= n; i++)
  {
    ans += a[i] * max(dp[i][0], dp[i][1]);
  }
  cout << ans << "\n";
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