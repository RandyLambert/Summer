#include <bits/stdc++.h>
using namespace std;
int main(){

    char a[10] = {'1','2','3','4','5','6','7','8','9'};
    double bb;
    int ii[10] = {1,2,3,4,5,6,7,8,9,0};
    string b = "1 3 1 2 3 2 1";
    stringstream ss;
    ss<<ii[0];
    /* printf("%c\n",97); */
    /* cout<<a<<"dsa"<<endl; */
    while(ss>>bb)
        cout<<bb<<endl;
    
    return 0;
}

