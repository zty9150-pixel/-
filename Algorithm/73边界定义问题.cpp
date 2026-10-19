// # AtCoder ABC480 D — Concatenation of Prefixes

// ## 核心模型
// B 由 A 的每个前缀依次拼接而成，第 i 块为 A[1...i]。

// ## 三个辅助数组
// - pre1[i]：A[1...i] 的和，用于计算单块内部区间和。
// - pre2[i]：前 i 个完整块的总和，用于计算多个完整块的和。
// - pre3[i]：前 i 块的总长度，用于定位 B 中的位置属于哪一块。

// ## 查询区间 [L,R] 的处理流程
// 1. blockL：L 所在的区块编号。
// 2. blockR：R 所在的区块编号。
// 3. lpos、rpos：L、R 在各自区块内部的位置。
// 4. 若 blockL == blockR，直接用 pre1 求区间和。
// 5. 若 blockL < blockR，将区间拆为左侧残块、中间完整块、右侧残块。

// ## 本题复盘重点
// 不要一开始就推公式。先固定变量含义，再画区间、拆分区间，最后分别套用前缀和。

// ## 易错点
// - 混淆区块编号与区块内部位置。
// - 忘记左右端点可能处于同一块。
// - 混淆 B 中的位置与 A 中的下标。
// - 查询位置和区块总长度可能超过 int 范围。

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve()
{
  int n, q;
  cin >> n >> q;

  vector<ll> a(n + 1), pre1(n + 1), pre2(n + 1), pre3(n + 1);

  for (int i = 1; i <= n; ++i)
  {
    cin >> a[i];
    pre1[i] = pre1[i - 1] + a[i];
    pre2[i] = pre2[i - 1] + pre1[i];
    pre3[i] = pre3[i - 1] + i;
  }

  while (q--)
  {
    ll l, r;
    cin >> l >> r;

    int i = lower_bound(pre3.begin() + 1, pre3.end(), l) - pre3.begin();
    int j = lower_bound(pre3.begin() + 1, pre3.end(), r) - pre3.begin();

    ll lp = l - pre3[i - 1];
    ll rp = r - pre3[j - 1];

    ll ans = 0;

    if (i == j)
    {
      ans = pre1[rp] - pre1[lp - 1];
    }
    else
    {
      ans = pre1[i] - pre1[lp - 1];
      ans += pre2[j - 1] - pre2[i];
      ans += pre1[rp];
    }

    cout << ans << '\n';
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();

  return 0;
}
