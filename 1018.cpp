#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxtree maxn<<2
#define cnm {printf("Y\n");continue;}
struct DataType
{
    bool ai[7],bi[7];
    void mem()
    {
        for(int i=1;i<=6;i++) ai[i]=bi[i]=false;
    }
    DataType operator+(const DataType pos)const
    {
        DataType res;res.mem();
        res.ai[1]|=ai[1],res.ai[2]|=ai[2],res.ai[3]|=ai[3];
        res.ai[4]|=pos.ai[4],res.ai[5]|=pos.ai[5],res.ai[6]|=pos.ai[6];
        res.bi[5]|=bi[5],res.bi[6]|=pos.bi[6];
        if(ai[6])
        {
            res.bi[1]|=bi[1]&&pos.bi[4];
            res.bi[2]|=bi[1]&&pos.bi[3];
            res.bi[3]|=bi[4]&&pos.bi[3];
            res.bi[4]|=bi[4]&&pos.bi[4];
        }
        if(ai[4])
        {
            res.bi[1]|=bi[2]&&pos.bi[1];
            res.bi[2]|=bi[2]&&pos.bi[2];
            res.bi[3]|=bi[3]&&pos.bi[2];
            res.bi[4]|=bi[3]&&pos.bi[1];
        }
        if(bi[2]&&bi[4]&&pos.bi[5]&&ai[4]&&ai[6]) res.bi[5]|=1;
        if(bi[6]&&pos.bi[2]&&pos.bi[4]&&ai[4]&&ai[6]) res.bi[6]|=1;
        //if(res.ai[2]&&res.bi[1]) res.bi[2]|=1;
        //if(res.ai[5]&&res.bi[3]) res.bi[4]|=1;
        return res;
    }
    void updata()
    {
        memset(bi,0,sizeof(bi));
        if(ai[5]||ai[2]) bi[1]=bi[3]=bi[5]=bi[6]=true;
        bi[2]=bi[4]=true;
    }
};
struct DataType val[maxtree];
int L[maxtree],R[maxtree],mid[maxtree],n;
void build(int now,int l,int r)
{
    L[now]=l,R[now]=r;if(l==r) return;mid[now]=l+r>>1;
    build(now<<1,l,mid[now]),build(now<<1|1,mid[now]+1,r);
}
void change(int now,int to,int x,bool di)
{
    if(L[now]==R[now])
    {
        val[now].ai[x]=di;
        if(x==2) val[now].ai[5]=di;
        val[now].updata();
        return;
    }
    if(to<=mid[now]) change(now<<1,to,x,di);
    else change(now<<1|1,to,x,di);
    val[now]=val[now<<1]+val[now<<1|1];
}
DataType query(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r) return val[now];
    DataType res;bool did=false;
    if(l<=mid[now]) res=query(now<<1,l,r),did=true;
    if(r>mid[now])
        if(did) res=res+query(now<<1|1,l,r);
        else res=query(now<<1|1,l,r);
    return res;
}
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),build(1,1,n);
    char op[10];int u1,u2,v1,v2;bool x;
    DataType l,r,m;
    while(1)
    {
        scanf("%s",op);
        if(op[0]=='E') break;
        in(v1),in(u1),in(v2),in(u2);
        if(op[0]=='O'||op[0]=='C')
        {
            x=(op[0]=='O');
            if(u1>u2) swap(u1,u2),swap(v1,v2);
            if(u1==u2) change(1,u1,2,x);
            else if(v1==1) change(1,u1,4,x),change(1,u2,1,x);
            else change(1,u1,6,x),change(1,u2,3,x);
        }
        else
        {
            if(u1>u2) swap(u1,u2),swap(v1,v2);
            m=query(1,u1,u2);
            if(v1==1&&v2==1&&m.bi[2])cnm
            if(v1==1&&v2==2&&m.bi[1])cnm
            if(v1==2&&v2==1&&m.bi[3])cnm
            if(v1==2&&v2==2&&m.bi[4])cnm
            l=query(1,1,u1),r=query(1,u2,n);
            if(v1==1&&v2==1)
            {
                if(m.bi[1]&&r.bi[5])cnm
                if(m.bi[3]&&l.bi[6])cnm
                if(m.bi[4]&&l.bi[6]&&r.bi[5])cnm
            }
            if(v1==1&&v2==2)
            {
                if(m.bi[2]&&r.bi[5])cnm
                if(m.bi[4]&&l.bi[6])cnm
                if(m.bi[3]&&l.bi[6]&&r.bi[5])cnm
            }
            if(v1==2&&v2==1)
            {
                if(m.bi[4]&&r.bi[5])cnm
                if(m.bi[2]&&l.bi[6])cnm
                if(m.bi[1]&&l.bi[6]&&r.bi[5])cnm
            }
            if(v1==2&&v2==2)
            {
                if(m.bi[1]&&l.bi[6])cnm
                if(m.bi[3]&&r.bi[5])cnm
                if(m.bi[2]&&l.bi[6]&&r.bi[5])cnm
            }
            printf("N\n");
        }
    }
    return 0;
}
