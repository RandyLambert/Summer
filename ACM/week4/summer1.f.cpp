
#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
ll n,k;
int main(){
	cin>>n>>k;
	ll remain=n;
	if(n==k)
        cout<<"YES";
	else if(n%k==0&&((n/k)%2==0))
        cout<<"NO";
	else if(n%k==0&&(n/k)%2!=0)
        cout<<"YES";
	else if (n%k!=0){	
		remain=n%k;
		if((n/k)%2==0)
            cout<<"NO";
		else
            cout<<"YES";
	}
	return 0;
}
