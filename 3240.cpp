#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=1e9+7;
const int maxn=1e6+5;

ll a,b,c,d,lenn,lenm,n1,n2,m1,m2;

char n[maxn],m[maxn];

inline ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e%2==1)
			res=res*x%mod;
		e/=2;
		x=x*x%mod;
	}
	return res;
}

int main()
{
//	freopen("data3.txt","r",stdin);
//	freopen("matrixb.in","r",stdin);
//	freopen("matrixb.out","w",stdout);
	std::cin>>n+1>>m+1;
	lenn=strlen(n+1);
	lenm=strlen(m+1);
	for(int i=1;i<=lenn;i++)
	{
		n1=(n1*10+n[i]-'0')%(mod-1);
		n2=(n2*10+n[i]-'0')%mod;
	}
	for(int i=1;i<=lenm;i++)
	{
		m1=(m1*10+m[i]-'0')%(mod-1);
		m2=(m2*10+m[i]-'0')%mod;
	}
	std::cin>>a>>b>>c>>d;
	if(a!=1)
	{
		ll t=m1-1;
		ll t2=n1;
		ll am=poww(a,t);
		ll A=am*c%mod;
		ll B=(b*c%mod*(am-1)%mod*poww(a-1,mod-2)%mod+d)%mod;
		ll an=poww(A,t2);
		ll ans=(an+B*(an-1)%mod*poww(A-1,mod-2)%mod)%mod;
		ans=(ans-d)*poww(c,mod-2)%mod;
		std::cout<<(ans+mod)%mod<<std::endl;
	}
	else
	{
		ll t=m2-1;
		ll D=((c*t%mod*b%mod)+d)%mod;
		if(c==1)
		{
			ll ans=(1+(n2*D)%mod)%mod;
			ans=(ans+mod-d)*poww(c,mod-2)%mod;
			std::cout<<(ans+mod)%mod<<std::endl;
		}
		else
		{
			ll t2=poww(c,n1);
			ll ans=((t2+D*(t2-1)%mod*poww(c-1,mod-2))%mod+mod)%mod;
			ans=(ans+mod-d)*poww(c,mod-2)%mod;
			std::cout<<(ans+mod)%mod<<std::endl;
		}
	}
	return 0;
}
