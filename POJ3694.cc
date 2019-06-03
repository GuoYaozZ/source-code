/* 
如果在图上加上一条边(u, v) 那么这个图减少的桥的个数就是u和v到达LCA之间经过的桥的个数
 */
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

const int maxn = 1e5+19;
const int mod = 998244353;
const double eps = 1e-6;
const int inf = 0x3f3f3f3f;

vector<int> G[maxn];
int dfn[maxn];
int low[maxn];
int is[maxn];
int pre[maxn];
int vis[maxn];
int dfs_block;
int cnt;

void dfs(int u, int fa)
{
    pre[u] = fa;
    low[u] = dfn[u] = ++dfs_block;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(!dfn[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u])
            {
                cnt++;//记下桥的个数
                is[v] = 1;
            }
        }
        else if(v != fa)
            low[u] = min(low[u], low[v]);
    }
}

void init(int n)
{
    for(int i = 0; i <= n; i++) pre[i] = i;
    for(int i = 0; i <= n; i++) is[i] = 0;
    for(int i = 0; i <= n; i++) dfn[i] = 0;
    for(int i = 0; i <= n; i++) low[i] = 0;
    for(int i = 0; i <= n; i++) G[i].clear();
    dfs_block = cnt = 0;
}

void check(int u, int v)//用不压缩路径的并查集来寻找LCA
{
    if(dfn[u] > dfn[v]) swap(u, v);
    while(dfn[u] < dfn[v])
    {
        if(is[v] == 1) is[v] = 0,cnt--;  
        v = pre[v];
    }
    while(u != v)
    {
        if(is[v] == 1) is[v] = 0, cnt--;
        if(is[u] == 1) is[u] = 0, cnt--;
        v = pre[v];
        u = pre[u];
    }
}

int main()
{
    int n, m, q;
    int asdasd = 1;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0 && m == 0) break;
        init(n);
        int u, v;
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, 1);
        scanf("%d", &q);
        printf("Case %d:\n", asdasd++);
        for(int i = 0; i < q; i++)
        {
            scanf("%d%d", &u, &v);
            check(u, v);
            printf("%d\n", cnt);
        }
        printf("\n");
    }   
    //system("pause");
    return 0;
}

/* 

 */