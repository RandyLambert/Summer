#include <bits/stdc++.h>
using namespace std;
struct node{
    int a,b;
}aa[1005];
int c[1005];
bool cmp(node x,node y){
    return x.b > y.b;
}
int main(){
    int t,n;
    cin>>t;
    while(t--){
        int sum = 0;
        memset(aa,0,sizeof(aa));
        memset(c,0,sizeof(c));
        cin>>n;
        for(int i = 1;i <= n;i++)
            cin>>aa[i].a;
        for(int i = 1;i <= n;i++){
            cin>>aa[i].b;
            sum = sum + aa[i].b;
        }
        sort(aa+1,aa+n+1,cmp);
        for(int i = 1;i <= n;i++){
            int xx = aa[i].a;
            while(xx > 0){
                if(c[xx] < aa[i].b){
                    c[xx] = aa[i].b;
                    sum = sum - c[xx];
                    break;
                }
                else{
                    xx--;
                }
            }
        }
        cout<<sum<<"\n";
        
    }

    return 0;
}

