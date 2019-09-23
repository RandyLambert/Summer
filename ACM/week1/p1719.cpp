#include <bits/stdc++.h>
using namespace std;
int dp[130+100][130+100],ans = -3123123,aa;
int main(){
    int n;
    cin>>n;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            scanf("%d",&dp[i][j]);
            dp[i][j] = dp[i][j] + dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            for(int q = i;q <= n;q++){
                for(int z = j;z <= n;z++){
                    aa = dp[q][z] - dp[q][j-1] - dp[i-1][z] + dp[i-1][j-1];

                    if(aa>ans) 
                        ans = aa;

                }
            }
        }
    }
        
    cout<<ans;

    return 0;
}

