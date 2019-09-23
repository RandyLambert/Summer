#include <bits/stdc++.h>
using namespace std;
long long int a[100005],b[100005],dp[100005],dp1[100005];
int main(){
    int n;
    cin>>n;
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    for(int i = 1;i <= n;i++){
        cin>>b[i];
    }
    for(int i = 1;i <= n;i++){
        dp[i] = max(dp[i-1],dp1[i-1] + b[i]);
        dp1[i] = max(dp1[i-1],dp[i-1] + a[i]);
    }
    printf("%lld\n",max(dp[n],dp1[n]));
    return 0;
}
