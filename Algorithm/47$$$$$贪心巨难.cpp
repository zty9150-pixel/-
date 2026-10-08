#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 莫诺卡普家附近有一家卖手办的商店。一套新的手办即将发售；这套手办一共有 n 个，第 i 个手办售价 i 枚硬币，可在第 i 天至第 n 天购买。

// 对于这 n 天中的每一天，莫诺卡普都清楚自己能否去商店。

// 每次莫诺卡普到商店时，可以购买任意数量店内在售的手办（当然，不能购买还未到发售时间的手办）。如果莫诺卡普在同一天购买至少两个手办，他可以享受折扣：减免所购买最贵手办的费用（也就是说，当天买的最贵那个手办免费）。

// 莫诺卡普想要买下这套手办里恰好1个第1款、1个第2款……1个第 n 款手办。同一个手办不能买两次。请问他最少需要花费多少硬币？

// 输入
// 第一行包含一个整数 t（1 <= t <= 10^4）——测试用例的数量。
// 每个测试用例包含两行：
// - 第一行包含一个整数 n（1 <= n <= 4*10^5）——这套手办的数量（同时也是总天数）；
// - 第二行是字符串 s（|s|=n，s_i 的取值为 0 或 1）。若莫诺卡普可以在第 i 天去商店，则 s_i 为 1；否则为 0。

// 输入额外约束：
// - 每个测试用例中，s_n=1，因此莫诺卡普一定可以在第 n 天买齐所有手办；
// - 所有测试用例的 n 之和不超过 4*10^5。

// 输出
// 对每个测试用例，输出一个整数——莫诺卡普需要花费的最少硬币数。

bool check(const string &s, int k)
{
  int n = s.size();
  vector<int> used(n, 0);
  for (int i = n - 1; i >= 0; --i)
  {
    if (k > 0 && s[i] == '1')
    {
      used[i] = 1;
      --k;
    }
  }
  int cur = 0;

  for (int i = 0; i < n; ++i)
  {
    if (used[i])
    {
      --cur;
      if (cur < 0)
        return false;
    }
    else
    {
      ++cur;
    }
  }

  return true;
}

void solve()
{
  int n;
  cin >> n;

  string s;
  cin >> s;
  if (n == 1)
  {
    cout << 1 << '\n';
    return;
  }
  int cnt1 = 0;
  for (char c : s)
  {
    if (c == '1')
      ++cnt1;
  }
  int l = 1;
  int r = cnt1 + 1;
  while (r - l > 1)
  {
    int mid = (l + r) / 2;

    if (check(s, mid))
      l = mid;
    else
      r = mid;
  }
  ll ans = 0;
  for (int i = n - 1; i >= 0; --i)
  {
    if (s[i] == '1' && l > 0)
    {
      --l;
    }
    else
    {
      ans += i + 1;
    }
  }

  cout << ans << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--)
  {
    solve();
  }

  return 0;
}
