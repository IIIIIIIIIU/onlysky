#include<bits/stdc++.h>
using namespace std;

#define N 100001
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define drp(i, a, b) for (int i = a; i >= b; i--)

int s[N], a[N], b[N], c[N];
int n, lena, lenb, lenc, sum1, sum2 = 2000000000, f[N], g[N];
vector<int> bur[15000000];

void getString(int* s, int& n) {
    int x = 0; char ch = getchar();
    for(; ch != '\n'; ch = getchar()) if(ch >= 'a' && ch <= 'z') x = x * 27 + ch - 'a' + 1; else if(x) s[++n] = x, x = 0;
    if(x) s[++n] = x;
}

int main() {
    getString(s, n), getString(a, lena), getString(b, lenb), getString(c, lenc);
    int l = 0, r = n + 1;
    rep(i, 1, lena) { l++; while(a[i] ^ s[l]) sum1++, l++; }
    drp(i, lenc, 1) { r--; while(c[i] ^ s[r]) sum1++, r--; }
    rep(i, 1, lenb) bur[b[i]].push_back(i); rep(i, 0, lenb) g[i] = sum2;
    l++, r--;
    rep(i, l, r) {
        int t = bur[s[i]].size() - 1, x;
        drp(j, t, 0) {
            x = bur[s[i]][j];
            if(!x) continue;
            if(x == 1) f[1] = i, g[1] = 0;
            else if(f[x - 1]) f[x] = i, g[x] = g[x - 1] + i - f[x - 1] - 1;
            sum2 = min(sum2, g[lenb]);
        }
    } 
    cout << sum1 + sum2;
    return 0;
}
