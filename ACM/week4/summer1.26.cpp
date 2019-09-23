#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
int main(){
    long long int a,b;
    while(~scanf("%lld%lld",&a,&b)){
        if(a < b)
            swap(a,b);
        if(int((a-b)*((1.0+sqrt(5.0))/2.0)) == b)
            printf("0\n");
        else
            printf("1\n");
    }

    return 0;
}

