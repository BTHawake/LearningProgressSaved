// https://www.luogu.com.cn/article/o661kqqx 题解以及题目
// 枚举，贡献法，容斥原理，并查集

/*
比如字串a能给字串aa,ab,ac都能做出贡献,但是我们在枚举到aa,ab,ac的时候与a重复的贡献有aaa,aab,aac所以要用到容斥
二进制压缩与容斥结合
*/

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
const int MOD = 1e9 + 7;

int n, m;

int ctz(int n) {
    if (n == 0) return 32;
    
    // 查找表：0-15对应的末尾零个数
    static const int table[16] = {
        4, 0, 1, 0, 2, 0, 1, 0,
        3, 0, 1, 0, 2, 0, 1, 0
    };
    
    // 只查看最低4位
    unsigned int u = (unsigned int)n;
    int cnt = 0;
    
    // 每次检查4位
    while ((u & 0xF) == 0) {
        cnt += 4;
        u >>= 4;
    }
    cnt += table[u & 0xF];
    return cnt;
}

ll qp(ll x, ll p)
{
  ll ans = 1;
  while (p)
  {
    if (p % 2 == 1)
      ans =ans* x % MOD;
    p = p >> 1;
    x = (x * x) % MOD;
  }
  return ans;
}
ll ans = 0;
int f[N];
ll fa(int x)
{
  if (f[x] == x)
  {
    return x;
  }
  return f[x] = fa(f[x]);
}

void handle(int x)
{
  // 枚举一个子串在哪些位置出现（就是子串第一个字符的位置）
  ll all = 1 << (n - x + 1);
  ll b = (1 << x) - 1; // 全是1的掩码,用来只保留
  for (int i = 1; i < all; i++)
  {
    int c = 0;   // 表示最近x位的选择情况
    int tot = 0; // 可以自由选择的字符数（未覆盖的位 + 并查集连通块数）
    for (int j = 0; j < x; j++)
    {
      f[j] = j;
    }

    for (int j = 0; j < n; j++)
    {
      c = (c << 1) | ((i >> j) & 1);
      c &= b; // 因为b是x位的所以这样相当于只保留c的最后x位
      if (!c)
      {
        tot++;
      }
      else
      {
        ll t = c - (c & -c);           // lowbit()
        ll tmp = fa(ctz(c)); // 二进制末尾连续0的个数
        while (t)
        {
          f[fa(ctz(t))] = tmp;
          t -= t & -t;
        }
      }
    }
    for(int j=0;j<x;j++){
      tot+=(j==f[j]);
    }
    ll tmp = qp(m, tot);
    //查找1的个数的奇偶性
		if (__builtin_parity(i)) { //出现奇数次加，偶数次减，容斥
			ans = (ans + tmp) % MOD;
		} else {
			ans = (ans - tmp + MOD) % MOD;
		}
  }
}

signed main()
{
  IOS;

  cin >> n >> m;
  for (int i = 1; i <= n; i++)
  {
    handle(i);
  }
  cout << (ans * qp(qp(m, n), MOD - 2) % MOD) << endl; // 费马小定理

  return 0;
}