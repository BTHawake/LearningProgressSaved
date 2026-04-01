//https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=9584
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define all(x) (x).begin(), (x).end()
signed main()
{
  IOS;
  int n, t;
  cin >> n >> t;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(all(a));
  int last = a[0];
  int cnt = 1;
  for (int i = 1; i < n; i++)
  {
    if (a[i] - last >= t)
    {
      cnt++;
      last = a[i];
    }
  }
  cout << cnt << "\n";

  return 0;
}