
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;

/*
题目：网格多米诺查询
h行w列网格，.是空，#是障碍
多米诺占相邻两格（横向左右 / 纵向上下），两格都必须是空
q次询问，每次给矩形[r1,c1]~[r2,c2]，求这个矩形内能放多米诺的方案总数
限制：h,w≤500，q≤1e5
思路：
预处理两个二维前缀和
s_h[i][j]：以(i,j)为左侧格子的横向多米诺（(i,j)和(i,j+1)都为.）
s_v[i][j]：以(i,j)为上方格子的纵向多米诺（(i,j)和(i+1,j)都为.）
查询：
横向：统计在查询矩形内，左端点(i,j)满足 r1≤i≤r2 , c1≤j≤c2-1
纵向：统计在查询矩形内，上端点(i,j)满足 r1≤i≤r2-1 , c1≤j≤c2
用二维前缀和O(1)回答每次询问
*/

void solve()
{
  cin >> n >> m;

  vector<string> a(n + 1);

  for (int i = 1; i <= n; ++i)
  {
    string s;
    cin >> s;
    a[i] = " " + s;
  }
  vector<vector<int>> h(n + 1, vector<int>(m + 1, 0));
  vector<vector<int>> v(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      int H = (j < m && a[i][j] == '.' && a[i][j + 1] == '.');
      int V = (i < n && a[i][j] == '.' && a[i + 1][j] == '.');
      h[i][j] = H + h[i - 1][j] + h[i][j - 1] - h[i - 1][j - 1];
      v[i][j] = V + v[i - 1][j] + v[i][j - 1] - v[i - 1][j - 1];
    }
  }
  int q;
  cin >> q;
  while (q--)
  {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    int H = h[r2][c2 - 1] - h[r1 - 1][c2 - 1] - h[r2][c1 - 1] + h[r1 - 1][c1 - 1];
    int V = v[r2 - 1][c2] - v[r1 - 1][c2] - v[r2 - 1][c1 - 1] + v[r1 - 1][c1 - 1];
    cout << H + V << '\n';
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();

  return 0;
}
