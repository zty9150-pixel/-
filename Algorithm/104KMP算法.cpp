
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

char s[N], p[N];
int nex[N];

void solve()
{
  cin >> (s + 1) >> (p + 1);

  int n = strlen(s + 1);
  int m = strlen(p + 1);

  // 1. 求 nex 数组
  nex[0] = nex[1] = 0;

  for (int i = 2, j = 0; i <= m; ++i)
  {
    // 失配：利用 nex 回退
    while (j && p[i] != p[j + 1])
      j = nex[j];

    // 匹配成功：长度 +1
    if (p[i] == p[j + 1])
      j++;

    nex[i] = j;
  }

  // 2. 利用 nex 数组进行匹配
  int ans = 0;

  for (int i = 1, j = 0; i <= n; ++i)
  {
    // 失配：利用 nex 回退
    while (j && s[i] != p[j + 1])
      j = nex[j];

    // 匹配成功：长度 +1
    if (s[i] == p[j + 1])
      j++;

    // 完整匹配成功
    if (j == m)
    {
      ans++; // 匹配次数
      // i - m + 1 为匹配起始位置

      j = nex[j]; // 回退，继续寻找
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
