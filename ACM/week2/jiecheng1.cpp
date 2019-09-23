#include<stdio.h>
#define MOD 100000//5位一存
#define max 8000
int main()
{
    int a[max];//10000!大概有10000*4=40000位,5位一存,数组大小需要开40000/5=8000的大小
    int n,i,j,bit,t;
    while(scanf("%d",&n)!=EOF)
    {
        bit=a[0]=1;
        t=0;
        for(i=2;i<=n;i++)
        {
            for(j=0;j<bit;j++)
            {
                t+=i*a[j];
                a[j]=t%MOD;
                t=t/MOD;
            }
            if(t>0)//一轮乘法过后，是否产生新的进位
            {
                a[bit++]=t;
                t=0;
            }
        }
        printf("%d",a[bit-1]);//首位不能为0，所以先输出<span style="font-family: Arial, Helvetica, sans-serif;">例如001编译器自动输出1</span>
 
        for(i=bit-2;i>=0;--i)
            printf("%05d",a[i]);//注意：5位一存输出格式05不能写成5
//输出占位符，就这题目来说，输出a[i]时，输出五位，右对齐，不足五位用0补位。例如a[i]=1时，输出00001。
        printf("\n");
    }
    return 0;
}
