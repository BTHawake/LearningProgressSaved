// https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=9560
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long
#define all(x) (x).begin(), (x).end()
signed main()
{
  IOS;
  int T;
  cin >> T;
  while (T--)
  {
    int n, x;

    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
      cin >> a[i];
    }
    sort(all(a));
    int l = 0, r = n - 1;
    int sum = 0;
    vector<int> ans;
    int cur = 0;
    while (l <= r)
    {
      int interval = x - (cur % x);
      if (a[r] >= interval)
      {
        cur = (cur + a[r]) % x;
        sum += a[r];
        ans.push_back(a[r]);
        r--;
      }
      else
      {
        cur += a[l];
        ans.push_back(a[l]);
        l++;
      }
    }
    cout << sum << "\n";
    for (int i = 0; i < ans.size(); i++)
    {
      if (i != 0)
      {
        cout << ' ';
      }
      cout << ans[i];
    }
    cout << "\n";
  }

  return 0;
}