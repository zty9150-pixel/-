#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, a[N], st[N][21];
int getMax(int l, int r)
{
  int k = log(r - l + 1) / log(2);
  return max(st[l][k], st[r - (1 << k) + 1][k]); // 从l朝右走2^j长度，从r朝左走2^j长度
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
    st[i][0] = a[i];
  for (int j = 1; j <= 20; ++j)
  {
    for (int i = 1; i <= n; ++i)
    {
      if (i + (1 << j) - 1 <= n) // （1<<j）是区间长度，i+(1<<j)-1是区间右端下标
      {
        st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]); // st[i][j]，i是区间左端点，j是区间长度
      }
    }
  }
  cout << getMax(1, 3);
  return 0;
}