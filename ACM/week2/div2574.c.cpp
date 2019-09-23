#include <bits/stdc++.h>
using namespace std;
int a1[1005],a2[1005],dp[1005],cci[1005];
int n,flag = 0;
int dfs(int j,int ci,int zhong){
    if(cci[j] == 1){
        return dp[j];
    }
    cci[j] = 1;
    dp[j] = -(1<<30); 
    if(ci == 0){
        for(int i = 1;j < n;i++){
            if(j >= a1[i])
                dp[j] = max(dp[j],dfs(n,1,i)+a1[j]);
        }
    }
    else if(ci == 1){
        for(int i = 1;j < n;i++){
            if(j >= a2[i])
                dp[j] = max(dp[j],dfs(n,0,i)+a2[j]);
        }
    }
    return dp[j];
}
int main(){
    long long mx = -999999999,ans = 0;
    scanf("%d",&n);

    for(int i = 1;i < n;i++)
        scanf("%d",&a1[i]);
    for(int i = 0;i < n;i++)
        scanf("%d",&a2[i]);

    for(int j = 0;j < n;j++){
        memset(dp,0,sizeof(dp));
        dp[j] = a1[j];
        ans = dfs(n,0,j);
        mx = max(mx,ans);
    }
    
    memset(cci,0,sizeof(cci));
    
    for(int j = 0;j < n;j++){
        memset(dp,0,sizeof(dp));
        dp[j] = a2[j];
        ans = dfs(n,1,j);
        mx = max(mx,ans);
    }
    
    printf("%lld\n",mx);



    return 0;
}

