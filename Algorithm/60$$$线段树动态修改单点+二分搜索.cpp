/*
题目：动态添加 v_i身高，a_i人数，每次加完求领队身高
规则：全部人排序，找中间；偶数选偏左（矮的那个）
设总人数sum，目标位置 k = (sum + 1)/2 上取整，求第k小身高
n<=2e5，v可以1e9，离散化+线段树维护权值和，二分找第k小
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
int n, m;
ll t[N << 2];

// 向上合并区间和
void pushup(int o)
{
    t[o] = t[o << 1] + t[o << 1 | 1];
}
// 单点增加a，L是离散后的下标
void update(ll a, int L, int s = 1, int e = m, int o = 1)
{
    if (s == e)
    {
        t[o] += a;
        return;
    }
    int mid = (s + e) >> 1;
    if (L <= mid)
        update(a, L, s, mid, o << 1);
    else
        update(a, L, mid + 1, e, o << 1 | 1);
    pushup(o);
}
// 权值线段树二分查找第k小
int query(ll k, int s = 1, int e = m, int o = 1)
{
    if (s == e)
        return s;
    int mid = (s + e) >> 1;
    if (t[o << 1] >= k)
        return query(k, s, mid, o << 1);
    else
        return query(k - t[o << 1], mid + 1, e, o << 1 | 1);
}

void solve()
{
    cin >> n;
    vector<pair<ll, ll>> a(n + 1);
    vector<ll> v;
    // 读入，收集所有v用于离散化
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].first >> a[i].second;
        v.push_back(a[i].first);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    // 离散映射函数，v→压缩下标，从1开始
    auto get = [&](ll x)
    {
        return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
    };
    m = v.size();
    ll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        ll val = a[i].first, cnt = a[i].second;
        update(cnt, get(val));
        sum += cnt;
        ll k = (sum + 1) / 2; // 目标第k小
        int pos = query(k);
        cout << v[pos - 1] << '\n';
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
