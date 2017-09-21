#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100005;
int n,ai[maxn],d;
ll lu[maxn],ld[maxn],ru[maxn],rd[maxn],ans;
int main()
{
    scanf("%d%d",&n,&d);
    for(int i=1;i<=n;i++) scanf("%d",&ai[i]);
    for(int i=1;i<=n;i++)
        if(ai[i]==d)
        {
            int b=0,s=0;
            for(int v=i-1;v>=1;v--)
            {
                if(ai[v]>d) b++;
                else s++;
                if(b-s>=0) lu[b-s]++;
                else ld[s-b]++;
            }
            b=0,s=0;
            for(int v=i+1;v<=n;v++)
            {
                if(ai[v]>d) b++;
                else s++;
                if(b-s>=0) ru[b-s]++;
                else rd[s-b]++;
            }
            ans+=lu[0]+ru[0]+lu[0]*ru[0]+1;
            for(int i=1;i<=n;i++) ans+=lu[i]*rd[i]+ld[i]*ru[i];
            cout<<ans;break;
        }
    return 0;
}
