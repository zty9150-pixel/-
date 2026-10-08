#include <bits/stdc++.h>
using namespace std;

char a[1000][1000];

void dfs(int x, int y, int n)
{
  if (n == 1)
  {
    a[x][y] = 'X';
    return;
  }
  int d = 1;
  for (int i = 1; i < n - 1; i++)
    d *= 3;
  dfs(x, y, n - 1);
  dfs(x, y + 2 * d, n - 1);
  dfs(x + 2 * d, y, n - 1);
  dfs(x + 2 * d, y + 2 * d, n - 1);
  dfs(x + d, y + d, n - 1);
}

int main()
{
  int n;

  while (cin >> n && n != -1)
  {
    int len = 1;
    for (int i = 1; i < n; i++)
      len *= 3;
    for (int i = 0; i < len; i++)
      for (int j = 0; j < len; j++)
        a[i][j] = ' ';
    dfs(0, 0, n);
    for (int i = 0; i < len; i++)
    {
      int last = len - 1;
      while (last >= 0 && a[i][last] == ' ')
        last--;
      for (int j = 0; j <= last; j++)
        cout << a[i][j];
      cout << '\n';
    }
    cout << "-\n";
  }

  return 0;
}