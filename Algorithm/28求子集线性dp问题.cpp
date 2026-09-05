#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 110;
const int mod = 998244353;

// 给定两个长度均为 n 的整数数组 a 和 b。
// 你可以任选一组下标子集，交换这些下标对应位置上的元素（即对子集中的每一个下标 i，执行 {swap}(a_i,b_i）。若交换完成后，两个数组都按非降序排列，则称该下标子集为合法子集。
// 你的任务是求出合法子集的数量。由于答案可能很大，请输出答案对 998244353 取模后的结果。

// 输入
// 第一行输入一个整数 $t$（$1 \le t \le 500$）——表示测试用例的组数。
// 每组测试用例的第一行输入一个整数 $n$（$1 \le n \le 100$）。
// 第二行输入 $n$ 个整数 $a_1,a_2,\dots,a_n$（$1 \le a_i \le 1000$）。
// 第三行输入 $n$ 个整数 $b_1,b_2,\dots,b_n$（$1 \le b_i \le 1000$）。

// 输入额外保证：至少存在一个合法子集。

// 输出
// 对于每组测试用例，输出一个整数——合法子集的数量，结果对 $998244353$ 取模。

int n, m, k;
int a[N], b[N];
int dp[N][2]; // dp表示遍历到i时选j或不选j的子集的合法子集数

void solution()
{
  memset(dp, 0, sizeof(dp));
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
    cin >> b[i];
  dp[1][0] = 1;
  dp[1][1] = 1;
  for (int i = 2; i <= n; ++i)
  {
    if (a[i - 1] <= a[i] && b[i - 1] <= b[i])
    {
      dp[i][0] = (dp[i][0] + dp[i - 1][0]) % mod;
    }
    if (b[i - 1] <= a[i] && a[i - 1] <= b[i])
    {
      dp[i][0] = (dp[i][0] + dp[i - 1][1]) % mod;
    }
    if (a[i - 1] <= b[i] && b[i - 1] <= a[i])
    {
      dp[i][1] = (dp[i][1] + dp[i - 1][0]) % mod;
    }
    if (b[i - 1] <= b[i] && a[i - 1] <= a[i])
    {
      dp[i][1] = (dp[i][1] + dp[i - 1][1]) % mod;
    }
  }
  std::cout << ((dp[n][0] + dp[n][1]) % mod) << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
  {
    solution();
  }
  return 0;
}