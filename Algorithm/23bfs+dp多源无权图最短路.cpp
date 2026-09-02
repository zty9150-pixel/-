#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e4 + 10;
const int inf = 1e9;

int h, w, k;
queue<pair<int, int>> q;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void solution()
{
  cin >> h >> w >> k;
  vector<string> s(h + 1);
  vector<int> row_vis(h + 1, 0), col_vis(w + 1, 0);
  vector<vector<int>> dist(h + 1, vector<int>(w + 1, -1));
  for (int i = 1; i <= h; ++i)
  {
    string str;
    cin >> str;
    s[i] = " " + str;
  }
  for (int i = 1; i <= h; ++i)
  {
    for (int j = 1; j <= w; ++j)
    {
      if (s[i][j] == '#')
      {
        row_vis[i] = 1;
        col_vis[j] = 1;
      }
    }
  }
  for (int i = 1; i <= h; ++i)
  {
    if (row_vis[i])
      continue;
    for (int j = 1; j <= w; ++j)
    {
      if (col_vis[j])
        continue;
      if (s[i][j] == '.')
      {
        dist[i][j] = 0;
        q.push({i, j});
      }
    }
  }
  while (q.size())
  {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();
    if (dist[x][y] == k)
      continue;
    for (int i = 0; i < 4; ++i)
    {
      int nx = dx[i] + x;
      int ny = dy[i] + y;
      if (nx <= h && nx >= 1 && ny <= w && ny >= 1 && dist[nx][ny] == -1 && s[nx][ny] == '.')
      {
        dist[nx][ny] = dist[x][y] + 1;
        q.push({nx, ny});
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= h; ++i)
  {
    for (int j = 1; j <= w; ++j)
    {
      if (dist[i][j] <= k && dist[i][j] != -1)
      {
        ans++;
      }
    }
  }
  cout << ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solution();
  return 0;
}