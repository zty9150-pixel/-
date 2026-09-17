#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 10;

// 关于向量王国起源的传说提到两个整数$x$和$y$。数百年前，数组国王在数轴上的$|x|$与$|y|$两点放置标记，占领了两点之间的全部区域（包含端点），并将这片土地命名为数组王国。多年以后，向量国王在$|x-y|$和$|x+y|$两点放置标记，占领了两点之间的全部区域（包含端点），将其命名为向量王国。向量国王的这片领地满足：数组王国的土地完全包含在向量王国之内（包含端点）。

// 其中$|z|$表示$z$的绝对值。

// 现在，何塞被历史试卷上的一道题难住了：“$x$和$y$的值是多少？”何塞不知道答案，但他认为候选答案可以缩小到$n$个整数$a_1,a_2,\dots,a_n$。现在他想知道，从这$n$个整数中选取两个不同元素组成的无序对一共有多少组，满足：若$x$和$y$取这两个数，则传说中的条件成立。注意何塞的猜想可能不成立，也就是不存在任何满足条件的数对。

// 输入
// 第一行输入一个整数$n$（$2\le n\le 2\cdot10^5$）——候选数字的数量。

// 第二行包含$n$个互不相同的整数$a_1,a_2,\dots,a_n$（$-10^9\le a_i\le10^9$）——何塞考虑的候选数值。

// 输出
// 输出一个整数，表示从候选数字里选取两个不同数字构成、能够满足传说条件的无序数对$\{x,y\}$的数量。

int n;
ll a[N];

bool check(ll x, ll y)
{
  if (x > y)
    swap(x, y);

  return y <= 2 * x;
}

void solution()
{
  cin >> n;

  for (int i = 1; i <= n; ++i)
  {
    cin >> a[i];
    a[i] = abs(a[i]);
  }
  sort(a + 1, a + n + 1);
  int l = 1, r = 2;
  ll ans = 0;
  while (r <= n)
  {
    if (check(a[l], a[r]))
    {
      ans += r - l;
      r++;
    }
    else
    {
      l++;
    }
  }

  cout << ans << '\n';
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solution();

  return 0;
}