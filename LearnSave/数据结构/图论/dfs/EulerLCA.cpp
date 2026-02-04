/// 欧拉序结合RMQ求LCA模板，复杂度 O(logN)预处理+O(1)查询
/// 题目链接: https://www.luogu.com.cn/problem/P3379

#include <bits/stdc++.h>

using namespace std;

constexpr int N = 5e5 + 5; // 节点数量
constexpr int logN = __lg(N * 2) + 1;

vector<int> T[N]; // Tree邻接表

struct Node
{
    int dep, u;
    bool operator<(const Node &b) const noexcept { return dep < b.dep; }
} eul[N * 2], st[N * 2][logN]; // eul: 欧拉序列，st: st表
int fst[N], tim; // fst[i]: 第一次到访节点i时间，tim: 时间戳

void dfs(const int u, const int f, const int d)
{
    eul[tim] = {d, u};
    fst[u] = tim++;
    for (const auto &v : T[u])
        if (v != f)
        {
            dfs(v, u, d + 1);
            eul[tim++] = {d, u};
        }
}

int pow2(const int j) { return 1 << j; }

void build()
{
    for (int i = 0; i < tim; ++i)
        st[i][0] = eul[i];

    for (int j = 1; j < logN; ++j)
        for (int i = 0; i + pow2(j) - 1 < tim; ++i)
            st[i][j] = min(st[i][j - 1], st[i + pow2(j - 1)][j - 1]);
}

int lca(const int u, const int v)
{
    const auto &[l, r] = minmax(fst[u], fst[v]);
    const int k = __lg(r - l + 1);
    return min(st[l][k], st[r - pow2(k) + 1][k]).u;
}

int main()
{
    ios;
    int n, m, s; // 节点数量，询问次数，根节点编号
    cin >> n >> m >> s;
    for (int i = 1, u, v; i < n; ++i)
        cin >> u >> v, T[u].push_back(v), T[v].push_back(u);

    dfs(s, 0, 0);
    build();

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
}