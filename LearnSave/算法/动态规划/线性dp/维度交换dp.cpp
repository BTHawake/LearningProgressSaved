// 维度反转dp，不用常规的目标值作为dp的值 https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=9048
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()

using ll = long long;
using pii = pair<int, int>;
using pil = pair<int, long long>;
const int INF = 0x3f3f3f3f;
const int N = 205;
// const int TIME = 86405;

struct node
{
  int l, r;
  int t;
};
// int dp[N][TIME];

void solve(int T)
{
  int n;
  cin >> n;
  vector<node> arr(n + 1);
  int ti = 0;
  for (int i = 1; i <= n; i++)
  {
    int l, r, t;
    cin >> l >> r >> t;
    arr[i] = {l, r, t};
    ti = max(ti, r);
    ti += t;
  }
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
  dp[0][0] = 0; // i为当前是第几个节点，j为当前已经拍了的照片数量

  for (int i = 1; i <= n; i++)
  {
    for (int j = 0; j <= i - 1; j++)
    {

      int cur = dp[i - 1][j];
      if (cur == INF)
        continue;
      int endtime = cur + arr[i].t;
      dp[i][j] = min(dp[i][j], endtime);

      if (endtime <= arr[i].r)
      {
        int leave = max(endtime, arr[i].l); // 拍完照的时间
        dp[i][j + 1] = min(dp[i][j + 1], leave);
      }
    }
  }

  int ans = 0;
  for (int j = n; j >= 0; j--)
  {
    if (dp[n][j] != INF)
    {
      ans = j;
      break;
    }
  }
  cout << "Data Set " << T << ":\n";
  cout << ans << "\n";
}
signed main()
{
  IOS;
  int T;
  // T=1;
  cin >> T;
  for (int i = 1; i <= T; i++)
  {
    solve(i);
    cout << "\n";
  }

  return 0;
}