#include <bits/stdc++.h>
using namespace std;
int main(){

    int t,cnt = 1;
    cin>>t;
    while(t--){
        int a,b;
        cin>>a>>b;
        if(b==1){
            if(a%2 == 1)
                printf("Case %d: first\n",cnt++);
            else
                printf("Case %d: second\n",cnt++);
        }
        else if(b>=a)
            printf("Case %d: first\n",cnt++);
        else
            printf("Case %d: second\n",cnt++);
            
    }
    return 0;
}

