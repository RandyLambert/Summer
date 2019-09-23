#include <iostream>
#include<stack>
using namespace std;
typedef long long ll;
ll niu[80100],l[80100],ans;
int main(){
    int n;
    cin>>n;
    for(int i = 0;i < n;i++){
        cin>>niu[i];
    }
    stack<int>q;

    for(int i = 0;i < n;i++){
        while(q.size() && niu[q.top()] <= niu[i]) q.pop();
        /* if(q.empty()) l[i] = 0; */
        /* else l[i] = q.top() + 1; */
        ans += q.size();
        q.push(i);

    }

    cout<<ans<<"\n";

    return 0;
}

