#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define ll long long

const int N = 100005;
ll n,a[N],s[N],ans,ave,mid;

int main()
{
	cin>>n;
	ave=0;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		ave+=a[i];
	}
	ave/=n;
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+a[i]-ave;
	sort(s+1,s+n+1);
	ans=0;mid=s[(n+1)/2];
	for(int i=1;i<=n;i++)
		ans+=abs(s[i]-mid);
	cout<<ans<<endl;
	return 0;
}
