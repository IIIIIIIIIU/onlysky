#include <cstdio>
#include <cstring>
using namespace std;
#define maxm 1005
#define maxn 1000005
int n,m,ch[maxm][26],val[maxn],tot=1,root=1,len;
bool f[maxn];
char str[maxn];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1),len=strlen(str+1);
        int to,now=root;
        for(int v=1;v<=len;v++)
        {
            to=str[v]-'a';
            if(!ch[now][to]) ch[now][to]=++tot;
            now=ch[now][to];
        }
        val[now]++;
    }
    int ans;
    for(int i=1;i<=m;i++)
    {
        ans=0;
        scanf("%s",str+1),len=strlen(str+1),f[0]=true;
        for(int v=1;v<=len;++v) f[v]=false;
        for(int v=1;v<=len;++v)
        {
            if(f[v-1])
            {
                int now=root,to;
                for(int e=v;e<=len;e++)
                {
                    to=str[e]-'a';
                    if(ch[now][to]) now=ch[now][to];
                    else break;
                    if(val[now]) f[e]=true;
                }
            }
            if(f[v]) ans=v;
        }
        printf("%d\n",ans);
    }
    return 0;
}
