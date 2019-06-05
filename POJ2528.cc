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
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1

const int maxn = 11111;
int l[maxn], r[maxn];
int col[maxn<<4];
int disc[maxn<<2];
int vis[maxn];

void push_down(int rt)
{
    if(col[rt] != -1)
    {
        col[rt<<1] = col[rt<<1|1] = col[rt];
        col[rt] = -1;
    }
}

void update(int L, int R, int c, int l, int r, int rt)
{
    if(L <= l && R >= r)
    {
        col[rt] = c;
        return;
    }
    push_down(rt);
    int m = (l+r) >> 1;
    if(L <= m) update(L, R, c, lson);
    if(R > m) update(L, R, c, rson);
}

int sum = 0;
void query(int l, int r, int rt)
{
    if(col[rt] != -1)
    {
        if(!vis[col[rt]]) sum++;
        vis[col[rt]] = true;
        return;
    }
    if(l == r) return;
    int m = (l+r)>>1;
    query(lson);
    query(rson);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--)
    {
        int n; scanf("%d", &n);
        int u, v;
        int tot = 0, cnt = 1;
        for(int i = 0; i < n; i++)
        {
            scanf("%d%d", &l[i], &r[i]);
            disc[tot++] = l[i];
            disc[tot++] = r[i];
        }
        sort(disc, disc+tot);
        for(int i = 1; i < tot; i++)
        {
            if(disc[i] != disc[i-1])
                disc[cnt++] = disc[i];
        }
        for(int i = cnt-1; i >= 1; i--)
        {
            if(disc[i] != disc[i-1]+1) 
                disc[cnt++] = disc[i-1] + 1;
        }
        sort(disc, disc+cnt);
        for(int i = 0; i < n; i++)
        {
            l[i] = lower_bound(disc, disc+cnt, l[i]) - disc + 1;
            r[i] = lower_bound(disc, disc+cnt, r[i]) - disc + 1;
        }
        sum = 0;
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < n; i++)
            update(l[i], r[i], i, 1, cnt, 1);
        query(1, cnt, 1);
        printf("%d\n", sum);
    }
    //system("pause");
    return 0;
}