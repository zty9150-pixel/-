#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
using ll = long long;

int n;
ll k;
ll a[N];

/*
题目翻译：
给定一个整数数组 a_1,a_2,…,a_n 和整数 k。

每一步操作，你可以选择下面其中一种：
1. 选一个下标 i，将 a_i 减 1（a_i = a_i - 1）；
2. 选两个下标 i 和 j，令 a_i = a_j（把 a_i 的值复制成 a_j 的值）。

求：使得数组总和 ∑a_i ≤ k 的最少操作步数。数组元素可以变成负数。

输入：
第一行一个整数 t (1 ≤ t ≤ 10^4) —— 测试用例数量。
每组测试用例：
第一行两个整数 n, k (1 ≤ n ≤ 2⋅10^5；1 ≤ k ≤ 10^15) —— 数组长度 n，总和上限 k。
第二行 n 个整数 a_1 … a_n (1 ≤ a_i ≤ 10^9) —— 数组。

保证所有测试用例的 n 总和不超过 2⋅10^5。

输出：
对每组测试用例，输出最少操作步数。

样例输入：
4
1 10
20
2 69
6 9
7 8
1 2 1 3 1 2 1
10 1
1 2 3 1 2 6 1 6 8 10

样例输出：
10
0
2
7

样例解释：
第1组：把 a_1 减10次，总和≤10。
第2组：数组原本总和就≤69，无需操作。
第3组：
操作1：令 a4 = a3 = 1；
操作2：a4 减1，变成0。
最终数组 [1,2,1,0,1,2,1]，总和≤8，一共2步。
第4组：
操作1：把 a7 连续减3次，得到 a7=-2；
操作2：把 a6,a8,a9,a10 这4个元素复制成 a7=-2；
最终数组 [1,2,3,1,2,-2,-2,-2,-2,-2]，总和≤1，一共3+4=7步。
*/

void solve()
{
  cin >> n >> k;

  ll sum = 0;

  for (int i = 1; i <= n; ++i)
  {
    cin >> a[i];
    sum += a[i];
  }

  if (sum <= k)
  {
    cout << 0 << '\n';
    return;
  }

  sort(a + 1, a + n + 1, greater<ll>());

  ll ans = sum - k; // i = 0 时，只减最小值

  ll prefix = 0;

  // i = 1 ~ n-1
  // 表示把最大的 i 个数复制成最小值
  for (int i = 1; i <= n - 1; ++i)
  {
    prefix += a[i];

    // 复制 i 个最大值之后的总和
    ll cur = sum - prefix + 1LL * i * a[n];

    // 还需要降低多少
    ll need = cur - k;

    // 最小值 + i 个复制出来的元素
    // 一共 i+1 个元素会随着最小值下降
    ll d = 0;

    if (need > 0)
    {
      d = (need + i) / (i + 1);
    }

    ans = min(ans, d + i);
  }

  cout << ans << '\n';
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