/*
二维递归填表（分治 + 坐标映射）

一、题目核心
给定一个 2^n * 2^n 的正方形表格，按照固定顺序填入 1 ~ 2^(2n)。
每次将当前表格划分为四个等大的子表，填充顺序为：
1. 左上
2. 右下
3. 左下
4. 右上
每个子表继续按照相同规则递归填充。

两种查询：
-> x y：查询第 x 行、第 y 列的数字。
<- d：查询数字 d 所在的行、列坐标。

二、递归的基本结构
len：当前子表的边长，初始为 2^n。
half = len / 2：子表边长的一半。
block = half * half：每个象限包含的数字个数。

递归终止条件：
当 len == 1 时，当前子表只有一个格子。
正向查询返回 1，反向查询返回坐标 (1, 1)。

三、正向查询：坐标 -> 数字
函数：getnum(x, y, len)

1. 判断坐标属于哪个象限。
2. 将全局坐标转换为当前子表的局部坐标。
3. 递归计算子表内部的数字。
4. 加上当前象限的数字偏移。

四个象限及其偏移：
左上：偏移 0
右下：偏移 block
左下：偏移 2 * block
右上：偏移 3 * block

坐标转换：
左上：(x, y)
右下：(x - half, y - half)
左下：(x - half, y)
右上：(x, y - half)

判断条件：
左上：x <= half && y <= half
右下：x > half && y > half
左下：x > half && y <= half
右上：x <= half && y > half

核心公式：
当前数字 = 象限偏移 + 子表内部的数字

五、反向查询：数字 -> 坐标
函数：getpos(d, len)

1. 每个象限有 block 个数字。
2. 计算数字所属的象限编号 part。
3. 计算数字在象限内部的编号 rem。
4. 递归求出 rem 在子表中的局部坐标。
5. 根据象限位置，将局部坐标还原为父表坐标。

代码：
part = (d - 1) / block;
rem = (d - 1) % block + 1;

part 的取值为 0、1、2、3：
0：左上
1：右下
2：左下
3：右上

为什么 d 要减 1？
因为 d 从 1 开始编号，而整数除法分组更适合从 0 开始。
(d - 1) / block 用来确定象限编号。
(d - 1) % block 得到从 0 开始的局部编号，再 +1 转换为从 1 开始的编号。

坐标还原：
part == 0：返回 (x, y)
part == 1：返回 (x + half, y + half)
part == 2：返回 (x + half, y)
part == 3：返回 (x, y + half)

六、两个递归函数的区别
正向查询：
全局坐标 -> 判断象限 -> 转换局部坐标 -> 递归 -> 加上数字偏移。

反向查询：
数字 -> 判断象限 -> 转换局部编号 -> 递归 -> 还原全局坐标。

七、复杂度分析
每次递归，len 都减半：
len -> len / 2 -> len / 4 -> ... -> 1

递归深度为 O(log len) = O(n)。
单次查询时间复杂度：O(n)。
递归栈空间复杂度：O(n)。
不需要真正构造整个二维表。

八、容易出错的地方
1. len 表示边长，不是格子总数。
2. 初始边长为 1LL << n。
3. 总格子数为 1LL << (2 * n)。
4. 象限顺序必须是左上、右下、左下、右上。
5. 进入下半部分时，行号减 half。
6. 进入右半部分时，列号减 half。
7. d - 1 用于将从 1 开始的编号转换为从 0 开始的编号。
8. n 最大为 30，总格子数可达 2^60，必须使用 long long。
9. 不建议用 pow 计算边长，使用 1LL << n 更直接。

九、记忆重点
这道题不需要构造整张表，而是每次只处理当前子表。
正向查询的关键是坐标映射和数字偏移。
反向查询的关键是利用整数除法确定象限，再还原坐标。
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll getnum(ll x, ll y, ll len)
{
  if (len == 1)
    return 1;

  ll half = len / 2;
  ll block = half * half;

  if (x <= half && y <= half)
    return getnum(x, y, half);

  if (x > half && y > half)
    return block + getnum(x - half, y - half, half);

  if (x > half && y <= half)
    return 2 * block + getnum(x - half, y, half);

  return 3 * block + getnum(x, y - half, half);
}

pair<ll, ll> getpos(ll d, ll len)
{
  if (len == 1)
    return {1, 1};

  ll half = len / 2;
  ll block = half * half;

  ll part = (d - 1) / block;
  ll rem = (d - 1) % block + 1;

  auto [x, y] = getpos(rem, half);

  if (part == 0)
    return {x, y};

  if (part == 1)
    return {x + half, y + half};

  if (part == 2)
    return {x + half, y};

  return {x, y + half};
}

void solve()
{
  int n, q;
  cin >> n >> q;

  ll len = 1LL << n;

  while (q--)
  {
    string op;
    cin >> op;

    if (op == "->")
    {
      ll x, y;
      cin >> x >> y;
      cout << getnum(x, y, len) << '\n';
    }
    else
    {
      ll d;
      cin >> d;
      auto [x, y] = getpos(d, len);
      cout << x << ' ' << y << '\n';
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--)
    solve();

  return 0;
}
