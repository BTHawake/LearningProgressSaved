//
// Created by awake on 2026/2/4.
//https://www.luogu.com.cn/problem/P3374
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define int long long
const int N = 5e5 + 5;

int tree[N];
int n, m;
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

signed main()
{
    IOS;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        pushup(i, x);
    }
    while (m--)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
        {
            pushup(x, y);
        }
        else
        {
            cout << query(y) - query(x - 1) << "\n";
        }
    }

    return 0;
}