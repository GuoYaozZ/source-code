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

const int maxn = 55555;
int tree[maxn<<2];

void push_up(int rt)
{
    tree[rt] = tree[rt<<1] + tree[rt<<1|1];
}

void build(int l, int r, int rt)
{
    if(l == r)
    {
        cin >> tree[rt];
        return;
    }
    int m = (l+r)>>1;
    build(lson);
    build(rson);
    push_up(rt);
}

void update(int p, int add, int l, int r, int rt)
{
    if(l == r)
    {
        tree[rt] += add;
        return;
    }
    int m = (l+r)>>1;
    if(p <= m) update(p, add, lson);
    else update(p, add, rson);
    push_up(rt);
}

int query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r)
    {
        return tree[rt];
    }
    int m = (l+r)>>1;
    int ret = 0;
    if(L <= m) ret += query(L, R, lson);
    if(R > m) ret += query(L, R, rson);
    return ret;
}

int main()
{
    int T; cin >> T;
    for(int asdasd = 1; asdasd <= T; asdasd++)
    {
        int n; cin >> n;
        cout << "Case " << asdasd << ":" << endl;
        build(1, n, 1);
        char op[10];
        int fir, sec;
        while(cin >> op)
        {
            if(op[0] == 'Q')
            {
                cin >> fir >> sec;
                cout << query(fir, sec, 1, n, 1) << endl;
            }
            else if(op[0] == 'A')
            {
                cin >> fir >> sec;
                update(fir, sec, 1, n, 1);
            }
            else if(op[0] == 'S')
            {
                cin >> fir >> sec;
                update(fir, -sec, 1, n, 1);
            }
            else break;
        }
    }
    //system("pause");
    return 0;
}
/* 
1
10
1 2 3 4 5 6 7 8 9 10
Query 1 3
Add 3 6
Query 2 7
Sub 10 2
Add 6 3
Query 3 10
End 
 */