#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
题目：
给定数轴上 n 条线段；每条线段端点坐标都是整数。线段可以退化成点、相交、嵌套、重合。
对每一个 k ∈ [1..n]，求：整数点 x 的数量，满足覆盖 x 的线段恰好等于 k 条。
线段 [li, ri] 覆盖整数点 x 当且仅当 li ≤ x ≤ ri。

输入：
第一行一个整数 n (1 ≤ n ≤ 2e5)，线段数量。
接下来 n 行，每行两个整数 li, ri (0 ≤ li ≤ ri ≤ 1e18)，代表第 i 条线段端点。

输出：
输出 n 个空格分隔整数 cnt_1, cnt_2,…,cnt_n，cnt_i 表示恰好被 i 条线段覆盖的整数点个数。

输入：
3
0 3
1 3
3 8
输出：
6 2 1

*/

const int N = 2e5 + 10;
int n;
ll ans[N];
map<ll, ll> d;

void solve()
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
  {
    ll l, r;
    cin >> l >> r;
    d[l]++;
    d[r + 1]--;
  }
  ll cnt = 0;
  for (auto it = d.begin(); it != d.end(); ++it)
  {
    cnt += it->second;
    ll x = it->first;
    auto nxt = next(it);
    if (nxt == d.end())
      break;
    ll y = nxt->first;
    if (cnt > 0)
    {
      ans[cnt] += y - x;
    }
  }
  for (int i = 1; i <= n; ++i)
  {
    cout << ans[i] << ' ';
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // int t;
  // cin >> t;
  // while (t--)
  {
    solve();
  }

  return 0;
}
