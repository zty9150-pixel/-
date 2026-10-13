#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, q, L[N], R[N], st1[N][21], st2[N][21];

/*
题目：ABC479 D Back and Forth Distance
有N个格子排成一行，编号1,2,…,N。
站在格子i时，可以执行下面其中一种移动：
1. 选整数j满足1 ≤ j < i，移动到格子j，本次移动代价为L_i。
2. 选整数j满足i < j ≤ N，移动到格子j，本次移动代价为R_i。
给出Q次查询，每次查询给定s和t。
求重复移动，从s到达t所需要的最小总代价。
约束：
2 ≤ N ≤ 3×10^5
1 ≤ Q ≤ 3×10^5
1 ≤ L_i ≤ 10^9 (2 ≤ i ≤ N)
1 ≤ R_i ≤ 10^9 (1 ≤ i ≤ N−1)
1 ≤ s,t ≤ N，s≠t
*/

int getMin1(int l, int r)
{
  int k = __lg(r - l + 1);
  return min(st1[l][k], st1[r - (1 << k) + 1][k]); // 从l朝右走2^j长度，从r朝左走2^j长度
}

int getMin2(int l, int r)
{
  int k = __lg(r - l + 1);
  return min(st2[l][k], st2[r - (1 << k) + 1][k]); // 从l朝右走2^j长度，从r朝左走2^j长度
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> q;
  for (int i = 2; i <= n; ++i)
    cin >> L[i];
  for (int i = 1; i <= n - 1; ++i)
    cin >> R[i];
  for (int i = 1; i <= n; ++i)
  {
    st1[i][0] = L[i];
    st2[i][0] = R[i];
  }
  for (int j = 1; j <= 20; ++j)
  {
    for (int i = 1; i <= n; ++i)
    {
      if (i + (1 << j) - 1 <= n)
      {
        st1[i][j] = min(st1[i][j - 1], st1[i + (1 << j - 1)][j - 1]);
        st2[i][j] = min(st2[i][j - 1], st2[i + (1 << j - 1)][j - 1]);
      }
    }
  }
  while (q--)
  {
    int s, t;
    cin >> s >> t;
    if (s == n || s == 1)
    {
      cout << (s < t ? R[s] : L[s]) << '\n';
      continue;
    }
    if (s < t)
    {
      cout << min(R[s], L[s] + getMin2(1, s - 1)) << '\n';
    }
    else
    {
      cout << min(L[s], R[s] + getMin1(s + 1, n)) << '\n';
    }
  }
  return 0;
}