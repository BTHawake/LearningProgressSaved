// 树形dp 没有上司的舞会https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=5829
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pb push_back
const int N = 6005;
int root;
int dp[N][2];
vector<int> g[N];
vector<int> H(N);
void dfs(int x)
{
  dp[x][0] = 0;
  dp[x][1] = H[x];
  for (auto y : g[x])
  {
    dfs(y);
    dp[x][1] += dp[y][0];                // 拿了子树只能不拿
    dp[x][0] += max(dp[y][0], dp[y][1]); // 不拿能拿子树最大情况
  }
}
signed main()
{
  IOS;
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
  {
    cin >> H[i];
  }
  vector<int> R(n + 1);
  for (int i = 1; i <= n - 1; i++)
  {
    int l, k;
    cin >> l >> k;
    g[k].pb(l);
    R[l]++;
  }
  int ab, ba;
  cin >> ab >> ba;
  for (int i = 1; i <= n; i++)
  {
    if (R[i] == 0)
    {
      root = i;
    }
  }
  dfs(root);
  cout << max(dp[root][0], dp[root][1]) << '\n';

  return 0;
}