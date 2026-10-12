/*
题目：仪仗队淘汰士兵
N个士兵礼仪值A[i]，K次操作。
每次给定当前序列的区间[l,r]，删除区间内最小值，有多个最小值删最左边那个。
每次删除后序列长度-1。求K次删除后剩余总和。

输入：
第一行N；第二行N个A_i；第三行K；之后K行l,r（l,r对应当前序列下标）
输出：剩余礼仪值总和

范围：N≤5e5，A_i≤1e9，K<N
样例：
5
1 2 4 5 4
3
2 3
1 3
1 3
输出：9
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;

int n, k;
int a[N], t[N << 2], tz[N]; // t:线段树，tz:树状数组
// 线段树维护最小值下标，树状数组二分维护真实下标
// 树状数组：
void updates(int x, int w)
{
    for (int i = x; i <= n; i += i & -i)
        tz[i] += w;
}

int check(int x)
{
    int res = 0;
    for (int i = x; i >= 1; i -= i & -i)
        res += tz[i];
    return res;
}

int querys(int x) // 线段树删去点后下标错乱，树状数组二分修正真实下标
{
    int l = 1, r = n;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid) >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return r;
}
// 线段树：
void push(int o)
{
    if (a[t[o << 1]] <= a[t[o << 1 | 1]])
        t[o] = t[o << 1];
    else
        t[o] = t[o << 1 | 1];
}
void bulid(int s = 1, int e = n, int o = 1)
{
    if (s == e)
    {
        t[o] = s;
        return;
    }
    int mid = (s + e) >> 1;
    bulid(s, mid, o << 1);
    bulid(mid + 1, e, o << 1 | 1);
    push(o);
}

void update(int L, int s = 1, int e = n, int o = 1)
{
    if (s == L && e == L)
    {
        t[o] = 0; // a[0] = INT_MAX,保证了它的父节点不会保存它，即消除此点
        return;
    }
    int mid = (s + e) >> 1;
    if (mid >= L)
        update(L, s, mid, o << 1);
    else
        update(L, mid + 1, e, o << 1 | 1);
    push(o);
}

int query(int l, int r, int s = 1, int e = n, int o = 1)
{
    if (s >= l && e <= r)
        return t[o];
    int mid = (s + e) >> 1;
    int L = -1, R = -1;
    if (mid >= l)
        L = query(l, r, s, mid, o << 1);
    if (mid + 1 <= r)
        R = query(l, r, mid + 1, e, o << 1 | 1);
    if (L != -1 && R != -1)
    {
        return (a[L] <= a[R] ? L : R);
    }
    else
        return (L != -1 ? L : R);
}

void solve()
{
    cin >> n;
    ll sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        sum += a[i];
        updates(i, 1);
    }
    bulid();
    a[0] = INT_MAX;
    cin >> k;
    while (k--)
    {
        int l, r;
        cin >> l >> r;
        int x = query(querys(l), querys(r));
        sum -= a[x];
        update(x);
        updates(x, -1);
    }
    cout << sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}