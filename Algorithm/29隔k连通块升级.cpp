#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
const int mod = 998244353;

// 赫莫斯有一个包含 $n$ 个整数的数组。他希望萨梅兹将数组按非递减顺序排序。但这道题对萨梅兹来说太过简单，因此赫莫斯规定萨梅兹只能使用下述操作：
// • 选取下标 i 和 j，满足 1 <= i,j <= n，且 |i-j| >= x，随后交换 a_i 与 a_j。

// 请你判断萨梅兹能否通过有限次（可以为 0 次）上述操作，将数组排成非递减顺序。

int n, x;

void solution()
{
  cin >> n >> x;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  if (2 * x <= n)
  {
    cout << "YES" << '\n';
    return;
  }
  vector<int> b(n + 1);
  b = a;
  sort(b.begin() + 1, b.end());
  for (int i = n - x + 1; i <= x; ++i)
  {
    if (a[i] != b[i])
    {
      cout << "NO" << '\n';
      return;
    }
  }
  cout << "YES" << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
  {
    solution();
  }

  return 0;
}