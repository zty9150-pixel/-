/*
题目：
    有 n 棵树，位置为 x[i]，高度为 h[i]，位置严格递增。
    每棵树可以选择：
    1. 向左倒，占据 [x[i]-h[i], x[i]]
    2. 向右倒，占据 [x[i], x[i]+h[i]]
    3. 不砍，占据位置 x[i]

    倒下的树不能覆盖其他树所在的位置。
    求最多能砍倒多少棵树。

思路：贪心

    从左往右遍历，维护 last，表示前面已经处理的树
    所占据区域的最右端。

    对于当前树，按照以下优先级决策：

    1. 优先向左倒：
       如果 x[i]-h[i] > last，
       说明左倒不会影响前面的树。
       答案 +1，更新 last = x[i]。

    2. 如果不能向左倒，尝试向右倒：
       如果 i 是最后一棵树，或者
       x[i]+h[i] < x[i+1]，
       说明右倒不会影响后面的树。
       答案 +1，更新 last = x[i]+h[i]。

    3. 如果左右都不能倒：
       保留当前树，更新 last = x[i]。

贪心正确性：

    向左倒和向右倒的收益都是 1。
    但向左倒后最右端为 x[i]，
    向右倒后最右端为 x[i]+h[i]。

    因此，能向左倒时优先向左倒，
    可以给后面的树留下更多空间，不会使最优答案变差。

    如果不能左倒，再判断右倒；
    如果也不能右倒，就只能保留当前树。

复杂度：
    时间 O(n)，每棵树只遍历一次。
    空间 O(n)，用于保存树的位置和高度。
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve()
{
  int n;
  cin >> n;

  vector<ll> x(n), h(n);

  for (int i = 0; i < n; ++i)
    cin >> x[i] >> h[i];

  ll last = LLONG_MIN;
  int ans = 0;

  for (int i = 0; i < n; ++i)
  {
    if (x[i] - h[i] > last)
    {
      ans++;
      last = x[i];
    }
    else if (i == n - 1 || x[i] + h[i] < x[i + 1])
    {
      ans++;
      last = x[i] + h[i];
    }
    else
    {
      last = x[i];
    }
  }

  cout << ans << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
  return 0;
}