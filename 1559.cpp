#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,m,tmpm,id[15],bit[15],root=1,ch[105][26],tot=1,len[15];
int que[105],tag[105],fail[105],anscnt,outag[105];
ll dp[26][105][1024],ans;
char str[15][15],*str2[15],out[105][105],pos[105];
bool del[15];
bool in(char *a,char *b)
{
    int lena=strlen(a+1),lenb=strlen(b+1);
    if(lenb>lena) return false;
    for(int i=1;i<=lena-lenb+1;i++)
    {
        bool can=true;
        for(int v=1;v<=lenb;v++)
            if(a[v+i-1]!=b[v])
            {
                can=false;
                break;
            }
        if(can) return true;
    }
    return false;
}
void dfs(int lenth,int s)
{
    if(lenth==n)
    {
        if(s==(1<<m)-1)
        {
            anscnt++;
            for(int i=1;i<=n;i++) out[anscnt][i]=pos[i];
//          puts(pos+1);
        }
        return;
    }
    for(int i=1;i<=m;i++)
    {
        for(int e=1;e<min(lenth,len[i]);e++)
        {
            bool can=false;
            for(int v=1;v<=e;v++)
                if(pos[lenth-e+v]!=str2[i][v])
                {
                    can=true;
                    break;
                }
            if(can||lenth+len[i]-e>n) continue;
            for(int v=e+1;v<=len[i];v++) pos[lenth+v-e]=str2[i][v];
            dfs(lenth+len[i]-e,s|bit[i]);
        }
        if(lenth+len[i]<=n)
        {
            for(int v=1;v<=len[i];v++) pos[lenth+v]=str2[i][v];
            dfs(lenth+len[i],s|bit[i]);
        }
    }
}
bool cmp(int a,int b)
{
    for(int i=1;i<=n;i++)
    {
        if(out[a][i]<out[b][i]) return true;
        if(out[a][i]>out[b][i]) return false;
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&m),tmpm=m;
    for(int i=1;i<=m;i++) scanf("%s",str[i]+1);
    for(int i=1;i<=m;i++)
        if(!del[i])
        {
            for(int v=i+1;v<=m;v++)
            {
                if(del[v]) continue;
                if(in(str[i],str[v])) del[v]=true,tmpm--;
                else if(in(str[v],str[i])) del[i]=true,tmpm--;
            }
        }
    bit[1]=1;
    for(int i=2;i<=tmpm;i++) bit[i]=bit[i-1]<<1;
    tmpm=0;
    for(int i=1;i<=m;i++)
    {
        if(del[i]) continue;
        str2[++tmpm]=str[i];
    }
    m=tmpm;
    for(int i=1;i<=m;i++)
    {
        int now=root;
        len[i]=strlen(str2[i]+1);
        for(int v=1;v<=len[i];v++)
        {
            int pos=str2[i][v]-'a';
            if(!ch[now][pos]) ch[now][pos]=++tot;
            now=ch[now][pos];
        }
        tag[now]=i;
    }
    int h=0,tail=1;
    que[h]=1;
    while(h<tail)
    {
        int now=que[h++],temp;
        for(int i=0;i<26;i++)
        {
            temp=fail[now];
            while(temp&&!ch[temp][i]) temp=fail[temp];
            if(!ch[now][i]) ch[now][i]=(temp?ch[temp][i]:root);
            else fail[ch[now][i]]=(temp?ch[temp][i]:root),que[tail++]=ch[now][i];
        }
    }
    dp[0][1][0]=1;
    for(int i=0;i<n;i++)
        for(int v=1;v<=tot;v++)
            for(int s=0;s<=(1<<m)-1;s++)
                if(dp[i][v][s])
                    for(int e=0;e<26;e++)
                        if(tag[ch[v][e]]) dp[i+1][ch[v][e]][s|bit[tag[ch[v][e]]]]+=dp[i][v][s];
                        else dp[i+1][ch[v][e]][s]+=dp[i][v][s];
    for(int i=1;i<=tot;i++)
        ans+=dp[n][i][(1<<m)-1];
    cout<<ans<<endl;
    if(ans<=42)
    {
        dfs(0,0);
        for(int i=1;i<=anscnt;i++) outag[i]=i;
        sort(outag+1,outag+anscnt+1,cmp);
        for(int i=1;i<=anscnt;i++) puts(out[outag[i]]+1);
    }
    return 0;
}
