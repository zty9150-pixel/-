#include <iostream>
#include <cstring>
using namespace std;

int n, m;
int tile[20][20]; // 初始地图
int flip[20][20]; // 当前尝试的翻转方案
int res[20][20];  // 保存最佳翻转方案
int opt[20][20];  // 当前递推中网格的状态

// 方向数组：当前、上、右、下、左
int dx[] = {0, -1, 0, 1, 0};
int dy[] = {0, 0, 1, 0, -1};

// 查询 (x, y) 最终的颜色（原颜色 + 周围所有的翻转影响）
int get_color(int x, int y)
{
  int c = tile[x][y];
  for (int i = 0; i < 5; ++i)
  {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 1 && nx <= n && ny >= 1 && ny <= m)
    {
      c += flip[nx][ny];
    }
  }
  return c % 2; // 翻转偶数次等于没翻，奇数次翻转颜色改变
}

int calc()
{
  // 根据第 1 行推导第 2 ~ n 行
  for (int i = 2; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      if (get_color(i - 1, j) == 1)
      { // 上面是黑色，这一格必须翻
        flip[i][j] = 1;
      }
    }
  }

  // 检查第 n 行是否全白
  for (int j = 1; j <= m; ++j)
  {
    if (get_color(n, j) == 1)
      return -1; // 不可行
  }

  // 统计总翻转次数
  int sum = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      sum += flip[i][j];
  return sum;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  if (!(cin >> n >> m))
    return 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> tile[i][j];

  int min_flips = -1;

  // 枚举第 1 行的所有 $2^m$ 种翻转可能（从 0 到 (1<<m)-1 字典序递增）
  for (int state = 0; state < (1 << m); ++state)
  {
    memset(flip, 0, sizeof(flip));

    for (int j = 1; j <= m; ++j)
    {
      // 注意字典序：题目要求输出最小字典序
      flip[1][j] = (state >> (m - j)) & 1;
    }

    int cnt = calc();
    if (cnt != -1 && (min_flips == -1 || cnt < min_flips))
    {
      min_flips = cnt;
      memcpy(res, flip, sizeof(flip));
    }
  }

  if (min_flips == -1)
  {
    cout << "IMPOSSIBLE\n";
  }
  else
  {
    for (int i = 1; i <= n; ++i)
    {
      for (int j = 1; j <= m; ++j)
      {
        cout << res[i][j] << (j == m ? "" : " ");
      }
      cout << "\n";
    }
  }
  return 0;
}