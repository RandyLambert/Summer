#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline ll findhigh(ll x){
    ll ans = 0;
    while(x != 0){
        ans++;
        x = x>>1;
    }
    return ans;
} 
int main(){
    int n;
    cin>>n;
    while(n--){
        ll ans,a,b;
        cin>>a>>b;
        ll x = a^b;
        ll y = findhigh(x);
        ll xx = ((long long)(1)<<y)-1;
        ans = xx|b;
        cout<<ans<<"\n";
    }
    return 0;
}

