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

const int maxn = 200005;
int tree[maxn<<2], h, w, n, solo;

void push_up(int rt)
{
    tree[rt] = max(tree[rt<<1], tree[rt<<1|1]);
}

void build(int l, int r, int rt, int w)
{
    if(l == r)
    {
        tree[rt] = w;
        return;
    }
    int m = (l+r) >> 1;
    build(lson, w);
    build(rson, w);
    push_up(rt);
}

void update(int p, int add, int l, int r, int rt)
{
    if(l == r)
    {
        tree[rt] += add;
        return;
    }
    int m = (l + r) >> 1;
    if(p <= m) update(p, add, lson);
    else update(p, add, rson);
    push_up(rt);
}

int query(int p, int l, int r, int rt)
{
    if(l == r)
    {
        tree[rt] -= p;
        return l;
    }
    int ret = -1;
    int m = (l + r) >> 1;
    if(tree[rt << 1] >= p) ret = query(p, lson);
    else ret = query(p, rson);
    push_up(rt);
    return ret;
}

int main()
{
    while(~scanf("%d%d%d", &h, &w, &n))
    {
        if(h >= n) solo = n;
        else solo = h;
        build(1, solo, 1, w);
        int wi, ans;
        _for(i, 0, n)
        {
            scan_f(wi);
            if(tree[1] < wi) printf("-1\n");
            else printf("%d\n", query(wi, 1, solo, 1));
        }
    }
    return 0;
}