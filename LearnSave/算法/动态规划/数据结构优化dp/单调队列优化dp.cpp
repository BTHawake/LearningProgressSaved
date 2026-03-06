//https://www.luogu.com.cn/problem/P2627
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define int long long

const int INF = 0x3f3f3f3f;


signed main()
{
  IOS;
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1, 0);
  vector<int> f(n + 1, 0);
  deque<int> q;
  for (int i = 1; i <= n; i++)
  {
    cin >> a[i];
  }
  q.push_back(0);
  // 1.维护合法区间(两个烽火台距离不超过m)  2.维护最优子结构（最小值递推）--->单调队列
  for (int i = 1; i <= n; i++)
  {
    while (q.size() && q.front() < i - m)
      q.pop_front();
    // 2.维护最优子结构（最小值递推）
    f[i] = f[q.front()] + a[i];
    while (q.size() && f[q.back()] >= f[i])
      q.pop_back();
    q.push_back(i);
  }
  int mx = INF;
  for (int i = n; i >= n - m + 1; i--)
    mx = min(mx, f[i]);
  cout << mx << '\n';
  return 0;
}