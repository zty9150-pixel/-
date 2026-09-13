#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;

int n, sum;
int a[13], c[13];
bitset<13> used;

bool dfs(int dep, int cur)
{
  if (dep == n)
  {
    return sum == cur;
  }
  for (int i = 0; i < n; ++i)
  {
    if (used[i + 1])
      continue;
    int next = cur + c[dep] * (i + 1);
    if (next > sum)
      return false;
    used[i + 1] = 1;
    a[dep] = i + 1;
    if (dfs(dep + 1, next))
      return true;
    used[i + 1] = 0;
  }
  return false;
}

void solution()
{
  cin >> n >> sum;
  int cur = 1;
  for (int i = 0; i < n; ++i)
  {
    c[i] = cur;
    cur = cur * (n - 1 - i) / (i + 1);
  }
  bool ok = dfs(0, 0);
  if (!ok)
    return;
  for (int i = 0; i < n; ++i)
    cout << a[i] << ' ';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
  return 0;
}