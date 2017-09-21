#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
  
using namespace std;
  
#define maxn 300005
  
struct TreeNodeType {
    int l, r, max, min, gcd, mid;
};
struct TreeNodeType tree[maxn << 2];
  
int n, m, ai[maxn], ty;
  
inline void in(int &now)
{
    char Cget = getchar(); now = 0;
    while (Cget > '9' || Cget < '0') Cget = getchar();
    while (Cget >= '0'&&Cget <= '9')
    {
        now = now * 10 + Cget - '0';
        Cget = getchar();
    }
}
  
int gcd(int a, int b)
{
    int tmp;
    while(b!=0) tmp=b,b=a%b,a=tmp;
    return a;
}
  
void tree_build(int now, int l, int r)
{
    tree[now].l = l, tree[now].r = r;
    if (l == r)
    {
        tree[now].gcd = ai[l] - ai[l - 1];
        tree[now].min = ai[l], tree[now].max = ai[l];
        return;
    }
    tree[now].mid = l + r >> 1;
    tree_build(now << 1, l, tree[now].mid);
    tree_build(now << 1 | 1, tree[now].mid + 1, r);
    tree[now].gcd = gcd(tree[now << 1].gcd, tree[now << 1 | 1].gcd);
    tree[now].max = max(tree[now << 1].max, tree[now << 1 | 1].max);
    tree[now].min = min(tree[now << 1].min, tree[now << 1 | 1].min);
}
  
void pre()
{
    in(n), in(m);
    for (int i = 1; i <= n; i++) in(ai[i]);
    tree_build(1, 1, n);
}
  
int tree_do(int now, int l, int r)
{
    if (tree[now].l == l&&tree[now].r == r)
    {
        if (ty == 1) return tree[now].max;
        if (ty == 2) return tree[now].min;
        if (ty == 3) return tree[now].gcd;
        tree[now].gcd = ai[l] - ai[l - 1];
        tree[now].max = ai[l], tree[now].min = ai[l];
        return 0;
    }
    int res=0;
    if (l > tree[now].mid) res = tree_do(now << 1 | 1, l, r);
    else if (r <= tree[now].mid) res = tree_do(now << 1, l, r);
    else
    {
        res = tree_do(now << 1, l, tree[now].mid);
        if (ty == 1) res = max(res, tree_do(now << 1 | 1, tree[now].mid + 1, r));
        if (ty == 2) res = min(res, tree_do(now << 1 | 1, tree[now].mid + 1, r));
        if (ty == 3) res = gcd(res, tree_do(now << 1 | 1, tree[now].mid + 1, r));
    }
    if (ty == 4)
    {
        tree[now].gcd = gcd(tree[now << 1].gcd, tree[now << 1 | 1].gcd);
        tree[now].max = max(tree[now << 1].max, tree[now << 1 | 1].max);
        tree[now].min = min(tree[now << 1].min, tree[now << 1 | 1].min);
    }
    return res;
}
  
void solve()
{
    int op, l, r, x, y, last = 0;
    for (int t = 1; t <= m; t++)
    {
        in(op);
        if (op == 1)
        {
            in(x), in(y);
            x^=last,y^=last,ty=4,ai[x]=y;
            tree_do(1,x,x);
            if(x!=n) tree_do(1,x+1,x+1);
        }
        else
        {
            in(l),in(r),in(x);
            l^=last,r^=last,x^=last;
            if(l==r)
            {
                last++;
                printf("Yes\n");
                continue;
            }
            int ma,mi,gcdd;
            ty=1,ma=tree_do(1,l,r);
            ty=2,mi=tree_do(1,l,r);
            ty=3,gcdd=tree_do(1,l+1,r);
            if((ma-mi)==x*(r-l)&&abs(gcdd)==x) printf("Yes\n"),last++;
            else printf("No\n");
        }
    }
}
  
int main()
{
    pre();
    solve();
    return 0;
}
