//贡献法解题https://www.luogu.com.cn/problem/P2671#submit
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long
#define all(x) (x).begin(), (x).end()

const int N = 1000;
const int MOD = 10007;
int n, m, k;

signed main()
{
  IOS;
  cin >> n >> m;
  vector<int> num(n + 1);
  vector<int> color(n + 1);
  for (int i = 1; i <= n; i++)
  {
    cin >> num[i];
    num[i] %= MOD;
  }
  for (int i = 1; i <= n; i++)
  {
    cin >> color[i];
  }
  // 第一维度:颜色，第二维度:奇偶
  vector<vector<int>> cnt(m + 1, vector<int>(2, 0));
  vector<vector<int>> sum(m + 1, vector<int>(2, 0));

  for (int i = 1; i <= n; i++)
  {
    int c = color[i];
    int p = i % 2;
    cnt[c][p]++;
    sum[c][p] = (sum[c][p] + num[i]) % MOD;
  }
  int total = 0;
  // 贡献法求出单个编号的贡献
  for (int i = 1; i <= n; i++)
  {
    int c = color[i];
    int p = i % 2;
    int k = cnt[c][p];
    if (k < 2)
      continue;
    int part = ((k - 2) % MOD * num[i]) % MOD;
    int contribution = (i % MOD * (part + sum[c][p]) % MOD) % MOD;

    total = (total + contribution) % MOD;
  }
  cout << total << "\n";

  return 0;
}