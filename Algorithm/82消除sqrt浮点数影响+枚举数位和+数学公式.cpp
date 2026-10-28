/*
【数位和 + 枚举 + 一元二次方程】

一、题目核心
求最小的正整数 x，使得：
x * x + s(x) * x = n
其中 s(x) 表示 x 的十进制数位和。

二、为什么不能直接二分 x？
定义 f(x) = x * x + s(x) * x。
虽然 x * x 单调递增，但 s(x) 可能突然减小，导致 f(x) 不单调。
例如：
f(99) = 99 * 99 + 18 * 99 = 11583
f(100) = 100 * 100 + 1 * 100 = 10100
因此不能直接对 x 二分。

三、核心突破：枚举数位和
由 x * x < n <= 1e18，得到 x < 1e9。
所以 x 最多有 9 位，数位和满足：
1 <= s(x) <= 9 * 9 = 81
因此只需枚举 s = 1 ~ 81，而不是枚举 x。

四、固定数位和后求根
假设 s(x) = s，则：
x * x + s * x = n
整理为：
x * x + s * x - n = 0

根据求根公式：
x = (-s + sqrt(s * s + 4 * n)) / 2

令：
D = s * s + 4 * n
r = sqrt(D)

要得到整数解，必须满足：
1. D 是完全平方数，即 r * r == D。
2. r - s 是偶数，保证 x 是整数。
3. 实际数位和 digitSum(x) == s。

由于 n > 0，所以 D > s * s。
如果 D 是完全平方数，则 r > s，因此 x > 0，不需要额外判断 x <= 0。

五、浮点平方根修正
sqrtl() 返回浮点近似结果，转换为整数后可能受精度误差影响。
可以用整数运算修正：
while ((r + 1) * (r + 1) <= D)
    ++r;
while (r * r > D)
    --r;

最终保证：
r * r <= D < (r + 1) * (r + 1)

然后判断 r * r == D，即可确认 D 是否为完全平方数。
注意：修正操作是为了防止浮点误差，不是为了排除非整数平方根。

六、哪些判断可以省略？
1. r < s 可以省略，因为 D > s * s 且 r * r == D 时，必有 r > s。
2. x <= 0 可以省略，因为 x = (r - s) / 2 > 0。
3. x * x + s * x != n 可以省略，因为由 D = r * r 和 x = (r - s) / 2 可严格推出原方程成立。
4. 奇偶性判断在数学上也可省略：r * r - s * s = 4 * n，说明 r 和 s 同奇偶。
   但保留 (r - s) % 2 != 0 的判断，更直观地体现整数解条件。

七、正确性证明
任何合法答案 x 的数位和 s 必然在 1 ~ 81 内，因此枚举一定会遍历到 s(x)。
固定 s 后，原方程唯一确定 x = (sqrt(s*s + 4*n) - s) / 2。
通过完全平方数检查和实际数位和检查，能够排除所有不合法候选。
遍历全部 s 并取最小合法 x，即得到题目要求的答案。
如果没有合法候选，输出 -1。

八、复杂度
最多枚举 81 种数位和。
每次计算平方根并验证，时间复杂度为 O(1)。
总时间复杂度 O(81) = O(1)，空间复杂度 O(1)。

九、关键思想
原变量范围很大时，不一定直接枚举原变量或二分原变量。
如果方程中存在取值范围很小的辅助量，可以枚举辅助量，再通过数学公式求出原变量。
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 4000000 + 10;

ll n;

ll digitSum(ll x)
{
  ll ans = 0;
  while (x)
  {
    ans += x % 10;
    x /= 10;
  }
  return ans;
}

void solve()
{
  cin >> n;
  ll ans = -1;
  for (int s = 0; s <= 81; ++s)
  {
    ll D = s * s + 4 * n;
    ll r = ((long double)sqrtl(D));

    while ((r + 1) * (r + 1) <= D)
      r++;
    while (r * r > D)
      r--;

    if (r * r != D)
      continue;
    if ((r - s) % 2 || r <= s)
      continue;

    ll x = (r - s) / 2;
    if (digitSum(x) != s)
      continue;

    if (ans == -1 || x < ans)
      ans = x;
  }
  cout << ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // int t;
  // cin >> t;

  // while (t--)
  solve();

  return 0;
}