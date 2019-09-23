#include <iostream>
#include <string.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    char l[100000][5];
    while(n--){
        int a,b,c[100000],ans = 0,stat = 0;//stat状态    
        cin>>a>>b;
        a = a*100;
        memset(l,0,sizeof(l));
        for(int i = 0;i < b;i++){
            cin>>c[i]>>l[i];
        }
        int xx = 0;
        for(int i = 0;i < b;i++){
            if(l[i][0] == 'l' && stat == 0){
                if(xx + c[i] <= a){
                    xx = xx + c[i];
                }
                else{
                    xx = 0;
                    ans+=2;
                    i--;
                }
            }
            else if(l[i][0] == 'l' && stat == 1){
                ans++;
                stat = 0;
                xx = c[i];
            }
            else if(l[i][0] == 'r' && stat == 0){
                ans++;
                stat = 1;
                xx = c[i];
            }
            else if(l[i][0] == 'r' && stat == 1){
                if(xx + c[i] <= a){
                    xx = xx+c[i];
                }
                else{
                    xx = 0;
                    ans+=2;
                    i--;
                }
            }
        }
        printf("%d\n",ans+1);
    }

    return 0;
}

