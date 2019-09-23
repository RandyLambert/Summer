#include <bits/stdc++.h>
using namespace std;
int main(){

    int n,m;
    while(scanf("%d%d",&n,&m)){
        if(m == 0&& n== 0)
            break;
        if(m%2==0 || n%2==0)
            printf("Wonderful!\n");
        else
            printf("What a pity!\n");

    }

    return 0;
}

