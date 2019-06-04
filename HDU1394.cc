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

const int maxn = 5555;
int tree[maxn<<2];
int a[maxn];

void push_up(int rt)
{
    tree[rt] = tree[rt<<1] + tree[rt<<1|1];
}

void build(int l, int r, int rt)
{
    tree[rt] = 0;
    if(l == r)
    {
        return;
    }
    int m = (l+r) >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

void update(int p, int l, int r, int rt)
{
    if(l == r)
    {
        tree[rt]++;
        return;
    }
    int m = (l+r) >> 1;
    if(p <= m) update(p, lson);
    else update(p, rson);
    push_up(rt);
}

int query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r)
    {
        return tree[rt];
    }
    int m = (l+r) >> 1;
    int ret = 0;
    if(L <= m) ret += query(L, R, lson);
    if(R > m) ret += query(L, R, rson);
    return ret;
}

int main()
{
    int n;
    while(cin >> n)
    {
        build(0, n-1, 1);/* 这里应该注意到，建树的前两个参数只是代表区间而已，甚至可以写成100，100+n-1 */
        int sum = 0;
        for(int i = 0; i < n; i++)
        {
            cin >> a[i];
            sum += query(a[i], n-1, 0, n-1, 1);
            /* 查找有多少个比a[i]大的并且在它之前就加进来的（即在a数组中位于之前的）
            在a[i]这里新添加一个 */
            update(a[i], 0, n-1, 1);
        }
        int ret = sum;
        for(int i = 0; i < n; i++)
        {
            ret += (n-a[i]-a[i]-1);
            /* 每一次将第一个数移到最后的时候，第一个数原本对逆序数的影响就是a[i]（a[i] = 2， 则有0和1）个，因为后边比他小的，移到最后又多出来n-1-a[i]个 */
            sum = min(ret, sum);
        }
        cout << sum << endl;
    }
    //system("pause");
    return 0;
}
/* 

 */