#include <bits/stdc++.h>
using namespace std;
const int mod=2009;
struct MatrixType
{
    int n,ai[105][105];
    void mem(int n_)
    {
        n=n_;
        for(int i=0;i<=n;i++)
            for(int v=0;v<=n;v++)
                ai[i][v]=0;
    }
    MatrixType operator*(const MatrixType &pos)const
    {
        MatrixType res;res.mem(n);
        for(int i=0;i<=n;i++)
            for(int v=0;v<=n;v++)
                for(int k=0;k<=n;k++)
                    (res.ai[i][v]+=(ai[i][k]*pos.ai[k][v])%mod)%=mod;
        return res;
    }
};
struct MatrixType conMat;
int n,k,id[15][15],cnt;
char ch[105];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)
        for(int v=0;v<=8;v++)
            id[i][v]=cnt++;
    cnt--;
    conMat.mem(cnt);
    for(int i=0;i<n;i++)
    {
        for(int v=1;v<=8;v++) conMat.ai[id[i][v-1]][id[i][v]]=1;
        scanf("%s",ch);
        for(int v=0;v<n;v++)
        {
            int tmp=ch[v]-'0';
            if(tmp) conMat.ai[id[i][tmp-1]][id[v][0]]++;
        }
    }
    MatrixType pos=conMat;
    k--;
    while(k)
    {
        if(k&1) conMat=conMat*pos;
        k>>=1,pos=pos*pos;
    }
    cout<<conMat.ai[id[0][0]][id[n-1][0]];
    return 0;
}
