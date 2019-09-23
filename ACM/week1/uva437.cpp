#include <bits/stdc++.h>
using namespace std;

struct node {
    int x,y,z;
}a[10000];
int dp[10000][10000];
int ans[10000];
int n;
bool cmp(struct node a,struct node b){
    return a.x*a.y < b.x*b.y;
}

int sove(int x){
    if(ans[x]) return ans[x];
    ans[x] = a[x].z;
    for(int i = 0;i < n*3;i++){
        if(dp[i][x]){
            ans[x] = max(ans[x],sove(i)+a[x].z);
        }
    }
    return ans[x];
}
int main(){
    int xxx = 1;
    while(cin>>n&&n!=0){
        memset(ans,0,sizeof(ans));
        memset(dp,0,sizeof(dp));
        memset(a,0,sizeof(a));
        
        for(int i = 0;i < n*3;i+=3)
        {
            scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
            a[i+1].y = a[i].x;
            a[i+1].x = a[i].z;
            a[i+1].z = a[i].y;
            a[i+2].y = a[i].z;
            a[i+2].x = a[i].y;
            a[i+2].z = a[i].x;
        }
        sort(a,a+n*3,cmp);

        for(int i = 0;i < n*3;i++){
            for(int j = i+1;j < n*3;j++){
                if((a[i].x < a[j].x&&a[i].y < a[j].y) || (a[i].y < a[j].x&&a[i].x < a[j].y)){
                    dp[i][j] = 1;
                }
            }
        }
        
        int cnt = 0;
        for(int i=0; i < n*3; i++)
        {
            int temp=sove(i);
            cnt=max(cnt,temp);
        }
        printf("Case %d: maximum height = %d\n",xxx,cnt);
        xxx++;
    }
    return 0;
}

