#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
 
int n,jk,kl,ai,bi,hand[20],ans=0x7fffffff;
int t,c[10];
 
int A_star()
{
    memset(c,0,sizeof(c));
    int tot=0,kll=0;
    for(int i=1;i<=15;i++) c[hand[i]]++;//统计当前还剩的牌数 
    while(c[4]&&c[2]>1) c[4]--,c[2]-=2,tot++;//四带一对 
    while(c[4]&&c[1]>1) c[4]--,c[1]-=2,tot++;//四带两单 
    while(c[3]&&c[2]) c[3]--,c[2]--,tot++;//三带二 
    while(c[3]&&c[1]) c[3]--,c[1]--,tot++;//三带一
    for(int i=1;i<=9;i++) kll+=c[i];
    return tot+kll;//带牌+三张 对子 单张
}
 
void dfs(int x)
{
//    num=min(num,ans);
//    printf("%d %d  ",x,ans);
//    for(int i=1;i<=15;i++) printf("%d ",hand[i]);
//    printf("\n");
    if(x>=ans) return;
    int pd=0;
    int cur=0;
     
    for(int i=1;i<=13;i++)//40202
    {
        if(hand[i]>=4)
        {
            hand[i]-=4;
            for(int j=1;j<=13;j++)
            {
                if(j!=i&&hand[j]>=2)
                {
                    hand[j]-=2;
                    for(int v=1;v<=13;v++)
                    {
                        if(hand[v]>=2&&v!=j)
                        {
                            hand[v]-=2;
 //                           printf("1 ");
                            dfs(x+1);
                            hand[v]+=2;
                        }
                    }
                    hand[j]+=2;
                }
            }
            hand[i]+=4;
        }
    }
    for(int i=1;i<=13;i++)//402
    {
        if(hand[i]>=4)
        {
            hand[i]-=4;
            for(int j=1;j<=13;j++)
            {
                if(j!=i&&hand[j]>=1)
                {
                    hand[j]-=1;
                    for(int v=1;v<=13;v++)
                    {
                        if(hand[v]>=1&&v!=i)
                        {
                            hand[v]-=1;
 ///                           printf("2 ");
                            dfs(x+1);
                            hand[v]+=1;
                        }
                    }
                    hand[j]+=1;
                }
            }
            hand[i]+=4;
        }
    }
    for(int i=1;i<=11;i++)//3s
    {
         cur=0;
        if(hand[i]>=3&&i<=11){
            for(int j=i;j<=12;j++)
            {
                if(hand[j]>=3) cur++;
                else break;
            }
            for(int j=cur;j>=2;j--)
            {
                for(int v=i;v<=j+i-1;v++) hand[v]-=3;
    //            printf("3 ");
                dfs(x+1);
                for(int v=i;v<=j+i-1;v++) hand[v]+=3;
            }
        }
    }
    for(int i=1;i<=10;i++)//2s
    {
        cur=0;
        if(hand[i]>=2&&i<=10){
            for(int j=i;j<=12;j++)
            {
                if(hand[j]>=2) cur++;
                else break;
            }
            for(int j=cur;j>=3;j--)
            {
                for(int v=i;v<=j+i-1;v++) hand[v]-=2;
              //  printf("4 ");
                dfs(x+1);
                for(int v=i;v<=j+i-1;v++) hand[v]+=2;
            }
        }
    }
    for(int i=1;i<=8;i++)//1s
    {
        cur=0;
        if(hand[i]>=1&&i<=8){
            for(int j=i;j<=12;j++)
            {
                if(hand[j]>=1) cur++;
                else break;
            }
            for(int j=cur;j>=5;j--)
            {
                for(int v=i;v<=j+i-1;v++) hand[v]-=1;
            //    printf("5 ");
                dfs(x+1);
                for(int v=i;v<=j+i-1;v++) hand[v]+=1;
            }
        }
    }
    for(int i=1;i<=13;i++)
    {
        if(hand[i]>=3)
        {
            hand[i]-=3;
            for(int j=1;j<=13;j++)
            {
                if(j!=i&&hand[j]>=2)
                {
                    hand[j]-=2;
             //       printf("6 ");
                    dfs(x+1);
                    hand[j]+=2;
                }
            }
            hand[i]+=3;
        }
    }
    for(int i=1;i<=13;i++)
    {
        if(hand[i]>=3)
        {
            hand[i]-=3;
            for(int j=1;j<=15;j++)
            {
                if(j!=i&&hand[j]>=1)
                {
                    hand[j]-=1;
           //         printf("7 ");
                    dfs(x+1);
                    hand[j]+=1;
                }
            }
            hand[i]+=3;
        }
    }
    if(hand[14]>=1&&hand[15]>=1)
    {
        hand[14]--;
        hand[15]--;
      //  printf("8 ");
        dfs(x+1);
        hand[14]++;
        hand[15]++;
    }
    jk=A_star();
    if(x+jk>=ans) return;
    else ans=x+jk;
}
 
int main()
{
    scanf("%d%d",&t,&n);
    while(t--)
    {
        memset(hand,0,sizeof(hand));
        ans=0x7fffffff;
        for(int i=1;i<=n;i++)
        {
            cin>>ai>>bi;
            if(ai!=0)
            {
                if(ai>=3) hand[ai-2]++;
                else hand[11+ai]++;
            }
            else
            {
                if(bi==1) hand[14]++;
                else hand[15]++;
            }
        }
       // for(int i=1;i<=15;i++) printf("%d ",hand[i]);
    //    printf("\n");
        dfs(0);
        printf("%d\n",ans);
    }
    return 0;
}
