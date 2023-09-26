#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 60
#define INPUT_LIMIT 82
#define PI 3.14159265

//inner fucntions
_Bool safeInput(void);
_Bool analyseInput(void);
_Bool getRange(int *startopr, int *endopr, int *startnum, int *endnum);
void printHelp(void);
void calRange(void);


//inner variables
float number[MAX_LENGTH];
char operators[MAX_LENGTH];
char input[100];
int length1=0;
int length2=0;
int rangenum[2];
int rangeopr[2];
_Bool safe=0;

int main() {

    ca

    return 0;

}


//检验合法输入
_Bool safeInput(void){
    int n=0;
    unsigned long pos=0;
    unsigned long i=0;
    while(input[n]!='\n'){
        if(((input[n]<40)||(input[n]>57)||(input[n]==','))&&(input[n]!='^')){
            if(((input[n]=='s')||(input[n]=='c')||(input[n]=='t')||(input[n]=='S')
                ||(input[n]=='C')||(input[n]=='T'))&&(input[n+1]!='(')){
                printf("Function operators should followed by brackets!(s(x)/(c(x)...)\n");
                return 1;
            }
            if((input[n]!='s')&&(input[n]!='c')&&(input[n]!='t')&&(input[n]!='S')&&(input[n]!='C')
               &&(input[n]!='T')){
                printf("Detected unexpected character: %c\n",input[n]);
                return 1;
            }
        }
        n++;
    }
    n=0;
    /* In order to calculate the negative number, such as:
     -3 will be rewritten as (0-3). */
    while(input[n]!='\n'){
        if(input[n]=='-'){
            if(((input[n-1]>=40)&&(input[n-1]<=47)&&(input[n-1]!=')'))||(n==0)||(input[n-1]=='^')){
                for(i=strlen(input)+1;i>=n+2;i--)
                    input[i]=input[i-2];
                input[n]='(';
                input[n+1]='0';
                for(i=n+3;i<=strlen(input)+1;i++){
                    if((input[i]!='.')&&(input[i]<'0')){
                        pos=i;
                        break;
                    }
                }
                for(i=strlen(input)+1;i>=pos+1;i--)
                    input[i]=input[i-1];
                input[pos]=')';
            }
        }
        n++;
    }
    return 0;
}

_Bool analyseInput(void){
    /* This function can analyse the input string,
     and divide the string into two groups: number and operators.*/
    int m=0;
    int m2=0;
    int i=0;
    int n=0;
    int length=0;
    float multiple=0;
    while(input[n]!='\n'){
        // Analyse the characters, to check them whether they are operators.
        if(((input[n]>=40)&&(input[n]<=47)&&(input[n]!=','))||(input[n]=='^')
           ||(input[n]=='s')||(input[n]=='c')||(input[n]=='t')||(input[n]=='S')
           ||(input[n]=='C')||(input[n]=='T')){
            operators[m]=input[n];
            m++;
            length1++;
            if(m>=MAX_LENGTH)
                return 1;
            n++;
        }
        // Analyse the input string, pick out the numbers.
        if((input[n]>='0')&&(input[n]<='9')){
            length2++;
            multiple=1;
            while((input[n]>='0')&&(input[n]<='9')){
                //If number detected, then count the length of the number.
                length++;
                n++;
            }
            n-=length;
            //Here the contains will turn in to a float number, and stored in array 'number'.
            for(;length>0;length--){
                for(i=1;i<length;i++)
                    multiple*=10;
                number[m2]+=(input[n]-'0')*multiple;
                n++;
                multiple=1;
            }
            length=0;
            //Check whther there is a decimal, if there is, then add decimals to the number.
            if(input[n]=='.'){
                n++;
                multiple=0.1;
                while((input[n]>='0')&&(input[n]<='9')){
                    number[m2]+=(input[n]-'0')*multiple;
                    multiple*=0.1;
                    n++;
                }
            }
            m2++;
        }
    }
    return 0;
}

_Bool getRange(int *startopr, int *endopr, int *startnum, int *endnum){
    /* This function gets the range from ( to ), or head to bottom. */
    int index=0;
    int n=0;
    int function=0;
    _Bool brackets=0;
    /* Get the positions of brackets here, and we will calculate them first. */
    while(operators[index]!=')'){
        if(operators[index]=='('){
            *startopr=index;
            brackets=1;
        }
        if(index+1<length1)
            index++;
        else
            break;

    }
    *endopr=index;
    /* Accoring to an amazing phenomenon, we can get the position of numbers which
     are int the brackets like this: */
    for(index=0;index<=(*startopr);index++){
        if((operators[index]!='(')&&(operators[index]!='s')
           &&(operators[index]!='c')&&(operators[index]!='t')
           &&(operators[index]!='S')&&(operators[index]!='C')&&(operators[index]!='T'))
            n++;
    }
    for(index=(*startopr);index<=(*endopr);index++){
        if((operators[index]=='s')||(operators[index]=='c')||(operators[index]=='t')
           ||(operators[index]=='S')||(operators[index]=='C')||(operators[index]=='T'))
            function++;
    }
    *startnum=n;
    *endnum=(*startnum)+(*endopr)-(*startopr)-1-function;
    return brackets;
}

void calRange(void){
    /* This function is used to calculate the result of a certain range.*/
    int i=0;
    int j=0;
    int l1=rangeopr[1]-rangeopr[0]+1;
    int l2=rangenum[1]-rangenum[0]+1;
    char bufopr[l1];
    float bufnum[l2];
    /* First, copy the operators and the numbers according to the range. */
    for(i=rangenum[0];i<=rangenum[1];i++){
        bufnum[j]=number[i];
        j++;
    }
    j=0;
    for(i=rangeopr[0];(i<length1)&&(i<MAX_LENGTH);i++){
        if(i<=rangeopr[1]){
            bufopr[j]=operators[i];
            j++;
        }
        operators[i]=operators[i+l1];
        operators[i+l1]='\0';
    }
    /* Then, cross out the ( and ), and tidy the string. */
    if(bufopr[0]=='('){
        for(i=0;i<l1;i++){
            if(bufopr[i+1]!=')'){
                bufopr[i]=bufopr[i+1];
                bufopr[i+1]='\0';
            }
            else{
                bufopr[i]='\0';
                bufopr[i+1]='\0';
                break;
            }
        }
        l1-=2;
    }
    for(i=0;i<l1;i++){
        if((bufopr[i]=='s')||(bufopr[i]=='c')||(bufopr[i]=='t')||(bufopr[i]=='S')
           ||(bufopr[i]=='C')||(bufopr[i]=='T')){
            if(bufopr[i]=='s')
                number[rangenum[0]]=sin(bufnum[i]*PI/180);
            else if(bufopr[i]=='c')
                number[rangenum[0]]=cos(bufnum[i]*PI/180);
            else if(bufopr[i]=='t')
                number[rangenum[0]]=tan(bufnum[i]*PI/180);
            else if(bufopr[i]=='S')
                number[rangenum[0]]=(asin(bufnum[i]))*180/PI;
            else if(bufopr[i]=='C')
                number[rangenum[0]]=(acos(bufnum[i]))*180/PI;
            else if(bufopr[i]=='T')
                number[rangenum[0]]=(atan(bufnum[i]))*180/PI;
            bufnum[i]=number[rangenum[0]];
            for(j=i;j<l1;j++){
                if((j<l1)||(l1<=2)){
                    bufopr[j]=bufopr[j+1];
                    bufopr[j+1]='\0';
                }
            }
            i=-1;
        }
    }
    for(i=0;i<l1;i++){
        if(bufopr[i]=='^'){
            number[rangenum[0]]=pow(bufnum[i],bufnum[i+1]);
            bufnum[i]=number[rangenum[0]];
            for(j=i;j<l1;j++){
                if((j<l1)||(l1<=2)){
                    bufopr[j]=bufopr[j+1];
                    bufopr[j+1]='\0';
                }
            }
            for(j=i+1;j<l2;j++){
                if(j+1<l2){
                    bufnum[j]=bufnum[j+1];
                    bufnum[j+1]=0;
                }
            }
            i=-1;
        }
    }
    /* calculate, * and / first */
    for(i=0;i<l1;i++){
        if((bufopr[i]=='*')||(bufopr[i]=='/')){
            if(bufopr[i]=='*')
                number[rangenum[0]]=bufnum[i]*bufnum[i+1];
            else
                number[rangenum[0]]=bufnum[i]/bufnum[i+1];
            bufnum[i]=number[rangenum[0]];
            for(j=i;j<l1;j++){
                if((j<l1)||(l1<=2)){
                    bufopr[j]=bufopr[j+1];
                    bufopr[j+1]='\0';
                }
            }
            for(j=i+1;j<l2;j++){
                if(j+1<l2){
                    bufnum[j]=bufnum[j+1];
                    bufnum[j+1]=0;
                }
            }
            i=-1;
        }
    }
    /* After * and /, it's time for + and - */
    for(i=0;i<l1;i++){
        if((bufopr[i]=='+')||(bufopr[i]=='-')){
            if(bufopr[i]=='+')
                number[rangenum[0]]=bufnum[i]+bufnum[i+1];
            else
                number[rangenum[0]]=bufnum[i]-bufnum[i+1];
            bufnum[i]=number[rangenum[0]];
            for(j=i;j<l1;j++){
                if((j<l1)||(l1<=2)){
                    bufopr[j]=bufopr[j+1];
                    bufopr[j+1]='\0';
                }
            }
            for(j=i+1;j<l2;j++){
                if(j+1<l2){
                    bufnum[j]=bufnum[j+1];
                    bufnum[j+1]=0;
                }
            }
            i=-1;
        }
    }
    if(l2>1){
        /* copy the result back to number */
        for(i=rangenum[0]+1;(i<length2)&&(i<MAX_LENGTH);i++){
            number[i]=number[i+l2-1];
            number[i+l2-1]=0;
        }
        /* shorten the length */
        length1-=l1;
        length2-=l2-1;
    }
}

