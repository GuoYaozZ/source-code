/* 
这道题我的初始化出现问题，加之之前用邻接矩阵建图时间上太慢
后来改成链式前向星建图
反正就是做这道题之前 最好写一下POJ1904
 */
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
const int maxn = 2019;
const int maxm = 500100;
int G[maxn][maxn];
int low[maxn], dfn[maxn], sccno[maxn];

int ans[maxn];
bool used[maxn];
int linker[maxn];
int lx[maxn];

int stakc[maxn], top;
bool instakc[maxn];
int uN, vN, n, m, dfs_clock, scc_cnt, asdasd;
struct Edge
{
    int to,next;
}edge[maxm];
int head[maxn],tot;

void addedge(int u,int v)//链式前向星加边
{
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
}

void dfs(int u)
{
    low[u] = dfn[u] = ++dfs_clock;
    stakc[top++] = u;
    instakc[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        int v = edge[i].to;
        if(!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(instakc[v])
            low[u] = min(low[u], low[v]);
    }
    if(low[u] == dfn[u])
    {
        ++scc_cnt;
        while(1)
        {
            int v = stakc[--top];
            instakc[v] = false;
            sccno[v] = scc_cnt;
            if(v == u) break;
        }
    }
}
void find_scc()//tarjan
{
    memset(dfn, 0, sizeof(dfn));
    memset(instakc, false, sizeof(instakc));
    dfs_clock = scc_cnt = top = 0;
    for(int i = 1; i <= vN; i++)
        if(!dfn[i]) dfs(i);
}

bool check(int u)
{
    for(int v = 1; v <= vN; v++)
        if(!used[v] && G[u][v] == asdasd)
        {
            used[v] = true;
            if(linker[v] == -1 || check(linker[v]))
            {
                linker[v] = u;
                return true;
            }
        }
    return false;
}
int finds()//匈牙利二分图匹配
{
    int res = 0;
    memset(linker, -1, sizeof(linker));
    for(int u = 1; u <= uN; u++)
    {
        memset(used, false, sizeof(used));
        if(check(u)) res++;
    }
    return res;
}

int main()
{
    int T;
    scanf("%d", &T);
    for(asdasd = 1; asdasd <= T; asdasd++)
    {
        scanf("%d%d", &n, &m);
        int k, v;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &k);
            while(k--)
            {
                scanf("%d", &v);
                G[i][v] = asdasd;
            }
        }
        uN = n;
        vN = m;
        int res = finds();//匹配一次
        uN = vN = n+m-res;//建立虚拟的完美匹配图
        for(int i = n+1; i <= uN; i++)
            for(int j = 1; j <= vN; j++)
                G[i][j] = asdasd;
        for(int i = 1; i <= uN; i++)
            for(int j = m+1; j <= vN; j++)
                G[i][j] = asdasd;
        finds();//匹配二次
        memset(lx, -1, sizeof(lx));
        for(int i = 1; i <= vN; i++)
            if(linker[i] != -1)
                lx[linker[i]] = i;
        init();//前向星建图
        for(int i = 1; i <= uN; i++)
            for(int j = 1; j <= vN; j++)
                if(G[i][j] == asdasd && lx[i] != j)
                    addedge(lx[i], j);
        find_scc();//求强连通分量
        printf("Case #%d:\n", asdasd);
        for(int u = 1; u <= n; u++)
        {
            memset(ans, 0, sizeof(ans));
            k = 0;
            for(int v = 1; v <= m; v++)
            {
                if(G[u][v] == asdasd && sccno[lx[u]] == sccno[v])
                    ans[k++] = v;
            }
            sort(ans, ans+k);
            printf("%d", k);
            for(int i = 0; i < k; i++)
                printf(" %d", ans[i]);
            printf("\n");
        }
    }
    //system("pause");
    return 0;
}
/* 
3
4 4
2 1 2
2 1 2
2 2 3
2 3 4
1 2
2 1 2
 */