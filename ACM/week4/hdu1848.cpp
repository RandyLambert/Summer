#include <bits/stdc++.h>
using namespace std;
int f[20],sgn[1010];
bool shi[1010];
void fb(){
    f[1] = 1,f[2] = 1;
    for(int i = 3;i < 20;i++){
        f[i] = f[i-1] + f[i-2];
    }
}
void sg(){
    memset(sgn,0,sizeof(sgn));

    for(int i = 1;i <= 1005;i++){
        memset(shi,0,sizeof(shi));
        for(int j = 1;j < 20 && f[j] <= i;j++){
            shi[sgn[i - f[j]]] = 1;
        }
        for(int k = 0;;k++){
            if(!shi[k]){
                sgn[i] = k;
                break;
            }
        }
    }
    
}
int main(){

    int a, b, c;
    fb();
    sg();


    /* for(int i = 0;i < 1000;i++) */
    /*     printf("%d ",sgn[i]); */
    while(cin>>a>>b>>c){
        if(a == 0 && b == 0 && c == 0){
            break;    
        }
        else{
            if(sgn[b]^sgn[a]^sgn[c])
                printf("Fibo\n");
            else
                printf("Nacci\n");
        }
    }


    return 0;
}

