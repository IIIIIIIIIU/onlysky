#include <bits/stdc++.h>
using namespace std;
int n,ci[10],ans;
void dfs(int A,int B)
{
    if(A>1&&ci[A-1]) return;
    if(A==n)
    {
        for(int i=1;i<=n;++i)
            if(ci[i]) return;
        ans++;
        return;
    }
    if(ci[A]>(n-B+1)*3) return;
    if(ci[B]>(n-A+1)*3) return;
    if(ci[A]==0) for(int i=B;i<=n;i++) if(ci[B]<3) return;
//  for(int i=B;i<=n;i++) if(ci[i]>(n-A)*3) return;
    if(B==n)
    {
        if(ci[A]==1&&ci[B]>0) ci[A]--,ci[B]--,dfs(A+1,A+2),ci[A]++,ci[B]++;
        if(ci[A]==3) ci[A]-=3,dfs(A+1,A+2),ci[A]+=3;
        if(!ci[A]&&ci[B]>2) ci[B]-=3,dfs(A+1,A+2),ci[B]+=3;
        return;
    }
    if(ci[A]>0&&ci[B]>0) ci[A]--,ci[B]--,dfs(A,B+1),ci[A]++,ci[B]++;
    if(ci[A]>=3) ci[A]-=3,dfs(A,B+1),ci[A]+=3;
    if(ci[B]>=3) ci[B]-=3,dfs(A,B+1),ci[B]+=3;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&ci[i]);
    dfs(1,2);
    cout<<ans;
    return 0;
}
