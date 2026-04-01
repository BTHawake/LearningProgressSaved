// https://www.luogu.com.cn/problem/P3375 0-based 版本
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

int n, m;
string s1, s2;

void kmp(vector<int> &nxt)
{
  // 1. 求 nxt 数组 (模式串 s2 自己匹配自己)
  // nxt[0] 默认为 0，所以 i 从 1 开始
  for (int i = 1, j = 0; i < m; i++)
  {
    // 匹配失败时，回退到上一个成功匹配字符的 nxt 值
    while (j > 0 && s2[i] != s2[j])
      j = nxt[j - 1];

    // 匹配成功时，已匹配长度 j 增加
    if (s2[i] == s2[j])
      j++;

    nxt[i] = j;
  }

  // 2. 主串 s1 匹配模式串 s2
  // 主串从 0 开始遍历
  for (int i = 0, j = 0; i < n; i++)
  {
    // 匹配失败时的回退逻辑，与上方完全一致！
    while (j > 0 && s1[i] != s2[j])
      j = nxt[j - 1];

    if (s1[i] == s2[j])
      j++;

    // 找到了一个完整匹配
    if (j == m)
    {
      // 0-based 下，匹配的起始下标是 i - m + 1
      // 洛谷题目要求输出 1-based 的位置，所以再 + 1，即 i - m + 2
      cout << (i - m + 2) << "\n";

      // 匹配成功后，为寻找下一个可能的重叠匹配，继续让 j 回退
      j = nxt[j - 1];
    }
  }
}

signed main()
{
  IOS;
  cin >> s1 >> s2;
  n = s1.length();
  m = s2.length();

  // 告别了拼接字符串 ' ' + s1
  vector<int> nxt(m, 0); // 数组大小直接为 m 即可，默认初始化为 0

  kmp(nxt);

  // 洛谷要求输出 next 数组 (即 0-based 下的整个数组)
  for (int i = 0; i < m; i++)
  {
    cout << nxt[i] << " ";
  }
  cout << "\n";

  return 0;
}