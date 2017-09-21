#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 20005
#define INF 0x7ffffff
 
int n,maxnlen=0,upx,upy,downx,downy;
int aix[maxn],aiy[maxn],maxlen,if_[maxn];
 
inline void in(int &now)
{
    int if_z=1;now=0;
    char Cget=getchar();
    while(Cget>'9'||Cget<'0')
    {
        if(Cget=='-') if_z=-1;
        Cget=getchar();
    }
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
}
 
bool thcheck(int len)
{
    int upx_=INF,upy_=-INF,downx_=-INF,downy_=INF;
    for(int i=1;i<=n;i++)
    {
        if(if_[i]==1||if_[i]==2) continue;
        if(aix[i]<upx_) upx_=aix[i];
        if(aiy[i]>upy_) upy_=aiy[i];
        if(aix[i]>downx_) downx_=aix[i];
        if(aiy[i]<downy_) downy_=aiy[i];
    }
    if(max(downx_-upx_,upy_-downy_)<=len) return true;
    else return false;
}
 
bool secheck(int len)
{
    int upx_=INF,upy_=-INF,downx_=-INF,downy_=INF;
    for(int i=1;i<=n;i++)
    {
        if(if_[i]==1) continue;
        if(aix[i]<upx_) upx_=aix[i];
        if(aiy[i]>upy_) upy_=aiy[i];
        if(aix[i]>downx_) downx_=aix[i];
        if(aiy[i]<downy_) downy_=aiy[i];
    }
    upx_=upx_+len,downx_=downx_-len,upy_=upy_-len,downy_=downy_+len;
    for(int i=1;i<=n;i++)
    {
        if(if_[i]==1) continue;
        if(aix[i]<=upx_&&aiy[i]>=upy_) if_[i]=2;
    }
    if(thcheck(len)) return true;
    for(int i=1;i<=n;i++)
    {
        if(if_[i]==1) continue;
        if(aix[i]<=upx_&&aiy[i]<=downy_) if_[i]=2;
        else if_[i]=0;
    }
    if(thcheck(len)) return true;
    for(int i=1;i<=n;i++)
    {
        if(if_[i]==1) continue;
        if(aix[i]>=downx_&&aiy[i]>=upy_) if_[i]=2;
        else if_[i]=0;
    }
    if(thcheck(len)) return true;
    for(int i=1;i<=n;i++)
    {
        if(if_[i]==1) continue;
        if(aix[i]>=downx_&&aiy[i]<=downy_) if_[i]=2;
        else if_[i]=0;
    }
    if(thcheck(len)) return true;
    else return false;
}
 
bool check(int len)
{
    for(int i=1;i<=n;i++) if_[i]=0;
    int upx_=upx+len,downx_=downx-len,upy_=upy-len,downy_=downy+len;
    for(int i=1;i<=n;i++) if(aix[i]<=upx_&&aiy[i]>=upy_) if_[i]=1;
    if(secheck(len)) return true;
    for(int i=1;i<=n;i++)
    {
        if(aix[i]<=upx_&&aiy[i]<=downy_) if_[i]=1;
        else if_[i]=0;
    }
    if(secheck(len)) return true;
    for(int i=1;i<=n;i++)
    {
        if(aix[i]>=downx_&&aiy[i]>=upy_) if_[i]=1;
        else if_[i]=0;
    }
    if(secheck(len)) return true;
    for(int i=1;i<=n;i++)
    {
        if(aix[i]>=downx_&&aiy[i]<=downy_) if_[i]=1;
        else if_[i]=0;
    }
    if(secheck(len)) return true;
    else return false;
}
 
int main()
{
    in(n);
    upx=INF,upy=-INF;
    downx=-INF,downy=INF;
    for(int i=1;i<=n;i++)
    {
        in(aix[i]),in(aiy[i]);
        if(aix[i]<upx) upx=aix[i];
        if(aiy[i]>upy) upy=aiy[i];
        if(aix[i]>downx) downx=aix[i];
        if(aiy[i]<downy) downy=aiy[i];
    }
    maxlen=max(upy-downy,downx-upx);
    int l=0,r=maxlen,ans=0x7fffffff;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;
    return 0;
}
