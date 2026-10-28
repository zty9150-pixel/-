/*
【阶乘比较 + 对数预处理 + 二分答案】

一、题目核心
给定正整数 a，求最小的正整数 n，使得：
n! > a^n

二、为什么不能直接计算？
n! 和 a^n 可能非常大，直接计算容易溢出。
因此使用自然对数，将乘法和幂转化为加法和乘法。

因为 ln(x) 在 x > 0 时严格单调递增：
n! > a^n
等价于：
ln(n!) > ln(a^n)
即：
ln(n!) > n * ln(a)

三、预处理对数
定义：
lg[i] = ln(i!)

根据对数性质：
ln(i!) = ln((i-1)! * i)
        = ln((i-1)!) + ln(i)

所以：
lg[0] = 0
lg[i] = lg[i-1] + logl(i)

预处理后，可以 O(1) 查询 ln(i!)，避免每次二分都重新计算整个阶乘的对数。

代码：
lg[0] = 0;
for (int i = 1; i < N; ++i)
    lg[i] = lg[i - 1] + logl(i);

注意：
1. lg[i] 保存的是 ln(i!)，不是 i! 本身。
2. logl(i) 计算自然对数。
3. lg 和 target 必须使用浮点类型，例如 long double。
4. 不能将 logl(a) 存入 long long，否则小数部分会被截断。

四、为什么可以二分？
定义：
F(n) = ln(n!) - n * ln(a)

目标是找到最小的 n，使得 F(n) > 0。

当 n <= a 时，每个阶乘因子都不超过 a，因此：
n! <= a^n
所以答案一定大于 a。

再看相邻两项：
F(n+1) - F(n)
= ln(n+1) - ln(a)
= ln((n+1)/a)

当 n >= a 时，n+1 > a，因此：
F(n+1) - F(n) > 0

所以 F(n) 从 n >= a 的位置开始严格递增。
在这个范围内，条件 F(n) > 0 具有单调性，可以二分最小满足条件的 n。

五、为什么右边界可以取 4 * a？
需要证明 4 * a 一定满足：
(4a)! > a^(4a)

利用积分估计：
ln(n!) >= n * ln(n) - n + 1

令 n = 4a：
ln((4a)!)
>= 4a * ln(4a) - 4a + 1
= 4a * ln(a) + 4a * (ln(4) - 1) + 1

因为 ln(4) > 1，所以：
ln((4a)!) > 4a * ln(a)

因此：
(4a)! > a^(4a)

所以可以取：
l = a
r = 4 * a

其中 l 是不满足条件的边界，r 是满足条件的边界。

六、二分判断
每次计算：
mid = (l + r) / 2

判断：
lg[mid] > mid * logl(a)

如果成立，说明 mid 已满足条件，答案在左侧或就是 mid：
r = mid

否则，答案在右侧：
l = mid + 1

最终 l 就是最小满足条件的 n。

七、正确性证明
1. 当 n <= a 时，n! <= a^n，因此答案大于 a。
2. 当 n >= a 时，F(n) 严格递增，满足条件后不可能再次失效。
3. 4a 一定满足条件，因此答案存在于 [a, 4a]。
4. 二分每次保留可能包含最小合法答案的区间，最终得到最小满足条件的 n。

八、复杂度
设 M = 4 * max(a)。
预处理时间复杂度：O(M)。
每组查询的二分时间复杂度：O(log a)。
空间复杂度：O(M)。

如果使用固定数组，必须确保最大查询值满足 4 * a < N。
如果 a 的范围变化较大，可以先读取全部测试数据，再根据 max(a) 决定预处理范围。

九、容易出错的地方
1. target 必须写成：
   long double target = logl(a);
   不能写成 long long target。

2. 比较时必须使用：
   lg[mid] > mid * target
   不能使用 >=，因为题目要求严格大于。

3. 不能直接计算 n! 或 a^n，避免数值溢出。

4. 预处理必须在查询前完成。
   如果程序启动后长时间没有输出，可能正在预处理，也可能在等待输入。

十、关键思想
当两个很大的正数相乘或取幂后难以比较时，可以考虑取对数。
当预处理结果会被反复查询时，可以提前计算并保存。
当判断条件在搜索区间内具有单调性时，可以使用二分答案。
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 4000000 + 10;

ll a;
long double lg[N];

void init()
{
  for (int i = 1; i < N; ++i)
  {
    lg[i] = lg[i - 1] + logl(i);
  }
}

void solve()
{
  cin >> a;
  ll l = a, r = 4 * a;
  long double target = logl(a);
  while (l < r)
  {
    ll mid = (l + r) >> 1;
    if (lg[mid] > mid * target)
      r = mid;
    else
    {
      l = mid + 1;
    }
  }
  cout << l << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t;
  cin >> t;
  while (t--)
  {
    solve();
  }

  return 0;
}
