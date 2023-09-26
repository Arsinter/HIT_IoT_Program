#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 600//大数的最大位数
char str[MAXSIZE];//储存需要转换的大数，以字符形式储存
//oldbase：原基数；newbase：新基数；len：大数的长度
int oldbase,newbase,len,k;
//a[MAXSIZE]；储存大数的最小整型，注意a[0]没有使用；r[MAXSIZE]：储存余数，即所求数的每一位
int a[MAXSIZE],r[MAXSIZE];
int GetNum(char c)//将字符转换成对应进制的整数
{
    if(c>='0'&&c<='9') return c-'0';
    if(c>='A'&&c<='Z' ) return c-'A'+10;
    return c-'a'+36;
}
char GetChar(int i)//将对应进制整数转换成对应的字符
{
    if(i>=0&&i<=9) return i+'0';
    if(i>=10&&i<=35) return i-10+'A';
    return i-36+'a';
}
void ChToNum()//调用函数将字符串转化成对应进制的整数，按位转化
{
    len=strlen(str);//测量字符串的长度
    //遍历每一个字符，一一对应转化，注意没有使用a[0]
    for(int i=1;i<=len;i++)
    {
        a[i]= GetNum(str[i-1]);
    }
}

void alter()//转化函数
{
    memset(r,0,sizeof(r));
    int m=1;
    k=0;
    while(m<=len)
    {
        int i,t = 0;
        //对数的每一位除新基数求商求余
        for(i=m;i<=len;i++)
        {
            t = t * oldbase + a[i];//计算除数
            a[i]=t / newbase;//求商
            t = t % newbase;//求余
        }
        r[k++]=t;//记录最后一个余数
        for(i=1;i<=len&&!a[i];i++);//去除前导0
        m=i;
    }
}

int main()
{
    printf("old base is:");
    scanf("%d",&oldbase);
    printf("new base is:");
    scanf("%d",&newbase);
    printf("num to trans:");
    scanf("%s",str);
    ChToNum();//字符转换为整型
    alter();//转化
    printf("Result is ");

    while(k--)//逆序输出余数，即是结果
    {
        printf("%c",GetChar(r[k]));
    }


    return 0;
}