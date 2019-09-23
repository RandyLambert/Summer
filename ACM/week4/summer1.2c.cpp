#include <bits/stdc++.h>
using namespace std;
char a[100000+10];
int next1[100000+10];
void getnext(){
    int i = -1,j = 0;
    int alen = strlen(a);

    next1[0] = -1;
    while(j < alen){
        if(i == -1 || a[i] == a[j]){
            i++;
            j++;
            next1[j] = i;
        }
        else{
            i = next1[i];
        }
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){

        scanf("%s",a);
        getnext();
        int alen = strlen(a);
        /* int xx = alen%(alen - next1[alen]); */
        int length1 = alen - next1[alen];
        /* cout<<xx<<endl; */
        if(alen != length1 && alen % length1 == 0){
            /* cout<<0<<"\n"; */
            printf("0\n");
        }
        else{
            /* cout<<length1 - next1[alen]%length1<<"\n"; */
            printf("%d\n",length1 - next1[alen]%length1);
        }
    }

    return 0;
}

