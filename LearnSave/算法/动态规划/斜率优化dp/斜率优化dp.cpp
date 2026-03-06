//斜率优化dp https://acm.hdu.edu.cn/showproblem.php?pid=3507
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long
using ll = long long;

void solve()
{
  int n;
  ll m;
  while (cin >> n >> m)
  {
    vector<int> dp(n + 1, 0);
    vector<int> S(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
      cin >> S[i];
      S[i] += S[i - 1];
    }
    deque<int> q;

    auto getY = [&](int j)
    { return dp[j] + S[j] * S[j]; };

    auto getX = [&](int j)
    { return S[j]; };

    auto checkFront = [&](int j, int k, ll Si)
    {
      // 是否满足
      return (getY(j) - getY(k)) <= 2 * Si * (getX(j) - getX(k));
    };

    auto checkBack = [&](int i, int j, int k)
    {
      // 是否为先陡后缓
      return (getY(i) - getY(j)) * (getX(j) - getX(k)) <= (getY(j) - getY(k)) * (getX(i) - getX(j));
    };

    q.push_back(0);
    for (int i = 1; i <= n; i++)
    {
      // 步骤一：以i为裁判淘汰队头过时的点
      while (q.size() >= 2 && checkFront(q[1], q[0], S[i]))
        q.pop_front();
      // 步骤二：获取当前最优断点并计算 dp[i]
      int best_j = q.front();
      dp[i] = dp[best_j] + (S[i] - S[best_j]) * (S[i] - S[best_j]) + m;
      // 步骤三：维护队尾下凸包的形态（剔除废物点）----根据数学的方法得出要维持下凸包状态(取三个点ABC)
      // q.back() 是队尾点，q[q.size() - 2] 是倒数第二个点
      while (q.size() >= 2 && checkBack(i, q.back(), q[q.size() - 2]))
        q.pop_back();
      q.push_back(i);
    }
    cout << dp[n] << '\n';
  }
}

signed main()
{
  IOS;
  solve();
  return 0;
}