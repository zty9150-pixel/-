
#include <iostream>
#include <cstring>
using namespace std;
int dx[] = {0, -1, 0, 1, 0};
int dy[] = {0, 0, 1, 0, -1};
int a[6][6];
int flip[6][6];
int res[6][6];

int get_color(int x, int y)
{
  int c = a[x][y];
  for (int i = 0; i < 5; ++i)
  {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 1 && nx <= 5 && ny >= 1 && ny <= 5)
    {
      c += flip[nx][ny];
    }
  }
  return c % 2;
}
int cal()
{
  for (int i = 2; i <= 5; ++i)
  {
    for (int j = 1; j <= 5; ++j)
    {
      if (get_color(i - 1, j) == 0)
      {
        flip[i][j] = 1;
      }
    }
  }
  for (int i = 1; i <= 5; ++i)
  {
    if (get_color(5, i) == 0)
    {
      return -1;
    }
  }
  int sum = 0;
  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 5; ++j)
    {
      sum += flip[i][j];
    }
  }
  if (sum > 6)
    return -1;
  else
    return sum;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  while (n--)
  {
    for (int i = 1; i <= 5; i++)
    {
      string s;
      cin >> s;
      for (int j = 1; j <= 5; j++)
      {
        a[i][j] = s[j - 1] - '0';
      }
    }
    int min_cnt = -1;
    for (int state = 0; state <= 31; ++state)
    {
      memset(flip, 0, sizeof(flip));
      for (int i = 1; i <= 5; ++i)
      {
        flip[1][i] = (state >> (5 - i)) & 1;
      }
      int cnt = cal();
      if (cnt != -1 && (min_cnt == -1 || cnt < min_cnt))
      {
        min_cnt = cnt;
        memcpy(res, flip, sizeof(flip));
      }
    }
    if (min_cnt == -1)
    {
      cout << -1 << '\n';
    }
    else
    {
      cout << min_cnt << '\n';
    }
  }
  return 0;
}