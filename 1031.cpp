#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 200005
const int hpos=251;
typedef unsigned long long ull;
int n,li[maxn],ri[maxn],ai[maxn];
ull num[maxn],Hash[maxn];
char ch[maxn];
inline bool cmp(int a,int b)
{
    int l=1,r=n>>1,mid,res=0;
    while(l<=r)
    {
        mid=l+r>>1;
        if((Hash[li[a]+mid-1]-Hash[li[a]-1]*num[mid])==(Hash[li[b]+mid-1]-Hash[li[b]-1]*num[mid]))
            res=mid,l=mid+1;
        else r=mid-1;
    }
    if(res==n) return false;
    return ch[li[a]+res]<ch[li[b]+res];
}
int main()
{
    scanf("%s",ch+1),n=strlen(ch+1);
    for(int i=1;i<=n;i++) ch[i+n]=ch[i],li[i]=i,ri[i]=i+n-1;
    n<<=1,num[0]=1;
    for(int i=1;i<=n;i++) num[i]=num[i-1]*hpos;
    for(int i=1;i<=n;i++) Hash[i]=Hash[i-1]*hpos+ch[i];
    for(int i=1;i<=(n>>1);i++) ai[i]=i;
    sort(ai+1,ai+(n>>1)+1,cmp);
    for(int i=1;i<=(n>>1);i++) putchar(ch[ri[ai[i]]]);
    return 0;
}
