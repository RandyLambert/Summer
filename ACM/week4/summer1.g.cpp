#include <iostream>
#include <algorithm>
using namespace std;
int a[1005];
int main(){
    int t,n;
    
    cin>>t;
    while(t--){
        cin>>n;
        for(int i = 0;i < n;i++){
            cin>>a[i];
        }
        sort(a,a+n);

        int sg = 0;
        if(n%2==0){
            for(int i = 0;i < n;i+=2){
                sg = sg ^ (a[i+1] - a[i] -1);
            }
        }
        else{
            sg = sg^(a[0] - 1);
            for(int i = 1;i < n;i+=2){

                sg = sg^(a[i+1] - a[i] - 1);
            }
        }
        if(sg == 0){
            cout<<"Bob will win"<<"\n";
        }
        else{
            cout<<"Georgia will win"<<"\n";
        }
    }

    return 0;
}

