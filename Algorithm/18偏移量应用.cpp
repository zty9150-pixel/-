#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e7 + 10;

int n, k;
priority_queue<int> qq;

void solution()
{
  cin >> n >> k;
  qq.push(k);
  int delta = 0;
  for (int i = 1; i <= n; ++i)
  {
    int m;
    cin >> m;
    if (m == 1)
    {
      int x;
      cin >> x;
      qq.push(x - delta);
    }
    else if (m == 2)
    {
      int x;
      cin >> x;
      delta += x;
    }
    else if (m == 3)
    {
      int x;
      cin >> x;
      delta -= x;
    }
    else
    {
      cout << delta + qq.top() << '\n';
      qq.pop();
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
  return 0;
}