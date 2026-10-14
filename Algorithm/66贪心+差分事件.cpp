#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;
ll n, m;

/*
数组a[1..m]初始全0。给定n个互不相同线段[l_i,r_i]。任选线段子集：
选中的线段，对区间内每个位置a_j +=1；不选无操作。
记max(a)为数组最大值，min(a)为数组最小值。
子集代价 = max(a) - min(a)。
求所有子集能得到的最大代价。

多组测试用例。
n:线段数，m:数组长度。
*/

void solve()
{
  cin >> n >> m;

  map<ll, int> d1, d2; // 差分事件

  for (int i = 1; i <= n; ++i)
  {
    ll l, r;
    cin >> l >> r;

    if (l > 1) // 要么min_i = 1,要么 = m ，可通过贪心得到，所以要找到除了这两点外的最大值
    {
      d1[l]++;
      d1[r + 1]--;
    }

    if (r < m)
    {
      d2[l]++;
      d2[r + 1]--;
    }
  }

  auto calc = [](const map<ll, int> &d)
  {
    int cnt = 0;
    int res = 0;

    for (auto [x, v] : d)
    {
      cnt += v;
      res = max(res, cnt);
    }

    return res;
  };

  cout << max(calc(d1), calc(d2)) << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
  {
    solve();
  }

  return 0;
}
