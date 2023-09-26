#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Plus(char *str1,char *str2);

void multiply(char *str1,char *str2);

int main()
{
    char op1[100];//��һ��������
    char op2[100];//�ڶ���������
    int i;
    srand(time(0));//�����������
    printf("1st\n");
    for(i=0;i<50;i++)
    {
        op1[i]=rand()%10+'0';
        printf("%c",op1[i]);
    }
    printf("\n2nd\n");
    for(i=0;i<50;i++)
    {
        op2[i]=rand()%10+'0';
        printf("%c",op2[i]);
    }

    Plus(op1,op2);

    multiply(op1,op2);

    return 0;
}


void Plus(char *str1,char *str2)
{
    int result[100]={0};
    for(int i=49;i>=0;i--)
    {
        result[49-i]=(result[49-i]+(str1[i]-'0')+(str2[i]-'0')%10)%10;
        result[49-i+1]=result[49-i+1]+((str1[i]-'0')+(str2[i]-'0'))/10;
    }
    printf("\n1\n");
    if (result[50]!=0)
    {
        printf("%d",result[50]);
    }
    for(int i=49;i>=0;i--)
    {
        printf("%d",result[i]);
    }
}

void multiply(char *str1,char *str2)
{
    int result[99]={0};
    int j=0;//����λ��
    int k=0;//�洢ָ��λ���ϵ�����
    for(j=49;j>=0;j--)//����λ��
    {
        for(int i=49;i>=0;i--)//������λ��
        {
            k=result[98-i-j];
            result[98-i-j]=(result[98-i-j]+(str1[i]-'0')*(str2[j]-'0'))%10;
            result[98-i-j+1]=(k+(str1[i]-'0')*(str2[j]-'0'))/10;
        }

    }
    printf("\nRESULT\n");
    if(result[99]!=0)
    {
        printf("%d",result[99]);
    }
    for (int i=98;i>=0;i--)
    {
        printf("%d",result[i]);
    }
}
