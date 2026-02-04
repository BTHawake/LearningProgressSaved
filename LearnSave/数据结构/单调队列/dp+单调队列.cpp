//https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=9547


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
const int N = 1000;
const int MOD = 998244353;
struct In
{
  void operator()(auto &val) const noexcept
  {
    std::cin >> val;
  }
};

struct Out
{
  void operator()(auto &val) const noexcept
  {
    std::cout << val << " ";
  }
};

signed main()
{
  IOS;
  int n;
  cin>>n;
  vector<int> a(n);
    
  ranges::for_each(a, In());

  deque<pair<vector<int>::iterator, int>> dq;

  dq.push_back({a.begin(), 1});

  for (int i = 1; i < n; i++)
  {
    int cur = 0;

    for (auto it : dq)
    {
      cur = (cur + it.second) % MOD;
    }
    while (!dq.empty() && *(dq.back().first) < a[i])
    {
      dq.pop_back();
    }
    dq.push_back({a.begin() + i, cur});
    // cout << cur << endl;
  }
  int ans = 0;
  for (auto it : dq)
  {
    ans = (ans + it.second) % MOD;
  }

  cout << ans << endl;

  return 0;
}