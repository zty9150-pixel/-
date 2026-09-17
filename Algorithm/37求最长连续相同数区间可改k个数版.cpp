#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int n, k;
char a[N];

// 高中生瓦夏收到一份生日礼物：一个长度为 $n$ 的字符串。该字符串仅由字母`a`和`b`组成。瓦夏将字符串的美观度定义为：由相同字符构成的子串（连续子序列）的最大长度。
// 瓦夏最多可以修改原字符串中的 $k$ 个字符。求他能得到的字符串的最大美观度。
// 输入的第一行包含两个整数 $n$ 和 $k$（$1 ≤ n ≤ 100000$，$0 ≤ k ≤ n$）——字符串的长度以及最多可修改的字符数量。
// 第二行给出该字符串，仅由字母`a`和`b`组成。
int solve(char target)
{
  int l = 1;
  int cnt = 0;
  int ans = 0;
  for (int r = 1; r <= n; ++r)
  {
    if (a[r] != target)
      cnt++;
    while (cnt > k)
    {
      if (a[l] != target)
        cnt--;
      l++;
    }
    ans = max(ans, r - l + 1);
  }
  return ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;

  for (int i = 1; i <= n; ++i)
    cin >> a[i];

  cout << max(solve('a'), solve('b'));

  return 0;
}