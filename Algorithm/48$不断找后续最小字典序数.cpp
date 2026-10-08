
#include <bits/stdc++.h>
using namespace std;

/*
题目：给定长度n的排列（1~n互不相同）
最多执行 n-1 次操作，第 i 个操作：交换位置i和i+1
**每个操作最多只能使用一次**，操作顺序可自选
求能得到的字典序最小排列
q组独立测试用例
输入：
q
每组：n，然后n个数字的排列
限制：1<=q<=100，1<=n<=100
*/

void solve()
{
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a)
    cin >> x;
  int s = 0;
  while (s < n - 1)
  {
    int pos = s;
    for (int i = s + 1; i < n; ++i)
    {
      if (a[i] < a[pos])
        pos = i;
    }
    for (int i = pos; i > s; --i)
    {
      swap(a[i], a[i - 1]);
    }
    s = max(s + 1, pos);
  }

  for (int x : a)
    cout << x << ' ';
  cout << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  cin >> q;

  while (q--)
    solve();

  return 0;
}
