#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
struct MatrixType
{
    int n;
    real ai[105][105];
    MatrixType operator*(const MatrixType &pos)const
    {
        MatrixType res;res.n=n;
        for(int i=1;i<=n;i++)
            for(int v=1;v<=n;v++)
            {
                res.ai[i][v]=0;
                for(int k=1;k<=n;k++) res.ai[i][v]+=ai[i][k]*ai[k][v];
            }
        return res;
    }
};
struct MatrixType mat1;
int ch[100001][10],tot=1,root=1,fail[100001],n,m,l;
int que[100001],tag[100001],post[1001];
real pi[15];
char str[10001];
int main()
{
    scanf("%d%d%d",&n,&l,&m);real x,y;
    for(int i=0;i<m;i++) scanf("%lf%lf",&x,&y),pi[i]=x/y;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        int now=root,pos;
        for(int v=1;v<=l;v++)
        {
            pos=str[v]-'A';
            if(!ch[now][pos]) ch[now][pos]=++tot;
            now=ch[now][pos];
        }
        tag[now]=i,post[i]=now;
    }
    int h=0,tail=1;que[0]=root;
    while(h<tail)
    {
        int now=que[h++];
        for(int i=0;i<m;i++)
            if(ch[now][i])
            {
                int temp=fail[now];
                while(temp&&!ch[temp][i]) temp=fail[temp];
                if(!temp) fail[ch[now][i]]=root;
                else fail[ch[now][i]]=ch[temp][i];
                que[tail++]=ch[now][i];
            }
    }
//  fail[root]=root;
    mat1.n=tot;
    for(int i=1;i<=tot;i++)
        if(tag[i]) mat1.ai[i][i]+=1;
        else for(int v=0;v<m;v++)
                if(ch[i][v]) mat1.ai[i][ch[i][v]]+=pi[v];
                else
                {
                    int temp=fail[i];
                    while(temp&&!ch[temp][v]) temp=fail[temp];
                    if(temp) mat1.ai[i][ch[temp][v]]+=pi[v];
                    else mat1.ai[i][root]+=pi[v];
                }
    for(int i=1;i<=50;i++)
        mat1=mat1*mat1;
    for(int i=1;i<=n;i++) printf("%.2lf\n",mat1.ai[1][post[i]]);
    return 0;
}
