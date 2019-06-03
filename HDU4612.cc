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

const int maxn = 200019;
int n, m, dfs_block, scc_cnt, last_node, bridge, ret;
int low[maxn];
int dfn[maxn];
int sccno[maxn];
int vis[maxn];
int dis[maxn];
vector<int> G[maxn], M[maxn];
stack<int> S;
//1 2两行去重边
//或者也可以用map在建图的时候重边直接不加入也可以
void dfs(int u, int fa)
{
    low[u] = dfn[u] = ++dfs_block;
    S.push(u);
    bool flag = false;//标记 1
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(!dfn[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u])
                bridge++;
        }
        else if(v != fa || flag)
            low[u] = min(low[u], low[v]);
        if(v == fa) flag = true;//标记2 同样边第二次就不会让通过了
        //只需要防止走回fa的边即可，不需要过多操作来去重边 2
    }
    if(low[u] == dfn[u])
    {
        ++scc_cnt;
        while(1)
        {
            int x = S.top(); S.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}

void find_scc()//tarjan
{
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) dfs(i, -1);
}

void bfs(int s)//bfs寻找树的直径
{
    queue<int> q;
    q.push(s);
    memset(vis, 0, sizeof(vis));
    vis[s] = 1;
    dis[s] = 0;
    last_node = s;

    ret = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = 0; i < M[u].size(); i++)
        {
            int v = M[u][i];
            if(!vis[v])
            {
                vis[v] = 1;
                dis[v] = dis[u] + 1;
                if(dis[v] > ret)
                {
                    ret = dis[v];
                    last_node = v;
                }
                q.push(v);
            }
        }
    }
}

void init() //初始化
{
    dfs_block = scc_cnt = last_node = bridge = ret = 0;
    for(int i = 0; i <= n; i++) low[i] = dis[i] = dfn[i] = sccno[i] = 0;
    for(int i = 0; i <= n; i++) G[i].clear(), M[i].clear();
    while(!S.empty()) S.pop();
}

int main()
{
    while(cin >> n >> m)
    {
        if(n == 0 && m == 0) break;
        init();
        int u, v;
        for(int i = 0; i < m; i++)
        {
            cin >> u >> v;
            G[v].push_back(u);
            G[u].push_back(v);
        }
        find_scc();

        for(int i = 1; i <= n; i++)//缩点后重新建图
            for(int j = 0; j < G[i].size(); j++)
            {
                int v = G[i][j];
                if(sccno[i] != sccno[v])
                {
                    M[sccno[i]].push_back(sccno[v]);
                    M[sccno[v]].push_back(sccno[i]);
                }
            }

        bfs(1);
        bfs(last_node);
        cout << bridge - ret << endl;
    }
    //system("pause");
    return 0;
}

/* 
4 4
1 2
1 3
1 4
2 3
0 0 
 */