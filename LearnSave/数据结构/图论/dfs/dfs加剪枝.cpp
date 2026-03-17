// dfs加剪枝 https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=5809
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
const int N = 1005;
int n, w;
int cat[N];
int sum[N];
int ans = INF;
void dfs(int a, int b)
{
  if (b >= ans)
  {
    return;
  }
  if (a == n)
  {
    ans = min(ans, b);
    return;
  }
  for (int i = 0; i < b; i++)
  {
    if (sum[i] + cat[a] <= w)
    {
      sum[i] += cat[a];
      dfs(a + 1, b);
      sum[i] -= cat[a];
    }
  }
  sum[b] = cat[a];
  dfs(a + 1, b + 1);
  sum[b] = 0;
}
signed main()
{
  IOS;
  cin >> n >> w;
  for (int i = 0; i < n; i++)
  {
    cin >> cat[i];
  }
  dfs(0, 0);
  cout << ans << '\n';
  return 0;
}