#include <bits/stdc++.h>
using namespace std;
int mod;
struct MatrixType {
    int n,m,ai[40][40];
    void mem(int n_,int m_)
    {
        n=n_,m=m_;
        for(int i=0;i<=n;i++)
        {
            for(int v=0;v<=m;v++) ai[i][v]=0;
        }
    }
    MatrixType operator*(const MatrixType pos)const
    {
        MatrixType res;
        res.mem(n,pos.m);
        for(int i=0;i<=res.n;i++)
        {
            for(int k=0;k<=res.m;k++)
            {
                for(int v=0;v<=m;v++) res.ai[i][k]=(res.ai[i][k]+(ai[i][v]*pos.ai[v][k])%mod)%mod;
            }
        }
        return res;
    }
    void debug()
    {
        puts("");
        for(int i=0;i<=n;i++)
        {
            for(int v=0;v<=m;v++) printf("%d ",ai[i][v]);
            putchar('\n');
        }
        puts("");
    }
};
int n,m,ti[1001],Next[1001],last[1001],to[40][40];
void poww(MatrixType res,MatrixType pos,int mi)
{
    while(mi)
    {
        if(mi&1) res=res*pos;
        mi=mi>>1,pos=pos*pos;
    }
    long long ans=0;
    for(int i=0;i<m;i++) ans=(ans+res.ai[0][i])%mod;
    cout<<ans;
}
int main()
{
    scanf("%d%d%d",&n,&m,&mod);
    char ch[30];scanf("%s",ch+1);
    for(int i=1;i<=m;i++) ti[i]=ch[i]-'0';
    for(int i=1;i<m;i++)
    {
        int v=Next[i];
        while(v&&ti[i+1]!=ti[v+1]) v=Next[v];
        Next[i+1]=ti[i+1]==ti[v+1]?v+1:0;
    }
    for(int i=0;i<m;i++)
    {
        for(int v=0;v<=9;v++)
        {
            to[i][v]=ti[i+1]==v?i+1:to[Next[i]][v];
        }
    }
    MatrixType sta,tmp;
    sta.mem(0,m-1),sta.ai[0][0]=1;
    tmp.mem(m-1,m-1);
    for(int i=0;i<m;i++)
    {
        for(int v=0;v<=9;v++)
        {
            if(to[i][v]!=m) tmp.ai[i][to[i][v]]++;
        }
    }
    poww(sta,tmp,n);
    return 0;
}
