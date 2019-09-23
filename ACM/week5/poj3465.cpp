#include <stdio.h>
#include <queue>
#include<string.h>
#include<algorithm>
using namespace std;

int main(){
    int n,x,y,h1,h2;
    int t = 0,flag = 0,k;
    long long ans = -1,sum = 0;
    priority_queue<int>q;

    while(scanf("%d%d%d%d%d",&n,&x,&y,&h1,&h2)!=EOF){
        while(!q.empty()) q.pop();
        for(int i = 1;i <= n;i++){
            scanf("%d",&t);

            if(h1<=0 || h2 <=0)
                continue;
            h1 = h1 - t;
            h2 = h2 - x;
            sum = sum + x;
            ans = max(ans,sum);
            q.push(max(y,t));

            if(h2 <= 0){
                flag = i;
                continue;
            }

            while(h1<=0 && (!q.empty())){
                k = q.top();
                q.pop();
                sum = sum - x;
                h2 = h2 + x;
                h1 = h1 + k;
            }
        }
        if(flag){
            printf("Win\n");
            printf("%d\n",flag);
        }
        else{
            printf("Lose\n");
            printf("%lld\n",ans);
        }
    }
    return 0;
}
