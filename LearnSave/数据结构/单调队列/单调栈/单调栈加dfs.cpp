// https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=9549
// 单调栈加dfs
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 5e5 + 50;

vector<int> tr[N];
int a[N], ans[N], stk[N];

void dfs(int u, int fa, int len)
{
  auto cmp = [&](int idx1, int idx2)
  { return a[idx1] < a[idx2]; };
  int *pos_ptr = lower_bound(stk, stk + len, u, cmp);
  int pos = pos_ptr - stk;

  ans[u] = ans[stk[pos - 1]] + 1;
  int tmp = stk[pos];
  stk[pos] = u;

  for (int v : tr[u])
  {
    if (v != fa)
    {
      dfs(v, u, pos + 1);
    }
  }

  stk[pos] = tmp;
}

signed main()
{
  IOS;
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i < n; ++i)
  {
    int u, v;
    cin >> u >> v;
    tr[u].push_back(v);
    tr[v].push_back(u);
  }
  a[0] = 0;
  ans[0] = -1;
  stk[0] = 0;
  dfs(1, 0, 1);

  for (int i = 1; i <= n; ++i)
  {
    cout << ans[i] << " ";
  }
  return 0;
}