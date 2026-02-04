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
    std::cout << val <<" ";
  }
};
void solve()
{
  int n;
  vector<int>a(n);
  ranges::for_each(a, In());
}

signed main()
{
  IOS;
  int T;
  cin >> T;
  while (T--)
  {
    solve();
  }

  return 0;
}