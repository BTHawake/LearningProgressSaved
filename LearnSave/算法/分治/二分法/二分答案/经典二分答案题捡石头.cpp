//https://www.luogu.com.cn/problem/P2678
//二分答案
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

signed main()
{
  IOS;
  int L, n, m;
  cin >> L >> n >> m;
  vector<int> a(n + 2, 0);
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  a[++n]=L;
  auto check = [&](int x)
  {
    int cnt = 0, last = 0;
    for (int i = 1; i <= n; i++)
    {
      if (a[i] - a[last] < x)
        cnt++; // 当前石头去掉
      else
        last = i; // 当前石头留下
    }
    return cnt <= m;
  };
  int l = 0, r =1e9+5;
  while (l + 1 < r)
  {
    int mid = l + r >> 1;
    if (check(mid))
      l = mid;
    else
      r = mid;
  }
  cout << l << endl;
  return 0;
}