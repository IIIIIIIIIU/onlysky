#include <cstdio>
#include <cstring>
#include <algorithm>
using std::sort;
using std::strlen;
using std::next_permutation;
int main()
{
    char bi[12];
    int T,ai[12],d,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",bi+1),n=strlen(bi+1);
        scanf("%d",&d);
        for(int i=1;i<=n;i++) ai[i]=bi[i]-'0';
        sort(ai+1,ai+n+1);int ans=0;
        long long now=0;
        int i;
        for(i=1;i<=n;++i) now=now*10+ai[i];
        if(now%d==0) ans++;
        while(next_permutation(ai+1,ai+n+1))
        {
            now=0;
            for(i=1;i<=n;++i) now=now*10+ai[i];
            if(now%d==0) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
