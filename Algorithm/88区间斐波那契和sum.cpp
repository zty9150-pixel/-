/*
题目：H - Fibonacci Sum

一、题目描述

斐波那契数列定义：

    F(0) = 0
    F(1) = 1
    F(n) = F(n-1) + F(n-2)  (n >= 2)

给定两个非负整数 N、M，求：

    S = F(N) + F(N+1) + ... + F(M)

答案对 1e9+7 取模。

数据范围：
    0 <= N <= M <= 1e9


二、区间斐波那契和公式

由斐波那契递推式：

    F(i) = F(i+2) - F(i+1)

因此：

    S = F(N) + F(N+1) + ... + F(M)

      = [F(N+2) - F(N+1)]
      + [F(N+3) - F(N+2)]
      + ...
      + [F(M+2) - F(M+1)]

中间项相互抵消，得到：

    S = F(M+2) - F(N+1)

最终公式：

    ans = (F(M+2) - F(N+1) + mod) % mod


三、矩阵快速幂求斐波那契数

转移矩阵：

    A = [1 1]
        [1 0]

矩阵幂与斐波那契数的关系：

    A^n = [F(n+1)  F(n)  ]
          [F(n)    F(n-1)]

因此，当 n >= 1 时：

    F(n) = (A^(n-1))[0][0]

也可以使用：

    F(n) = (A^n)[0][1]

注意：
    F(0) = 0，需要单独处理。

最终区间求和：

    ans = (fib(M+2) - fib(N+1) + mod) % mod

时间复杂度：
    O(log M)
*/

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
  Matrix ans_2 = qpow(ans, 1);
  if (n + 1 == m)
  {
    cout << (ans.a[0][0] + ans_2.a[0][0]) % mod << '\n';
  }

  ll fib_m2 = (qpow(A, m).a[0][0] * ans.a[0][0]) % mod + (qpow(A, m + 1).a[0][0] * ans_2.a[0][0]) % mod;

  cout << fib_m2 - ans_2.a[0][0];
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
