// dp预处理加数学代数运算 枚举x2 求答案  https://codeforces.com/contest/2204/problem/E
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define int long long

const int N = 1000005;

int dp[N];  // 从i开始的数位之和
int nxt[N]; // 从i开始的数位和的下一个数,0为结束

vector cntall(N, vector<int>(10));

int sum_of_digits(int x)
{
  if (x < 10)
    return 0;
  int res = 0;
  while (x)
  {
    res += x % 10;
    x /= 10;
  }
  return res;
}

void init()
{
  // cout<<"初始化"<<endl;
  for (int i = 1; i < N; i++)
  {
    // 动态规划优化/打表---使用之前的结果优化计算
    nxt[i] = sum_of_digits(i);
    cntall[i] = cntall[nxt[i]];
    dp[i] = dp[nxt[i]];
    int num = i;

    while (num)
    {
      cntall[i][num % 10]++;
      dp[i] += num % 10;
      num /= 10;
    };
  }
  // cout<<"初始化完成"<<endl;
}

void solve()
{
  string s;
  cin >> s;
  if (s.size() == 1)
  {
    cout << s << '\n';
    return;
  }

  int sum = 0;
  int cnt[10]{}; // 实际数字的数量
  for (int i = 0; i < s.size(); i++)
  {
    sum += s[i] - '0';
    cnt[s[i] - '0']++;
  }
  for (int i = 1; i <= sum; i++)
  {
    if (i + dp[i] == sum)
    {
      const auto &cnti = cntall[i];
      // 比对一下当前i的cnt可不可行
      bool ok = true;
      for (int j = 0; j < 10; j++)
      {
        if (cnti[j] > cnt[j]) // 需要数字的数量
        {
          ok = false;
          break;
        }
      }
      if (!ok)
        continue;
      stringstream ss;
      // cout<<i<<endl;
      for (int j = 9; j >= 0; j--)
      {
        if (cnt[j] -= cnti[j])
        {
          for (int k = 0; k < cnt[j]; k++)
          {
            ss << j;
          }
        }
      }
      // cout<<"ok"<<endl;
      // return;
      string res = ss.str();
      cout << res;
      int num = i;
      while (num)
      {
        cout << num;
        num = nxt[num];
      }
      cout << '\n';
      return;
    }
  }
}

signed main()
{
  IOS;
  int T;
  init();
  // T = 1;
  cin >> T;
  while (T--)
  {
    solve();
  }

  return 0;
}