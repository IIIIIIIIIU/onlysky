#include <bits/stdc++.h>
using namespace std;
int did[2000005],bit[17],ai[5][5],ans,que[2000005];
char ch[8];
int get()
{
    int res=0;
    for(int i=1,c=1;i<=4;i++)
        for(int v=1;v<=4;v++,c++)
            if(ai[i][v]) res+=bit[c];
    return res;
}
void back(int res)
{
    for(int i=1,c=1;i<=4;i++)
        for(int v=1;v<=4;v++,c++)
            ai[i][v]=((res&bit[c])==bit[c]);
}
int main()
{
    bit[1]=1;int a1=0,a2=0;
    for(int i=2;i<=16;i++) bit[i]=bit[i-1]<<1;
    for(int i=1,c=1;i<=4;i++)
    {
        scanf("%s",ch+1);
        for(int v=1;v<=4;v++,c++)
            if(ch[v]=='1') a1+=bit[c];
    }
    for(int i=1,c=1;i<=4;i++)
    {
        scanf("%s",ch+1);
        for(int v=1;v<=4;v++,c++)
            if(ch[v]=='1') a2+=bit[c];
    }
    if(a1==a2)
    {
        cout<<0;
        return 0;
    }
    did[a1]=1,did[a2]=-1;
    int h=0,tail=1,now,tmp;que[0]=a1;
    while(h<tail)
    {
        now=que[h++];
        back(now);
        for(int i=1;i<=4;i++)
            for(int v=1;v<=4;v++)
            {
                if(i<4&&ai[i][v]!=ai[i+1][v])
                {
                    swap(ai[i][v],ai[i+1][v]);
                    tmp=get();
                    if(did[tmp]==-1)
                    {
                        cout<<did[now];
                        return 0;
                    }
                    if(!did[tmp])
                    {
                        did[tmp]=did[now]+1;
                        que[tail++]=tmp;
                    }
                    swap(ai[i][v],ai[i+1][v]);
                }
                if(v<4&&ai[i][v]!=ai[i][v+1])
                {
                    swap(ai[i][v],ai[i][v+1]);
                    tmp=get();
                    if(did[tmp]==-1)
                    {
                        cout<<did[now];
                        return 0;
                    }
                    if(!did[tmp])
                    {
                        did[tmp]=did[now]+1;
                        que[tail++]=tmp;
                    }
                    swap(ai[i][v],ai[i][v+1]);
                }
            }
    }
    return 0;
}
