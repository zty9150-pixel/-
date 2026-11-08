
#include <bits/stdc++.h>
using namespace std;

const int N = 210;

int n, m;
int pre[N];

// 最大生成树：边权从大到小
struct node
{
  int x, y, w;

  bool operator<(const node &u) const
  {
    return w > u.w;
  }
};

// 环形字符串的最长公共子串
int get(string s, string t)
{
  // 环形展开：复制一遍，处理跨越首尾的匹配
  s += s;
  t += t;

  // dp[i][j]：以 s[i-1]、t[j-1] 结尾的最长公共子串长度
  vector<vector<int>> dp(2 * m + 1, vector<int>(2 * m + 1, 0));

  int ans = 0;

  for (int i = 1; i <= 2 * m; ++i)
  {
    for (int j = 1; j <= 2 * m; ++j)
    {
      if (s[i - 1] == t[j - 1])
      {
        // 字符相同，接在左上角的匹配后面
        // 最长匹配不能超过原字符串长度 m
        dp[i][j] = min(m, dp[i - 1][j - 1] + 1);
        ans = max(ans, dp[i][j]);
      }
      else
      {
        // 子串必须连续，不相等就归零
        dp[i][j] = 0;
      }
    }
  }

  return ans;
}

// 并查集：路径压缩
int root(int x)
{
  return pre[x] == x ? x : pre[x] = root(pre[x]);
}

void solve()
{
  cin >> n >> m;

  vector<string> a(n);
  vector<node> es;

  for (int i = 0; i < n; ++i)
    cin >> a[i];

  // 初始化并查集
  for (int i = 0; i < n; ++i)
    pre[i] = i;

  // 建完全图：每两个字符串之间建立一条边
  // 边权为两个环形字符串的最长公共子串长度
  for (int i = 0; i < n; ++i)
  {
    for (int j = i + 1; j < n; ++j)
    {
      int w = get(a[i], a[j]);
      es.push_back({i, j, w});
    }
  }

  // Kruskal 最大生成树
  sort(es.begin(), es.end());

  int ans = 0, cnt = 0;

  for (auto [x, y, w] : es)
  {
    int fx = root(x);
    int fy = root(y);

    if (fx == fy)
      continue;

    pre[fx] = fy;
    ans += w;
    cnt++;

    if (cnt == n - 1)
      break;
  }

  cout << ans << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
  return 0;
}

/*
知识点总结：

一、环形字符串
1. s += s：复制一遍，将循环匹配转化为普通连续子串匹配。
2. 原字符串长度为 m，因此最长匹配不能超过 m。
3. DP 遍历范围为 [1, 2m]。

二、最长公共子串 vs LCS

最长公共子串（必须连续）：
    相等：dp[i][j] = dp[i-1][j-1] + 1
    不等：dp[i][j] = 0
    答案：所有 dp[i][j] 的最大值。

LCS 最长公共子序列（不要求连续）：
    相等：dp[i][j] = dp[i-1][j-1] + 1
    不等：dp[i][j] = max(dp[i-1][j], dp[i][j-1])
    答案：dp[n][m]。

记忆：
    子串必须连续，不匹配就断开；
    子序列允许跳过，可以继承上方或左方的最优解。

三、最大生成树
1. 每个字符串看作一个点。
2. 两个字符串的最大公共子串长度作为边权。
3. 边权降序排序。
4. 并查集判断是否形成环。
5. 每次选择最大合法边，直到选出 n-1 条边。

四、复杂度
设字符串数量为 n，长度为 m：

建图及边权计算：O(n²m²)
排序：O(n²log n)
Kruskal：O(n²α(n))

总复杂度：O(n²m² + n²log n)
*/
