//
// Created by awake on 2026/2/4.
//https://www.luogu.com.cn/problem/P3368
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define int long long
const int N = 5e5 + 5;

struct BIT
{
    int tree[N];
    int n;
    int lowbits(int x)
    {
        return x & -x;
    }

    void pushup(int x, int k)
    {
        while (x <= n)
        {
            tree[x] += k;
            x += lowbits(x);
        }
    }

    int query(int x)
    {
        int res = 0;
        while (x)
        {
            res += tree[x];
            x -= lowbits(x);
        }
        return res;
    }
};


signed main()
{
    IOS;
    int n, m;
    cin >> n >> m;
    BIT bit;
    bit.n = n;
    memset(bit.tree, 0, sizeof(bit.tree));

    int last = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        int diff = x - last;
        bit.pushup(i, diff);
        last = x;
    }

    while (m--) {
        int op, x, y, k;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> k;
            bit.pushup(x, k);
            bit.pushup(y + 1, -k);
        } else {
            cin >> x;
            cout << bit.query(x) << "\n";
        }
    }
    return 0;
}
