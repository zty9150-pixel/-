#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;

int n, k;
ll a[N], pre[N], t1[N << 2], t2[N << 2];

void push1(int o)
{
    t1[o] = max(t1[o << 1], t1[o << 1 | 1]);
}
void push2(int o)
{
    t2[o] = min(t2[o << 1], t2[o << 1 | 1]);
}

void build1(int s = 0, int e = n, int o = 1) // 注1：从0开始维护，因为存在l1-1查询
{
    if (s == e)
    {
        t1[o] = pre[s];
        return;
    }
    int mid = (s + e) >> 1;
    build1(s, mid, o << 1);
    build1(mid + 1, e, o << 1 | 1);
    push1(o);
}

void build2(int s = 0, int e = n, int o = 1) // 同注1
{
    if (s == e)
    {
        t2[o] = pre[s];
        return;
    }
    int mid = (s + e) >> 1;
    build2(s, mid, o << 1);
    build2(mid + 1, e, o << 1 | 1);
    push2(o);
}

ll query1(int l, int r, int s = 0, int e = n, int o = 1)
{
    if (l <= s && e <= r)
    {
        return t1[o];
    }
    int mid = (s + e) >> 1;
    ll L = 0, R = 0;        // 注2:存在负值，所以需要tag标签来判断是否是废值
    int Ltag = 0, Rtag = 0; // 或者 ll L = LLONG_MIN, R = LLONG_MIN; ll L = LLONG_MAX, R = LLONG_MAX;
    if (mid >= l)
    {
        L = query1(l, r, s, mid, o << 1);
        Ltag = 1;
    }
    if (mid + 1 <= r)
    {
        R = query1(l, r, mid + 1, e, o << 1 | 1);
        Rtag = 1;
    }
    if (Ltag && Rtag) // 注3:分治思想，要对区间两边取答案
        return max(L, R);
    else
        return (Ltag ? L : R);
}

ll query2(int l, int r, int s = 0, int e = n, int o = 1)
{
    if (l <= s && e <= r)
    {
        return t2[o];
    }
    int mid = (s + e) >> 1;
    ll L = 0, R = 0;
    int Ltag = 0, Rtag = 0;
    if (mid >= l)
    {
        L = query2(l, r, s, mid, o << 1);
        Ltag = 1;
    }
    if (mid + 1 <= r)
    {
        R = query2(l, r, mid + 1, e, o << 1 | 1);
        Rtag = 1;
    }
    if (Ltag && Rtag)
        return min(L, R);
    else
        return (Ltag ? L : R);
}

void solve()
{
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        pre[i] = a[i] + pre[i - 1];
    }
    build1();
    build2();
    while (k--)
    {
        int l1, l2, r1, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        ll mn = query2(l1 - 1, r1 - 1); // 注4:被减的那个前缀和取i-1, pre[r] - pre[l - 1]
        ll mx = query1(l2, r2);
        cout << mx - mn << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
