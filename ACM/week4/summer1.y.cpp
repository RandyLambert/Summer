#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n;
    while(scanf("%lld",&n)&&n){
        long long a = 1,b = 1,flag = 0,temp;
        while(1){
            if(n > a){
                temp = b;
                b = a + b;
                a = temp;
            }
            else if(n == a){
                flag = 1;
                break;
            }
            else if(n < a)
                break;
        }

        if(flag == 0)
            printf("First win\n");
        else
            printf("Second win\n");
    }

    return 0;
}

