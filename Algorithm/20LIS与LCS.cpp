#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e5 + 10;

int n, m;
int dp[N], a[N], b[N];
int dp2[N][N];

void solution1() // 朴素LIS最长上升子序列************************
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
  {
    dp[i] = a[i];
    for (int j = 1; j < i; ++i)
    {
      if (a[j] < a[i])
        dp[i] = max(dp[j] + 1, dp[i]);
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i)
  {
    ans = max(ans, dp[i]);
  }
  cout << ans;
}

void solution2() // 二分LIS**************************************
{
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  vector<int> tails;
  for (int x : a)
  {
    auto it = lower_bound(tails.begin(), tails.end(), x);
    if (it == tails.end())
    {
      tails.push_back(x);
    }
    else
    {
      *it = x;
    }
  }
  cout << tails.size();
}

void solution3() // 双指针LCS最长公共子序列**********************
{
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
  {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i)
  {
    cin >> b[i];
  }
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      if (a[i] == a[j])
        dp2[i][j] = dp2[i - 1][j - 1] + 1;
      else
      {
        dp2[i][j] = max(dp2[i - 1][j], dp2[i][j - 1]);
      }
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution1();
  return 0;
}