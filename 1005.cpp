#include <bits/stdc++.h>
using namespace std;
#define maxn 1005
#define maxlen 4000500
struct int666 {
    int len;
    char ai[maxlen];
    void mul(int pos)
    {
        long long cnt=0;
        for(int i=0;i<len;i++)
        {
            cnt+=pos*(ai[i]);
            ai[i]=cnt%10,cnt/=10;
        }
        while(cnt)
        {
            ai[len]=cnt%10;
            cnt/=10,len++;
        }
        while(len>1&&!ai[len-1]) len--;
    }
    void print()
    {
        for(int i=len-1;i>=0;i--) putchar(ai[i]+'0');
        putchar('\n');
    }
};
struct int666 ans;
int n,tot,ai[maxn],m,pi[maxn*10],num,bi[maxn*10];
bool if_p[maxn*10];
inline void in(int &now)
{
    int if_z=1;now=0;
    char Cget=getchar();
    while(Cget>'9'||Cget<'0')
    {
        if(Cget=='-')if_z=-1;
        Cget=getchar();
    }
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
}
void euler(int lit)
{
    for(int i=2;i<=lit;i++)
    {
        if(!if_p[i]) pi[++num]=i;
        for(int v=1;pi[v]*i<=lit&&v<=num;v++)
        {
            if_p[i*pi[v]]=true;
            if(i%pi[v]==0) break;
        }
    }
}
void apart(int now,int di)
{
    int temp=now;
    for(int v=1;v<=num;v++)
    {
        now=temp;
        while(now)
        {
            bi[v]+=di*now/pi[v];
            now/=pi[v];
        }
    }
}
int main()
{
//  freopen("bzoj_1005.in","r",stdin);
//  freopen("bzoj_1005.out","w",stdout);
    ans.len=1,ans.ai[0]=1;
    in(n),euler(maxn-1);
    if(n==1)
    {
        int pos;
        in(pos);
        if(pos<=0) printf("1");
        else printf("0");
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        in(ai[i]);
        if(!ai[i])
        {
            printf("0");
            return 0;
        }
        if(ai[i]==-1) m++;
        else tot+=--ai[i];
    }
    if(tot>n-2)
    {
        puts("0");
        return 0;
    }
    apart(n-2,1),apart(n-2-tot,-1);
    for(int i=1;i<=n;i++) if(ai[i]) apart(ai[i],-1);
    for(int i=1;i<=num;i++)
    {
        for(int v=1;v<=bi[i];v++) ans.mul(pi[i]);
    }
    for(int i=1;i<=n-2-tot;i++) ans.mul(m);
    ans.print();
    return 0;
}
