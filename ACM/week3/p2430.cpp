#include <bits/stdc++.h>
using namespace std;
int tim[5010],dp[5010];
struct node{
    int shi;
    int w;
}pp[5010];
int main(){
    
    int wky,wang,m,n,temp,zong;
    cin>>wky>>wang>>m>>n;
    wky = wang/wky;
    for(int i = 1;i <= n;i++){
        cin>>temp;
        tim[i] = temp*wky;
    }

    for(int i = 0;i < m;i++){
        int x;
        cin>>x>>pp[i].w;
        pp[i].shi = tim[x];
    }

    cin>>zong;

    for(int i = 0;i < m;i++){
        for(int j = zong;j >= pp[i].shi;j--){
            dp[j] = max(dp[j-pp[i].shi] + pp[i].w,dp[j]);
        }
    }

    printf("%d\n",dp[zong]);



    return 0;
}

