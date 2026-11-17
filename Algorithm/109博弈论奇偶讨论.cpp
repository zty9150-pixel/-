
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
题目：J - Eat the Chip
考点：博弈论、奇偶性、贪心、边界距离

一、题目说明
    棋盘大小为 h * w，Alice 和 Bob 分别位于 (xa,ya)、(xb,yb)，
    Alice 先手。

    Alice 每次向下移动一格（可斜向）：
        (x+1,y), (x+1,y-1), (x+1,y+1)

    Bob 每次向上移动一格（可斜向）：
        (x-1,y), (x-1,y-1), (x-1,y+1)

    不能走出棋盘，也不能停留在原地。

    如果走到对方所在格子则获胜；
    如果某一方无法移动且无人获胜，则 Draw。

二、核心思路
    1. 如果 xa >= xb：
       两人行方向相反，无法相遇，Draw。

    2. 计算行距离 d = xb - xa。

    3. 根据 d 的奇偶性判断谁有先接触的机会。

三、d 为偶数：Bob 有利（追击者）

    Bob 可以利用每轮的移动追赶 Alice。

    如果两人初始在同一列，Bob 可以直接获胜。

    否则计算 Bob 到 Alice 逃跑方向边界的距离：

        ya < yb：Alice 向左逃，k = yb - 1
        ya > yb：Alice 向右逃，k = w - yb

    Bob 每轮最多缩短行距离 2，因此需要：
        d >= 2 * k

    满足则 Bob 胜，否则 Draw。

四、d 为奇数：Alice 有利（追击者）

    Alice 先移动一步，优先向 Bob 的列靠近：

        ya < yb：ya++
        ya > yb：ya--
        ya == yb：列不变

    如果移动后两人列相同，Alice 必胜。

    否则 Alice 追击 Bob，Bob 会向边界逃跑：

        ya < yb：Bob 向右逃，k = w - ya
        ya > yb：Bob 向左逃，k = ya - 1

    Alice 剩余追击时间需要满足：
        d >= 2 * k

    满足则 Alice 胜，否则 Draw。

五、总结
    行距离奇偶性决定追击者：
        偶数 -> Bob
        奇数 -> Alice

    追击者先确定逃跑方向，再计算到边界的距离 k。

    最终统一判断：
        d >= 2 * k

复杂度：O(1)
*/

void solve()
{
  ll h, w, x1, y1, x2, y2;
  cin >> h >> w >> x1 >> y1 >> x2 >> y2;

  if (x1 >= x2)
  {
    cout << "Draw\n";
    return;
  }

  ll d = x2 - x1;

  if (d % 2 == 0)
  {
    // 偶数：Bob 追击
    if (y1 == y2)
    {
      cout << "Bob\n";
      return;
    }

    ll k = (y1 < y2 ? y2 - 1 : w - y2);

    cout << (d >= 2 * k ? "Bob\n" : "Draw\n");
  }
  else
  {
    // 奇数：Alice 先移动，向 Bob 靠近
    if (y1 < y2)
      y1++;
    else if (y1 > y2)
      y1--;

    if (y1 == y2)
    {
      cout << "Alice\n";
      return;
    }

    ll k = (y1 < y2 ? w - y1 : y1 - 1);

    cout << (d >= 2 * k ? "Alice\n" : "Draw\n");
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--)
    solve();

  return 0;
}
