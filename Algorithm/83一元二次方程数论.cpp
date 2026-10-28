/*
【一元二次方程与韦达定理】

一、一般形式
一元二次方程：
A*x*x + B*x + C = 0  (A != 0)

判别式：
delta = B*B - 4*A*C

求根公式：
x1 = (-B + sqrt(delta)) / (2*A)
x2 = (-B - sqrt(delta)) / (2*A)

实数解条件：
delta >= 0

二、韦达定理
对于 A*x*x + B*x + C = 0，设两个根为 x1、x2，则：

x1 + x2 = -B / A
x1 * x2 = C / A

特别地，当方程为：
x*x - S*x + P = 0

则：
x1 + x2 = S
x1 * x2 = P

因此，如果已知两个数的和为 S、积为 P，
可以构造方程：
x*x - S*x + P = 0

求出两个根，它们就是满足条件的两个数。

三、本题：a + b = d，a * b = d

已知：
a + b = d
a * b = d

因为 a、b 的和为 d、积也为 d，
所以构造方程：
x*x - d*x + d = 0

根据求根公式：
x1 = (d + sqrt(d*d - 4*d)) / 2
x2 = (d - sqrt(d*d - 4*d)) / 2

因此：
a = (d + sqrt(d*d - 4*d)) / 2
b = (d - sqrt(d*d - 4*d)) / 2

四、本题的有解条件

判别式：
delta = d*d - 4*d
      = d * (d - 4)

结合 d >= 0：
d == 0 或 d >= 4 时有非负实数解。
d == 1、2、3 时无解。

五、核心记忆

已知两个数的和与积：
和 = S，积 = P

构造方程：
x*x - S*x + P = 0

两个根就是这两个数。

韦达定理：
根之和 = -一次项系数 / 二次项系数
根之积 = 常数项 / 二次项系数
*/
#include <bits/stdc++.h>
using namespace std;

void solve()
{
  int d;
  cin >> d;

  if (d > 0 && d < 4)
  {
    cout << "N\n";
    return;
  }

  long double delta = sqrtl(1.0L * d * d - 4.0L * d);
  long double a = (d + delta) / 2.0L;
  long double b = (d - delta) / 2.0L;

  cout << "Y " << fixed << setprecision(10)
       << a << " " << b << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--)
    solve();

  return 0;
}