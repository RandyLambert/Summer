#include <bits/stdc++.h>
using namespace std;

struct node{
    int qi,zhong,w;
}a[1005];
int mp[105][105];
int main(){

    int c,s,n,xxx = 1;
    while(scanf("%d%d%d",&c,&s,&n)){
        if(c==0&&s==0&&n==0){
            break;
        }

        memset(a,0,sizeof(a));
        

        for(int i = 1;i <= c;i++){
            for(int j = 1;j <= c;j++){
                mp[i][j] = 999999999;
            }
        }
        for(int i = 0;i < s;i++){
            scanf("%d%d%d",&a[i].qi,&a[i].zhong,&a[i].w);
            
            mp[a[i].qi][a[i].zhong] = a[i].w;
            mp[a[i].zhong][a[i].qi] = a[i].w;
        }

        
        for(int i = 1;i <= c;i++){
            for(int j = 1;j <= c;j++){
                for(int k = 1;k <= c;k++){
                    if(mp[j][i]!=999999999&&mp[i][k]!=999999999)
                        mp[j][k] = min(mp[j][k],max(mp[j][i],mp[i][k])); 
                }
            }
        }
        int a1,b1;
        /* printf("Case #%d\n",xxx++); */
        cout<<"Case #"<<xxx++<<endl;
        for(int i = 0;i < n;i++){
            scanf("%d%d",&a1,&b1);
            if(mp[a1][b1] > 99999999){
                /* printf("no path\n"); */
                 cout<<"no path"<<endl;
            }
            else{
                /* printf("%d\n",mp[a1][b1]); */
                cout<<mp[a1][b1]<<endl;
            }
        }
    }
    return 0;
}

