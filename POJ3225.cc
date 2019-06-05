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

const int maxn = 131072;
int c[maxn<<2];
int x[maxn<<2];
bool vis[maxn];

void fxor(int rt)
{//cover 不为-1,那么XOR必为0
    if(c[rt] != -1) c[rt] ^= 1;//原本有异或信息但是这里已经被覆盖过了，那么无需异或了
    else x[rt] ^= 1;//区间异或
}

void push_down(int rt)
{
    if(c[rt] != -1)
    {
        c[rt<<1] = c[rt];//下放标记
        c[rt<<1|1] = c[rt];
        c[rt] = -1;//覆盖标记下放完毕
        x[rt<<1] = 0;//区间覆盖之后之前的异或信息就全部被清除了
        x[rt<<1|1] = 0;
    }
    if(x[rt])//如果这一段原本有异或信息
    {
        fxor(rt<<1);
        fxor(rt<<1|1);
        x[rt] = 0;//异或标记下放完毕
    }
}

void update(char op, int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r)
    {
        if(op == 'U')
            c[rt] = 1, x[rt] = 0;//区间覆盖为1
        else if(op == 'D')
            c[rt] = 0, x[rt] = 0;//区间覆盖为0
        else if(op == 'C' || op == 'S')
            fxor(rt);//区间异或
        return;
    }
    push_down(rt);
    int m = (l+r) >> 1;
    if(L <= m) update(op, L, R, lson);
    else if(op == 'I' || op == 'C') x[rt<<1] = c[rt<<1] = 0;//更新区间缩小到l r之内后，两边多出来的部分 顺便就将I与C的清零完成
    if(R > m) update(op, L, R, rson);
    else if(op == 'I' || op == 'C') x[rt<<1|1] = c[rt<<1|1] = 0;
}

void query(int l, int r, int rt)//递归标记
{
    if(c[rt] == 1)
    {
        for(int i = l; i <= r; i++)
            vis[i] = true;
        return;
    }
    else if(c[rt] == 0) return;
    if(l == r) return;
    int m = (l+r) >> 1;
    push_down(rt);
    query(lson);
    query(rson);
}

int main()
{
    c[1] = x[1] = 0;//取代memset，直接将线段树的根位置0即可
    char op, lef, rig;
    int a, b;
    while(~scanf("%c %c%d,%d%c\n", &op, &lef, &a, &b, &rig))
    {
        memset(vis, 0, sizeof(vis));
        a <<= 1;b <<= 1;//区间处理
        if(lef == '(') a++;
        if(rig == ')') b--;
        if(a > b)
        {
            if(op == 'I' || op == 'C')
                c[1] = x[1] = 0;
            continue;
        }
        update(op, a, b, 0, maxn, 1);
    }
    query(0, maxn, 1);
    int s = -1, e = 0;
    bool flag = false;
    for(int i = 0; i <= maxn; i++)
    {
        if(vis[i])//被成段标记为true区间的首尾查找
        {
            if(s == -1) s = i;
            e = i;
        }
        else if(s != -1)
        {
            if(flag) printf(" ");//空格处理
            flag = true;
            if(s&1) printf("(%d", (s>>1)); else printf("[%d", (s>>1)); //区间输出处理
            if(e&1) printf(",%d)", ((e+1)>>1)); else printf(",%d]", ((e+1)>>1));
            s = -1;
        }
    }
    if(!flag) printf("empty set");
    printf("\n");
    //system("pause");
    return 0;
}