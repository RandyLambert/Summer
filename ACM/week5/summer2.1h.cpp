#include <bits/stdc++.h>
using namespace std;

int n,c[50005];
int lowbit(int x){
    return x&(-x);
}

void add(int i,int value){
    while(i <= n){
        c[i] = value + c[i];
        i += lowbit(i);
    }
}

int sum(int i){
    int sum = 0;
    while(i > 0){
        sum = sum + c[i];
        i = i-lowbit(i);
    }
    return sum;
}
int main(){
    int t,Case = 0,d;
    
    cin>>t;
    while(t--){

        printf("Case %d:\n",++Case);
        scanf("%d",&n);

        memset(c,0,sizeof(c));

        for(int i = 1;i <= n;i++){
            scanf("%d",&d);
            add(i,d);
        }
        char command[15];
        int x,y;
        while(~scanf("%s",command)&&command[0]!='E'){
            scanf("%d%d",&x,&y);
            if(command[0] == 'Q')
                printf("%d\n",sum(y) - sum(x-1));
            else if(command[0] == 'A') add(x,y);
            else add(x,-y);
        }
    }
    return 0;
}
