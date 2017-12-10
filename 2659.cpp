#include <iostream>  
#include <cstdio>  
#include <algorithm>  
#include <cmath>  
using namespace std;  
int main()  
{  
    long long p,q;  
    cin>>p>>q;  
    if (p==q) cout<<(p*p-1LL)/4LL<<endl;  
    else cout<<(p-1LL)*(q-1LL)/4LL<<endl;  
    return 0;  
}  
