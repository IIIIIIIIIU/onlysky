#include <bits/stdc++.h>
using namespace std;
#define mod 10007
int n,m,ch[60005][26],tot,root,fail[60050],que[60005];
int dp[105][60005],ans,get[60005][26];
char str[1000];
bool has[6005];
int main()
{
    root=tot=1,scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        int len=strlen(str+1),now=root;
        for(int v=1;v<=len;v++)
        {
            int to=str[v]-'A';
            if(!ch[now][to]) ch[now][to]=++tot;
            now=ch[now][to];
        }
        has[now]=true;
    }
    int h=0,tail=1;que[0]=root;
    for(int i=0;i<26;i++) ch[0][i]=1;
    while(h<tail)
    {
        int now=que[h++];
        for(int i=0;i<26;i++)
        {
            if(!ch[now][i]) continue;
            int to=fail[now];
            while(!ch[to][i]) to=fail[to];
            to=ch[to][i];
            if(has[to]) has[ch[now][i]]++;
            fail[ch[now][i]]=to;
            que[tail++]=ch[now][i];
        }
    }
    dp[0][1]=1;int now;
    for(int i=1;i<=tot;i++)
        for(int v=0;v<26;v++)
        {
            now=i;
            while(!ch[now][v]) now=fail[now];
            get[i][v]=ch[now][v];
        }
    for(int i=0;i<m;i++)
        for(int v=1;v<=tot;v++)
            if(dp[i][v]&&!has[v])
            {
                for(int e=0;e<26;e++)
                    dp[i+1][get[v][e]]=(dp[i+1][get[v][e]]+dp[i][v])%mod;
            }
    ans=1;
    for(int i=1;i<=m;i++) ans=(ans*26)%mod;
    for(int i=1;i<=tot;i++) if(!has[i]) ans=(ans-dp[m][i]+mod)%mod;
    ans=(ans+mod)%mod;
    cout<<ans;
    return 0;
}
