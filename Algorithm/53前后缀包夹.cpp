/*
题型：字符串 前缀后缀统计 子序列计数 O(n)
题意：
子序列wow，其中本题w定义为【连续两个v(vv)】
一段连续k个v，可以产生 k-1 个w。
wow = 左边一个w + o + 右边一个w，w必须在o两侧。
求整个字符串中wow子序列总个数。
输入：仅由v、o组成的字符串，长度<=1e6
输出：wow总数量，答案用long long

思路：
1. pre[i]：s[0~i]累计有多少个w
2. suf[i]：s[i~end]累计有多少个w
3. 遍历每个o，贡献 = o左侧全部w数量 * o右侧全部w数量
4. 累加所有o的贡献即为答案

样例：vvvovvv
左vvv：2个w；右vvv：2个w；o贡献2*2=4，输出4

坑点：
1. w要求v相邻，不是任意两个v
2. 数据范围大，必须long long，不能暴力枚举
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;

string s;
int pre[N];

void solve()
{
  cin >> s;
  int len = s.length();
  s = '0' + s;
  for (int i = 1; i <= len; ++i)
  {
    if (s[i] == 'v' && s[i - 1] == 'v')
      pre[i] = pre[i - 1] + 1;
    else
    {
      pre[i] = pre[i - 1];
    }
  }
  ll ans = 0;
  for (int i = 1; i <= len; ++i)
  {
    if (s[i] == 'v')
      continue;
    ans += 1LL * pre[i - 1] * (pre[len] - pre[i]); // 1LL不能少！！！！！
  }
  cout << ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();

  return 0;
}
