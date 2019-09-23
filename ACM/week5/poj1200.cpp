#include<iostream>
#include<cstring>
using namespace std;
const int MaxNum = 20000000;
char ch[MaxNum];
bool lage[MaxNum];                                //用于标记是否为相同的子串
int hashArray[256];                                //存储n个字母转换成整数之后再转换成nc进制的数

int main() {
    int n, nc;
    while (cin >> n >> nc >> ch) {
        int k = 0;
        int len = strlen(ch);                    //注意此处
        for (int i = 0; i < len; i++) {
            if (hashArray[ch[i]] == 0) {
                hashArray[ch[i]] = k++;            //给nc个字母编号，如hashArray['a']=1
            }
        }


        /* for(int i = 0;i < 256;i++) */
        /*     printf("%d %d\n",i,hashArray[i]); */
        int ans = 0;                            //记录不同子串的种数
        for (int i = 0; i <= len - n; i++) {
            int sum = 0;
            for (int j = i; j < i + n; j++) {
                sum = sum * nc + hashArray[ch[j]];//将hashArray[]的nc进制数转换成一个十进制的整数sum
            }
            if (!lage[sum]) {                    //未出现过为false
                ans++;
                lage[sum] = true;                //出现过的为true
            }
        }
        cout << ans << endl;
    }
    return 0;
}
