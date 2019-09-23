#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int x,flag = 0,ans = 0,y;
        cin>>x;
        for(int i = 0;i < x;i++){
            cin>>y;
            ans = ans^y;
            if(y > 1)
                flag = 1;
        }

        if(flag == 0)
            if(ans == 0)
                printf("%d\n",1);
            else
                printf("2\n");
        if(flag == 1)
            if(ans == 0)
                printf("2\n");
            else
                printf("1\n");
    }
    return 0;
}

