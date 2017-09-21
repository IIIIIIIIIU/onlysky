#include <bits/stdc++.h>
using namespace std;
#define mod 45989
struct MatrixType {
    int n,m,ai[120][120];
    MatrixType(int n_,int m_)
    {
        n=n_,m=m_;
        for(int i=0;i<=n;i++)
        {
            for(int j=0;j<=m;j++)ai[i][j]=0;
        }
    }
    MatrixType operator*(const MatrixType pos)const
    {
        MatrixType res(n,pos.m);
        for(int i=0;i<=res.n;i++)
            for(int j=0;j<=res.m;j++)
                for(int v=0;v<=m;v++)
                    res.ai[i][j]=(res.ai[i][j]+ai[i][v]*pos.ai[v][j])%mod;
        return res;
    }
};
int n,m,t,a,b,cnt=-1,E[200],V[200],head[200];
bool ma[60][60];
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
MatrixType poww(MatrixType x,MatrixType y,int e)
{
    while(e)
    {
        if(e&1) x=x*y;
        y=y*y,e>>=1;
    }
    return x;
}
int main()
{
    memset(head,-1,sizeof(head));
    in(n),in(m),in(t),in(a),in(b);
    int u,v;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    MatrixType bi(cnt,cnt);
    for(int i=0;i<=cnt;i++)
    {
        for(int v=head[V[i]];v!=-1;v=E[v])
        {
            if(v!=(i^1)) bi.ai[i][v]++;
        }
    }
    MatrixType ai(0,cnt);
    for(int i=head[a];i!=-1;i=E[i]) ai.ai[0][i]++;
    MatrixType ans=poww(ai,bi,t-1);
    int ans_=0;
    for(int i=0;i<=ans.m;i++) if(V[i]==b)ans_=(ans_+ans.ai[0][i])%mod;
    printf("%d",ans_);
    return 0;
}
