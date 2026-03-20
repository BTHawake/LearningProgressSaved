//每轮拓扑排序确定顺序 https://tzcoder.cn/acmhome/problemdetail.do?method=showdetail&id=1082
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pb push_back

const int INF = 0x3f3f3f3f;
const int N = 30;
int n, m;
vector<int> adj[N];
int degree[N];
void init()
{
  for (int i = 0; i < n; i++)
  {
    adj[i].clear();
  }
  memset(degree, 0, sizeof degree);
}

int topo_sort(string &res)
{
  int temp[N];
  for (int i = 0; i < n; i++)
  {
    temp[i] = degree[i];
  }

  queue<int> q;
  bool uncertain = false; // 当队列大小大于2时，当前排序不确定
  res = "";
  int cnt = 0; // 已经处理的节点数量，用来判断是否有环
  for (int i = 0; i < n; i++)
  {
    if (temp[i] == 0)
    {
      q.push(i);
    }
  }

  while (!q.empty())
  {
    if (q.size() >= 2)
    {
      uncertain = true; // 顺序不为一
    }

    int u = q.front();
    q.pop();
    res += char(u + 'A'); // 记录答案
    cnt++;

    for (int v : adj[u])
    {
      temp[v]--;
      if (temp[v] == 0)
      { // 如果成环，永远入不了队从而让cnt到达不了m=n
        q.push(v);
      }
    }
  }

  if (cnt != n)
  {
    return -1; // 有环
  }
  if (uncertain)
  {
    return 0; // 顺序不为一
  }
  return 1; // 顺序为一
}

signed main()
{
  IOS;

  while (cin >> n >> m)
  {
    if (n == 0 && m == 0)
    {
      return 0;
    }
    init();

    bool ok = false;   // 答案是什么
    bool done = false; // 是否已经出答案了
    int endi = 0;      // 结束时的i
    string ans_s;

    for (int i = 0; i < m; i++)
    {
      char u, c, v;
      cin >> u >> c >> v;
      // cout << u << ' ' << c << ' ' << v << '\n';
      if (ok || done)
      {
        continue;
      }

      adj[u - 'A'].pb(v - 'A');
      degree[v - 'A']++;

      ans_s = "";
      int res = topo_sort(ans_s);
      if (res == 1)
      {
        ok = true;
        done = true;
        endi = i + 1; // 1-base
      }
      else if (res == -1)
      {
        done = true;
        endi = i + 1;
      }
    }

    if (done)
    {
      if (ok)
      {
        cout << "Sorted sequence determined after " << endi << " relations: " << ans_s << ".\n";
      }
      else
      {
        cout << "Inconsistency found after " << endi << " relations." << "\n";
      }
    }
    else
    {
      cout << "Sorted sequence cannot be determined.\n";
    }
  }

  return 0;
}