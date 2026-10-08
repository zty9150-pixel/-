/*
题目：数组切分成k个连续非空段，求最大代价
代价定义：sum( a[i] * f(i) )，f(i)代表第i个元素属于第几段（从左到右编号1~k）
n<=3e5
思路推导：
设前缀和 s[0]=0, s[i]=a1+a2+...+ai
原式展开：
第1段所有a乘1，第2段所有a乘2 ...第k段乘k
= sum(a) + sum(第2段a) + sum(第3段a)+...+sum(第k段a)
解释：
a*1 = a
a*2 = a+a
a*3 = a+a+a
累加后等价全部加一遍，第二段再多一遍，第三段再多一遍...第k段再多一遍
也就是 total_sum + s[pos1] + s[pos2] + ... + s[pos_{k-1}]
pos1,pos2...pos_{k-1} 是分割点（分割在pos后面，pos范围1~n-1）
要求选k-1个不同分割点，取出s[pos]最大的k-1个相加，再加上总和就是答案
步骤：
1.计算数组总和total_sum
2.计算前缀和s[1~n-1]（分割点只能在1~n-1）
3.把s[1]到s[n-1]排序，取最大k-1个累加
4.ans = total_sum + 选出的这k-1个数之和
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ll> a(n + 1), suf(n + 2, 0);
    ll ans = 0;

    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        ans += a[i];
    }

    for (int i = n; i >= 1; --i)
    {
        suf[i] = suf[i + 1] + a[i];
    }

    vector<ll> gains;
    for (int i = 2; i <= n; ++i)
    {
        gains.push_back(suf[i]);
    }

    sort(gains.begin(), gains.end(), greater<ll>());

    for (int i = 0; i < k - 1; ++i)
    {
        ans += gains[i];
    }

    cout << ans << '\n';
    return 0;
}
