
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

char s[N], p[N];
int nex[N];

void solve() /********************便于理解版本******************* */
{
  cin >> (s + 1) >> (p + 1);

  int n = strlen(s + 1);
  int m = strlen(p + 1);

  // 1. 求 nex 数组
  nex[0] = nex[1] = 0;

  for (int i = 2, j = 0; i <= m; ++i)
  {
    // 失配：利用 nex 回退
    while (j && p[i] != p[j + 1])
      j = nex[j];

    // 匹配成功：长度 +1
    if (p[i] == p[j + 1])
      j++;

    nex[i] = j;
  }

  // 2. 利用 nex 数组进行匹配
  int ans = 0;

  for (int i = 1, j = 0; i <= n; ++i)
  {
    // 失配：利用 nex 回退
    while (j && s[i] != p[j + 1])
      j = nex[j];

    // 匹配成功：长度 +1
    if (s[i] == p[j + 1])
      j++;

    // 完整匹配成功
    if (j == m)
    {
      ans++; // 匹配次数
      // i - m + 1 为匹配起始位置

      j = nex[j]; // 回退，继续寻找
    }
  }

  cout << ans << '\n';
}

//*****************************KMP标准写法******************************* */
// 求模式串 p 的前缀函数（nex 数组）
vector<int> getNext(const string &p)
{
  int m = p.size();
  vector<int> ne(m, 0);

  for (int i = 1, j = 0; i < m; ++i)
  {
    // 失配：回退到更短的公共前后缀
    while (j && p[i] != p[j])
      j = ne[j - 1];

    // 匹配成功
    if (p[i] == p[j])
      j++;

    ne[i] = j;
  }

  return ne;
}

// KMP 匹配，返回所有匹配起始位置（0 下标）
vector<int> KMP(const string &s, const string &p)
{
  int n = s.size(), m = p.size();
  vector<int> ne = getNext(p);
  vector<int> ans;

  for (int i = 0, j = 0; i < n; ++i)
  {
    // 失配：利用 nex 回退
    while (j && s[i] != p[j])
      j = ne[j - 1];

    // 匹配成功
    if (s[i] == p[j])
      j++;

    // 完整匹配
    if (j == m)
    {
      ans.push_back(i - m + 1);
      j = ne[j - 1]; // 继续寻找，避免遗漏重叠匹配
    }
  }

  return ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();

  return 0;
}
