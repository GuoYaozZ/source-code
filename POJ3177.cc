#include<set>
#include<map>
#include<cmath>
#include<deque>
#include<queue>
#include<stack>
#include<time.h>
#include<vector>
#include<cstdio>
#include<string>
#include<utility>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;

const int maxn = 5e3+19;
const int mod = 998244353;
const double eps = 1e-6;
const int inf = 0x3f3f3f3f;

vector<int> G[maxn];
int dfn[maxn];
int low[maxn];
int in[maxn];
int dfs_block, cnt;
map<pair<int, int>, int> mp;

void init(int n)
{
    for(int i = 0; i <= n; i++) in[i] = 0;
    for(int i = 0; i <= n; i++) dfn[i] = 0;
    for(int i = 0; i <= n; i++) low[i] = 0;
    dfs_block = cnt = 0;
    mp.clear();
}

void dfs(int u, int fa)
{
    low[u] = dfn[u] = ++dfs_block;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(!dfn[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if(v != fa)
            low[u] = min(low[u], low[v]);
    }
}

int main()
{
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    init(n);
    for(int i = 0; i < m; i++)
    {
        scanf("%d%d", &u, &v);
        if(u > v) swap(u, v);
        if(mp.find(make_pair(u, v)) != mp.end()) continue;
        mp[make_pair(u, v)] = 1;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, -1);
    for(int i = 1; i <= n; i++)
        for(int j = 0; j < G[i].size(); j++)
            if(low[i] != low[G[i][j]])
                in[low[G[i][j]]]++;
    for(int i = 1; i <= n; i++)
        if(in[i] == 1)
            cnt++;
    printf("%d\n", (cnt+1)/2);
    //system("pause");
    return 0;
}

/* 

 */