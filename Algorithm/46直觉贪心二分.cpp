#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
using ll = long long;

int n, w;
int a[N];

// 给定 $n$ 个矩形，每个矩形高度为 $1$。每个矩形的宽度都是 $2$ 的幂（即可以表示为 $2^x$，其中 $x$ 为非负整数）。
//  同时给你一个二维盒子，宽度为 $W$。注意 $W$ 不一定是 $2$ 的幂。并且 $W$ 大于等于所有矩形里最大的宽度。
//  你需要求出这个盒子的最小高度，使得盒子能够放下所有给定矩形。所有矩形放入盒子后，盒子内允许留有空白区域。
//  你不能旋转矩形来放入盒子。任意两个不同矩形不能重叠，也就是任意两个不同矩形的相交面积必须为0。
//  第一行输入一个整数 t ——测试用例的数量。每组测试用例包含两行。
//  对于每组测试用例：
//  - 第一行包含两个整数 n（1e5）和 W（1e9）；
//  - 第二行包含 n 个整数 w_1,w_2,w_n（1e6），其中 w_i 代表第 i 个矩形的宽度。每个 w_i 都是 2 的幂；
//  n之和不超过1e5。
//  输出 $t$ 个整数。第 $i$ 个整数代表第 $i$ 组测试用例的答案，也就是盒子所需的最小高度。

void solve()
{
  cin >> n >> w;
  vector<int> ret;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  sort(a + 1, a + 1 + n);
  for (int i = n; i >= 1; --i)
  {
    auto it = lower_bound(ret.begin(), ret.end(), a[i]);
    if (it == ret.end())
      ret.push_back(w - a[i]);
    else
      *it -= a[i];
  }
  cout << ret.size() << '\n';
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