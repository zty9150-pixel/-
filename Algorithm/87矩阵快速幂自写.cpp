#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e4;

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

ll fib(ll n)
{
  if (n == 0)
    return 0;

  Matrix A;
  A.a[0][0] = 1;
  A.a[0][1] = 1;
  A.a[1][0] = 1;
  A.a[1][1] = 0;
  Matrix ans = qpow(A, n - 1);

  return ans.a[0][0];
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  while (cin >> n && n != -1)
  {
    cout << fib(n) << '\n';
  }

  return 0;
}
