#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long

const int INF = 1e18;

signed main()
{
  IOS;
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1, 0);
  vector<int> f(n + 1, 0);
  deque<int> q;
  int sum = 0;
  for (int i = 1; i <= n; i++)
  {
    cin >> a[i];
    sum += a[i];
  }
  q.push_back(0);
  // 1.维护合法区间  2.维护最优子结构（最小值递推）--->单调队列--->逆向思维
  for (int i = 1; i <= n; i++)
  {
    //现在是i-1的时候
    while (q.size() && i - 1 - q.front() > m)
      q.pop_front();
    // 2.维护最优子结构（最小值递推）
    f[i] = f[q.front()] + a[i];
    while (q.size() && f[q.back()] >= f[i])
      q.pop_back();
    q.push_back(i);
    //现在进入到i
  }
  int mi = INF;
  for (int i = n; i >= n - m; i--)
    mi = min(mi, f[i]);

  cout << sum - mi << '\n';

  return 0;
}