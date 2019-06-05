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

const int maxn = 111111;
ll tree[maxn<<2];
ll col[maxn<<2];

void push_up(int rt)
{
    tree[rt] = tree[rt<<1] + tree[rt<<1|1];
}

void push_down(int rt, int l)
{
    if(col[rt])
    {
        col[rt<<1] += col[rt];
        col[rt<<1|1] += col[rt];
        tree[rt<<1] += (l - (l >> 1)) * col[rt];
        tree[rt<<1|1] += (l >> 1) * col[rt];
        col[rt] = 0;
    }
}

void build(int l, int r, int rt)
{
    col[rt] = 0;
    if(l == r)
    {
        scanf("%lld", &tree[rt]);
        return;
    }
    int m = (l+r)>>1;
    build(lson);
    build(rson);
    push_up(rt);
}

void update(int L, int R, int c, int l, int r, int rt)
{
    if(L <= l && R >= r)
    {
        col[rt] += c;
        tree[rt] += (ll)c*(r-l+1);
        return;
    }
    push_down(rt, r-l+1);
    int m = (l+r)>>1;
    if(L <= m) update(L, R, c, lson);
    if(R > m) update(L, R, c, rson);
    push_up(rt);
}

ll query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r)
    {
        return tree[rt];
    }
    push_down(rt, r-l+1);
    int m = (r+l)>>1;
    ll ret = 0;
    if(L <= m) ret += query(L, R, lson);
    if(R > m) ret += query(L, R, rson);
    return ret;
}

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    build(1, n, 1);
    int a, b, c;
    char op[3];
    while(q--)
    {
        scanf("%s", op);
        if(op[0] == 'C')
        {
            scanf("%d%d%d", &a, &b, &c);
            update(a, b, c, 1, n, 1);
        }
        else
        {
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(a, b, 1, n, 1));
        }
    }
    //system("pause");
    return 0;
}

/* 

10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4
 */