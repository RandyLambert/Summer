#include <bits/stdc++.h>
using namespace std;
long long int mod = 10000003;
int main(){
	int a,i = 0;
	unsigned long long ans = 1;
	scanf("%d",&a);
    if(a==0){
        printf("0\n");
        exit(0);
    }
	while(i < a-1){
		ans = (ans*2)%mod;
		i++;
	}
	ans = ans%mod;
	printf("%lld",ans);
	return 0;
}
