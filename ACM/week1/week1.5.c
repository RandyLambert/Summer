#include <stdio.h>
int main(){
    int n,a,b;
    scanf("%d",&n);
    while(n--){
        scanf("%d%d",&a,&b);
        if(a%(b+1) == 0){
            printf("second\n");
        }
        else{
            printf("first\n");
        }
    }
    
    return 0;
}

