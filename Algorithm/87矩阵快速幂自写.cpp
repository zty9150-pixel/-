#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e9 + 7;

struct Matrix
{
  ll a[2][2] = {};
};

Matrix mul(Matrix A, Matrix B)
{
  Matrix ans;
  ans.a[0][0] = (A.a[0][0] * B.a[0][0] + A.a[0][1] * B.a[1][0]) % mod;
  ans.a[0][1] = (A.a[0][0] * B.a[0][1] + A.a[0][1] * B.a[1][1]) % mod;
  ans.a[1][0] = (A.a[1][0] * B.a[0][0] + A.a[1][1] * B.a[1][0]) % mod;
  ans.a[1][1] = (A.a[1][0] * B.a[0][1] + A.a[1][1] * B.a[1][1]) % mod;

  return ans;
}

Matrix qpow(Matrix a, ll b)
{
  Matrix ans;
  ans.a[0][0] = 1;
  ans.a[1][1] = 1;
  while (b)
  {
    if (b & 1)
      ans = mul(a, ans);
    a = mul(a, a);
    b >>= 1;
  }
  return ans;
}

void fib()
{
  ll n, m;
  cin >> n >> m;
  Matrix A;
  A.a[0][0] = 1;
  A.a[0][1] = 1;
  A.a[1][0] = 1;
  A.a[1][1] = 0;

  Matrix ans = qpow(A, n - 1);
  if (n == m)
  {
    cout << ans.a[0][0] << '\n';
    return;
  }
  Matrix ans2 = qpow(ans, 1);
  if (n + 1 == m)
  {
    cout << (ans.a[0][0] + ans2.a[0][0]) % mod << '\n';
  }

  ll fib_m2 = (qpow(A, m).a[0][0] * ans.a[0][0]) % mod + (qpow(A, m + 1).a[0][0] * ans2.a[0][0]) % mod;

  cout << fib_m2 - ans2.a[0][0];
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
  {
    fib();
  }

  return 0;
}
