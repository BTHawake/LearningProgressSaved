//容斥原理https://codeforces.com/contest/2204/problem/C
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
// #define int long long
using i64 = int64_t;
void solve()
{
  i64 a,b,c,m;
  cin >> a >> b >> c >> m;
  //lcm
  i64 ab=a*b/__gcd(a,b);
  i64 bc=b*c/__gcd(b,c);
  i64 ac=a*c/__gcd(a,c);
  i64 abc=c*ab/__gcd(c,ab);
  //ans
  i64 A=6*(m/a)-3*(m/ab)-3*(m/ac)+2*(m/abc);
  i64 B=6*(m/b)-3*(m/bc)-3*(m/ab)+2*(m/abc);
  i64 C=6*(m/c)-3*(m/bc)-3*(m/ac)+2*(m/abc);
  
  cout << A << " " << B << " " << C << '\n';

}

signed main()
{
  IOS;
  int T;
  // T=1;
  cin >> T;
  while (T--)
  {
    solve();
  }

  return 0;
}