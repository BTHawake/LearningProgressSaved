// 树状数组维护前缀最大值 https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=5746
// 这题还可以直接线性dp
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define all(x) (x).begin(), (x).end()
using pii = pair<int, int>;
const int N = 2005;
int n;
int tree[N * 2];
int mx = 0;
int lowbit(int x)
{
  return x & (-x);
}

int query(int x)
{
  int res = 0;
  while (x)
  {
    res = max(res, tree[x]);
    x -= lowbit(x);
  }
  return res;
}

void update(int x, int v)
{
  while (x <= mx)
  {
    tree[x] = max(tree[x], v);
    x += lowbit(x);
  }
}

signed main()
{
  IOS;

  cin >> n;
  vector<pii> arr(n);

  for (int i = 0; i < n; i++)
  {
    int st, en;
    cin >> st >> en;
    // st++; en++; // 规范起来，虽然这道题不需要
    arr[i] = {st, en};
    mx = max(mx, en);
  }
  sort(all(arr), [](pii a, pii b)
       { return a.second < b.second; });
  for (int i = 0; i < n; i++)
  {
    int lenmx = query(arr[i].first - 1);
    int len = lenmx + arr[i].second - arr[i].first + 1;
    update(arr[i].second, len);
  }
  cout << query(mx) << '\n';

  return 0;
}