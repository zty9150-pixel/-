#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 10;
bitset<N> vis;
vector<int> g[N];
void dfs(int x)
{
    vis[x] = 1;
    for (auto i : g[x])
    {
        if (vis[i])
            continue;
        dfs(i);
    }
}
void bfs(int st)
{ // st为起始点
    queue<int> q;
    q.push(st);
    vis[st] = 1;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (auto i : g[x])
        {
            if (vis[i])
                continue;
            vis[i] = 1; // 入队就要标记
            q.push(i);
        }
    }
}
void solution()
{
    // 邻接表输入
}
int main()
{
}