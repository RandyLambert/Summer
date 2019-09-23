#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdio>

using namespace std;
long long n,a,da=-2100000000,aa;//这里定义。 
int b[200+10][200+10];//这里我们多定义100，以免数据溢出。 
int main()
{
cin>>n;
for(int i=1;i<=n;i++)
{
    for(int j=1;j<=n;j++)
    {
        scanf("%lld",&a);//我们这里用scanf读入，以免超时。 
        b[i][j]=a+b[i-1][j]+b[i][j-1]-b[i-1][j-1];//这个就是二维部分和的公式：a[前一行][j]+a[i][前一个格子]+这个格子的数-之前加上的重合部分。
    }
}
for(int i=1;i<=n;i++)
{
    for(int j=1;j<=n;j++)
    {
        for(int q=i;q<=n;q++)//注意初始值应等i。
        {
            for(int z=j;z<=n;z++)//注意初始值应等于j。 
            {
                aa=b[q][z]-b[q][j-1]-b[i-1][z]+b[i-1][j-1];//这里是我们求总和的公式。 
                if(aa>da)da=aa;//这里判断矩阵总和是否大于da。 
            }
        }
    }
}
cout<<da;
    return 0;
}
 

