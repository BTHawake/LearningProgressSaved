// https://codeforces.com/gym/649308/problem/C2
#include <bits/stdc++.h>
using namespace std;
#define int long long

using ll = long long;
const int N = 200010;
const int inf = 2e9 + 10;

vector<int> primes;
bool is_prime[N];
vector<int> fac[N];

void precompute()
{
  for (int i = 0; i < N; i++)
  {
    is_prime[i] = true;
  }
  is_prime[0] = is_prime[1] = false;

  for (int i = 2; i < N; i++)
  {
    if (is_prime[i])
    {
      primes.push_back(i);
      fac[i].push_back(i);
    }

    for (int p : primes)
    {
      if (i * p >= N)
        break;
      is_prime[i * p] = false;

      for (int f : fac[i])
      {
        fac[i * p].push_back(f);
      }

      if (i % p != 0)
      {
        fac[i * p].push_back(p);
      }

      if (i % p == 0)
        break;
    }
  }
}

void solve()
{
  int n;
  cin >> n;
  vector<int> a(n + 1), b(n + 1);
  bool has_factor[N] = {false};
  ll ans = 0;
  int even = 0;
  int odd[2] = {0, 0};
  b[0] = inf;

  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
  {
    cin >> b[i];
    has_factor[i] = false;
    if (a[i] % 2 == 1)
    {
      if (b[odd[1]] > b[i])
      {
        odd[1] = i;
      }
      if (b[odd[0]] > b[odd[1]])
      {
        swap(odd[0], odd[1]);
      }
    }
    else
    {
      even = i;
    }
  }

  for (int i = 1; i <= n; i++)
  {
    for (int f : fac[a[i]])
    {
      if (has_factor[f])
      {
        cout << "0\n";
        return;
      }
      has_factor[f] = true;
    }
  }
  // 至少一个偶数
  if (even != 0) // 一个
  {
    ll MAX = b[odd[0]];
    for (const auto &re : fac[a[even]])
    {
      has_factor[re] = false;
    }
    int cnt = N;
    for (int i = 1; i < N; i++)
    {
      if (has_factor[i])
        cnt = min(cnt, i - a[even] % i);
    }
    ans = min(MAX, b[even] * cnt);
  }
  else
  {
    ll MAX = b[odd[0]] + b[odd[1]];
    for (int i = 1; i <= n; i++)
    {
      for (const auto &re : fac[a[i] + 1])
      {
        if (has_factor[re])
        {
          MAX = min(MAX, b[i]);
        }
      }
    }
    for (const auto &re : fac[a[odd[0]]])
    {
      has_factor[re] = false;
    }
    int cnt = N;

    for (int i = 1; i < N; i++)
    {
      if (has_factor[i])
      {
        cnt = min(cnt, i - a[odd[0]] % i);
      }
    }
    ans = min(MAX, b[odd[0]] * cnt);
  }
  cout << ans << endl;
}

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  precompute();
  int t;
  cin >> t;
  while (t--)
  {
    solve();
  }
  return 0;
}