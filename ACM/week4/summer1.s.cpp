#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    
    while(scanf("%d",&n)&&n){
        int ans = 0,xx;
        for(int i = 0;i < n;i++){
            scanf("%d",&xx);
            ans = ans^xx;
        }
        if(ans == 0)
            printf("Grass Win!\n");
        else
            printf("Rabbit Win!\n");

    }

    return 0;
}

