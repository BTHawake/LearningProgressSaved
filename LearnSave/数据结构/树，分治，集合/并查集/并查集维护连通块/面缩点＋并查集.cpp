// https://codeforces.com/problemset/problem/2205/F
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

/*
1. 因为所有点度数均为偶数必定形成闭合回路，即可将网格按面划分，把每个 $1 \times 1$ 的小方框“降维”成一个点。
2. 每个方框的独立价值设为其四条边的代数和（左正右负，上正下负），相邻方框同时选中时内部边权会自动正负抵消，完美契合奇偶交替加减规则。
3. 遍历题目限制，若某条边不能建，说明其两侧方框必须“同生共死”，用并查集将它们合并，价值相加；若碰触网格最外层边界，则强制与特殊的“0号外界集合”合并连坐。
4. 最后遍历所有连通块的根节点，若属于0号集合或总价值 $\le 0$ 则直接丢弃，剩下总价值 $> 0$ 的连通块全部累加，即为最终答案。
*/

// 并查集查找函数 (带路径压缩)
int find_root(int x, vector<int> &parent)
{
  if (parent[x] == x)
    return x;
  return parent[x] = find_root(parent[x], parent);
}

// 并查集合并函数
// 强制让 0 (外界) 成为根节点，这样方便最后判断连通块是否与外界相连
void merge_nodes(int a, int b, vector<int> &parent, vector<long long> &val)
{
  int rootA = find_root(a, parent);
  int rootB = find_root(b, parent);
  if (rootA != rootB)
  {
    if (rootA == 0)
    {
      parent[rootB] = 0;
      val[0] += val[rootB];
    }
    else if (rootB == 0)
    {
      parent[rootA] = 0;
      val[0] += val[rootA];
    }
    else
    {
      parent[rootA] = rootB;
      val[rootB] += val[rootA];
    }
  }
}

void solve()
{
  int n, m;
  cin >> n >> m;

  // V[i][j]: 垂直边 (对应你原本的 mp1)，长 n-1 行, 宽 m 列
  vector<vector<int>> V(n - 1, vector<int>(m));
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cin >> V[i][j];
    }
  }

  // U[i][j]: 水平边 (对应你原本的 mp2)，长 n 行, 宽 m-1 列
  vector<vector<int>> U(n, vector<int>(m - 1));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m - 1; j++)
    {
      cin >> U[i][j];
    }
  }

  // 读取限制条件（按字符串读取最安全，防止连续的 0101 被当成一个整数）
  // limit_V 对应垂直边 V 的限制 (n-1 行, 每行 m 个字符)
  vector<string> limit_V(n - 1);
  for (int i = 0; i < n - 1; i++)
    cin >> limit_V[i];

  // limit_U 对应水平边 U 的限制 (n 行, 每行 m-1 个字符)
  vector<string> limit_U(n);
  for (int i = 0; i < n; i++)
    cin >> limit_U[i];

  // --- 核心逻辑开始 ---

  // 内部方框的总数
  int box_count = (n - 1) * (m - 1);

  // 初始化并查集，0 号代表外界，1 到 box_count 代表内部方框
  vector<int> parent(box_count + 1);
  vector<long long> val(box_count + 1, 0);
  for (int i = 0; i <= box_count; i++)
  {
    parent[i] = i;
  }

  // 步骤 1：计算每个方框的“独立价值”
  // 二维坐标 (i, j) 映射到一维 ID: i * (m - 1) + j + 1
  auto get_id = [&](int r, int c)
  {
    if (r < 0 || r >= n - 1 || c < 0 || c >= m - 1)
      return 0; // 越界就是外界
    return r * (m - 1) + c + 1;
  };

  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < m - 1; j++)
    {
      int id = get_id(i, j);
      long long w = 0;
      w += U[i][j];     // 跨入上边：加权值
      w -= U[i + 1][j]; // 跨出下边：减权值
      w += V[i][j];     // 跨入左边：加权值
      w -= V[i][j + 1]; // 跨出右边：减权值
      val[id] = w;
    }
  }

  // 步骤 2：处理限制条件，把“不能建栅栏”的方框绑在一起

  // 检查水平边 U 的限制：如果 U[i][j] 不能建，说明它上下的方框必须绑在一起
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m - 1; j++)
    {
      if (limit_U[i][j] == '0')
      {
        int box_up = get_id(i - 1, j);
        int box_down = get_id(i, j);
        merge_nodes(box_up, box_down, parent, val);
      }
    }
  }

  // 检查垂直边 V 的限制：如果 V[i][j] 不能建，说明它左右的方框必须绑在一起
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (limit_V[i][j] == '0')
      {
        int box_left = get_id(i, j - 1);
        int box_right = get_id(i, j);
        merge_nodes(box_left, box_right, parent, val);
      }
    }
  }

  // 步骤 3：贪心统计答案
  long long ans = 0;
  for (int i = 1; i <= box_count; i++)
  {
    // 如果这个节点是它所在连通块的根节点
    if (parent[i] == i)
    {
      // 只要它没有和外界(0)绑在一起，且它的总价值为正，我们就果断“选中”这批方框
      if (val[i] > 0)
      {
        ans += val[i];
      }
    }
  }

  cout << ans << '\n';
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