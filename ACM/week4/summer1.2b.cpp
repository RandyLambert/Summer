#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
 
int sum=0;
int next1[1000010];
char str1[1000010],str2[1000010];
 
void getNext(char *str,int next[])
{
    int k=strlen(str);
    next[0]=-1;
    int i=0,j=-1;
    while (i<k)
    {
        if (j==-1||str[i]==str[j])
        {
            i++;
            j++;
            next1[i]=j;
        }
        else
            j=next1[j];
    }

    for(int i = 0;i <= k;i++)
    {
        printf("%d ",next1[i]);
    }
}
 
void kmp(char *str1,char *str2)
{
    int k=strlen(str1);
    int k2=strlen(str2);
    getNext(str2,next1);
    int i=0,j=0;
    while (i<k)
    {
        if (j==-1||str1[i]==str2[j])
        {
            i++;
            j++;
            if (j==k2)
            {
                sum++;
                j=next1[j];
            }
        }
        else
            j=next1[j];
    }
 
}
 
int main()
{
    int n;
    scanf("%d",&n);
    while (n--)
    {
        sum=0;
        scanf("%s%s",str2,str1);
        kmp(str1,str2);
        printf("%d\n",sum);
    }
    return 0;
}

