#include<iostream>
#include<queue>
#include<cstring>
#include<String>
#include<vector>
#include<stack>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<set>
#include<map>
using namespace std;
#define ll long long

const int maxn = 4019;
int dfn[maxn];
int low[maxn];
int sccno[maxn];
int n, m, dfs_clock, scc_cnt;
vector<int> G[maxn];
stack<int> S;
int ans[maxn];

void init()
{
    for(int i = 0; i <= n; i++) dfn[i] = low[i] = sccno[i] = 0;
    for(int i = 0; i <= n; i++) G[i].clear();
    while(!S.empty()) S.pop();
}

void dfs(int u)
{
    low[u] = dfn[u] = ++dfs_clock;
    S.push(u);
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!sccno[v])
            low[u] = min(low[u], low[v]);
    }
    if(low[u] == dfn[u])
    {
        ++scc_cnt;
        while(1)
        {
            int x = S.top();
            S.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}

void find_scc()
{
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) dfs(i);
}

int main()
{
    scanf("%d", &n);
    init();
    int k, v;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &k);
        while(k--)
        {
            scanf("%d", &v);
            G[i].push_back(v+n);
        }
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &v);
        G[v+n].push_back(i);
    }
    find_scc();
    for(int u = 1; u <= n; u++)
    {
        memset(ans, 0, sizeof(ans));
        int k = 0;
        for(int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i];
            if(sccno[u] == sccno[v])
            {
                ans[k++] = v;
            }
        }
        sort(ans, ans+k);
        printf("%d", k);
        for(int i = 0; i < k; i++)
            printf(" %d", ans[i]-n);
        printf("\n");
    }
    //system("pause");
    return 0;
}