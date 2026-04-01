//线性dp解区间调度问题 https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=5746
//这道题还有100种写法(夸张)，还可以枚举区间然后二分优化，还可以直接树状数组前缀最大值写
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pb push_back
#define eb emplace_back

const int N = 2005;

signed main()
{
  IOS;
  int n;
  cin >> n;
  vector<int> arr[N + 1];
  int mx = 0;
  for (int i = 0; i < n; i++)
  {
    int st, en;
    cin >> st >> en;
    arr[en].pb(st);
    mx = max(mx, en);
  }
  vector<int> dp(N + 1, 0);
  for (int i = 1; i <= mx; i++)
  {
    dp[i] = dp[i - 1];
    for (int j : arr[i])
    {
      dp[i] = max(dp[i], dp[j - 1] + i - j + 1);
    }
  }
  cout << dp[mx] << '\n';
  return 0;
}