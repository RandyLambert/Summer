#include <stdio.h>
#include <iostream>
using namespace std;
int main(){
    int a,b;
    while(cin>>a>>b){
        if(a==0&&b==0)
            break;
        else{
            if(a < b)
                swap(a,b);
            int flag = 0;
            while(b){
            if(a/b >= 2 || a%b == 0)
                break;
            a = a-b;
            swap(a,b);
            if(flag == 0)
                flag = 1;
            else if(flag == 1)
                flag = 0;
            }

            if(flag == 0)
                printf("Stan wins\n");
            else
                printf("Ollie wins\n");
        }
    }

    return 0;
}

