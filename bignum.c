#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignum.h"

// initial big number to n-bit integer, return -1 if fail to initialize
int32_t bigNumInit( BigNum *pNum, int32_t n )
{
    pNum->d=malloc(n*sizeof(int));
    if(pNum->d==NULL)return -1;
    pNum->b=malloc(4*n*sizeof(int));
    if(pNum->b==NULL)return -1;
    pNum->h=malloc(n*sizeof(int));
    if(pNum->h==NULL)return -1;
    pNum->sd=0;
    pNum->sb=0;
    pNum->sh=0;
    pNum->pos=1;
    pNum->space=n;
    return 0;
}

// free a big number
void bigNumFree( BigNum *pObj )
{
    free(pObj->d);
    pObj->sd=0;
    free(pObj->b);
    pObj->sb=0;
    free(pObj->h);
    pObj->sh=0;
    pObj->space=0;
    pObj->pos=0;
}

// 0 equal, -1 (obj1 less than obj2), 1 (obj1 bigger than obj2)
int32_t bigNumCmp( const BigNum *pObj1, const BigNum *pObj2 )
{
    if(pObj1->pos>pObj2->pos)return 1;
    if(pObj1->pos>0)
    {
        if(pObj1->sd>pObj2->sd)return 1;
        if(pObj1->sd<pObj2->sd)return -1;
        for(int i=0; i<pObj1->sd; i++)
        {
            if(pObj1->d[i]!=pObj2->d[i])
            {
                return (pObj1->d[i]>pObj2->d[i])?1:-1;
            }
        }
        return 0;
    }
    else
    {
        if(pObj1->sd>pObj2->sd)return -1;
        if(pObj1->sd<pObj2->sd)return 1;
        for(int i=0; i<pObj1->sd; i++)
        {
            if(pObj1->d[i]!=pObj2->d[i])
            {
                return (pObj1->d[i]>pObj2->d[i])?-1:1;
            }
        }
        return 0;
    }
}

// print big number decimal
void bigNumPrintDec( const BigNum *pObj )
{
    printf("Dec: ");
    if(pObj->sd>pObj->space)
    {
        printf("OVERFLOW\n");
        return;
    }
    if(pObj->pos<0)printf("-");
    for(int i=0; i<pObj->sd; i++)
    {
        printf("%d",pObj->d[i]);
    }
    printf("\n");
}

// print big number binary
void bigNumPrintBin( const BigNum *pObj )
{
    printf("Bin: ");
    if(pObj->sb>pObj->space*4)
    {
        printf("OVERFLOW\n");
        return;
    }
    if(pObj->pos<0)printf("-");
    for(int i=0; i<pObj->sb; i++)
    {
        printf("%d",pObj->b[i]);
    }
    printf("\n");
}

// print big number hex
void bigNumPrintHex( const BigNum *pObj )
{
    printf("Hex: ");
    if(pObj->sh>pObj->space)
    {
        printf("OVERFLOW\n");
        return;
    }
    if(pObj->pos<0)printf("-");
    for(int i=0; i<pObj->sh; i++)
    {
        switch(pObj->h[i])
        {
        case 0:
            printf("0");
            break;
        case 1:
            printf("1");
            break;
        case 2:
            printf("2");
            break;
        case 3:
            printf("3");
            break;
        case 4:
            printf("4");
            break;
        case 5:
            printf("5");
            break;
        case 6:
            printf("6");
            break;
        case 7:
            printf("7");
            break;
        case 8:
            printf("8");
            break;
        case 9:
            printf("9");
            break;
        case 10:
            printf("A");
            break;
        case 11:
            printf("B");
            break;
        case 12:
            printf("C");
            break;
        case 13:
            printf("D");
            break;
        case 14:
            printf("E");
            break;
        case 15:
            printf("F");
            break;
        }
    }
    printf("\n");
}

// set big number by decimal string, return -1 if fail or invalid
int32_t bigNumSetDec( BigNum *pObj, const char *decimal )
{
    if(strlen(decimal)>pObj->space)return -1;
    int i=0;
    for(i=0; i<strlen(decimal); i++)
    {
        switch(decimal[i])
        {
        case '0':
            pObj->d[i]=0;
            break;
        case '1':
            pObj->d[i]=1;
            break;
        case '2':
            pObj->d[i]=2;
            break;
        case '3':
            pObj->d[i]=3;
            break;
        case '4':
            pObj->d[i]=4;
            break;
        case '5':
            pObj->d[i]=5;
            break;
        case '6':
            pObj->d[i]=6;
            break;
        case '7':
            pObj->d[i]=7;
            break;
        case '8':
            pObj->d[i]=8;
            break;
        case '9':
            pObj->d[i]=9;
            break;
        case '-':
            pObj->pos=-1;
            break;
        default:
            return -1;
        }
    }
    pObj->sd=i;
    updbd(pObj);
}

// set big number by binary string, return -1 if fail or invalid
int32_t bigNumSetBin( BigNum *pObj, const char *binary )
{
    if(strlen(binary)>pObj->space*4)return -1;
    int i=0;
    for(i=0; i<strlen(binary); i++)
    {
        switch(binary[i])
        {
        case '0':
            pObj->b[i]=0;
            break;
        case '1':
            pObj->b[i]=1;
            break;
        case '-':
            pObj->pos=-1;
            break;
        default:
            return -1;
        }
    }
    pObj->sb=i;
    updbb(pObj);
}

// set big number by hex string, return -1 if fail or invalid
int32_t bigNumSetHex( BigNum *pObj, const char *hex )
{
    if(strlen(hex)>pObj->space)return -1;
    int i=0;
    for(i=0; i<strlen(hex); i++)
    {
        switch(hex[i])
        {
        case '0':
            pObj->h[i]=0;
            break;
        case '1':
            pObj->h[i]=1;
            break;
        case '2':
            pObj->h[i]=2;
            break;
        case '3':
            pObj->h[i]=3;
            break;
        case '4':
            pObj->h[i]=4;
            break;
        case '5':
            pObj->h[i]=5;
            break;
        case '6':
            pObj->h[i]=6;
            break;
        case '7':
            pObj->h[i]=7;
            break;
        case '8':
            pObj->h[i]=8;
            break;
        case '9':
            pObj->h[i]=9;
            break;
        case 'A':
        case 'a':
            pObj->h[i]=10;
            break;
        case 'B':
        case 'b':
            pObj->h[i]=11;
            break;
        case 'C':
        case 'c':
            pObj->h[i]=12;
            break;
        case 'D':
        case 'd':
            pObj->h[i]=13;
            break;
        case 'E':
        case 'e':
            pObj->h[i]=14;
            break;
        case 'F':
        case 'f':
            pObj->h[i]=15;
            break;
        case '-':
            pObj->pos=-1;
            break;
        default:
            return -1;
        }
    }
    pObj->sh=i;
    updbh(pObj);
}

// obj1 add obj2, return -1 if fail
int32_t bigNumAdd( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 )
{
    bigNumInit(pAns,(pObj1->space>=pObj2->space)?pObj1->space+1:pObj2->space+1);
    int t1[pObj1->sd];
    int t2[pObj2->sd];
    for(int i=0; i<pObj1->sd; i++)t1[i]=pObj1->d[pObj1->sd-i-1]; //rev
    for(int i=0; i<pObj2->sd; i++)t2[i]=pObj2->d[pObj2->sd-i-1]; //rev
    for(int i=0; i<pAns->space; i++)pAns->d[i]=0; //ini
    if(pObj1->pos==pObj2->pos) //same sign
    {
        int tc=(pObj1->sd>pObj2->sd)?pObj1->sd:pObj2->sd;
        for(int i=0; i<tc; i++)
        {
            if(i<pObj1->sd)pAns->d[i]+=t1[i];
            if(i<pObj2->sd)pAns->d[i]+=t2[i];
        }
        int c=0;//carry
        for(int i=0; i<tc+1; i++)
        {
            pAns->d[i]+=c;
            if(pAns->d[i]>=10)
            {
                c=pAns->d[i]/10;
                pAns->d[i]%=10;
            }
            else
            {
                c=0;
            }
        }
        pAns->sd=0;
        for(int i=pAns->space-1; i>=0; i--)
        {
            if(pAns->d[i]!=0)
            {
                pAns->sd=i+1;
                break;
            }
        }
        for(int i=0; i<(pAns->sd)/2; i++) //reverse
        {
            int t=pAns->d[i];
            pAns->d[i]=pAns->d[pAns->sd-i-1];
            pAns->d[pAns->sd-i-1]=t;
        }
        pAns->pos=pObj1->pos;
        updbd(pAns);
    }
    else //diff sign
    {
        if(pObj1->sd>pObj2->sd) //p1 longer
        {
            int tc=(pObj1->sd>pObj2->sd)?pObj1->sd:pObj2->sd;
            for(int i=0; i<tc; i++)
            {
                if(i<pObj1->sd)pAns->d[i]+=t1[i];
                if(i<pObj2->sd)pAns->d[i]-=t2[i];
            }
            int c=0;//carry
            for(int i=0; i<tc+1; i++)
            {
                pAns->d[i]+=c;
                if(pAns->d[i]>=10)
                {
                    c=pAns->d[i]/10;
                    pAns->d[i]%=10;
                }
                else if(pAns->d[i]<0)
                {
                    pAns->d[i]+=10;
                    c=-1;
                }
                else
                {
                    c=0;
                }
            }
            pAns->sd=0;
            for(int i=pAns->space-1; i>=0; i--)
            {
                if(pAns->d[i]!=0)
                {
                    pAns->sd=i+1;
                    break;
                }
            }
            for(int i=0; i<(pAns->sd)/2; i++) //reverse
            {
                int t=pAns->d[i];
                pAns->d[i]=pAns->d[pAns->sd-i-1];
                pAns->d[pAns->sd-i-1]=t;
            }
            pAns->pos=pObj1->pos;
            updbd(pAns);
        }
        else if(pObj2->sd>pObj1->sd) //p2 longer
        {
            int tc=(pObj1->sd>pObj2->sd)?pObj1->sd:pObj2->sd;
            for(int i=0; i<tc; i++)
            {
                if(i<pObj1->sd)pAns->d[i]-=t1[i];
                if(i<pObj2->sd)pAns->d[i]+=t2[i];
            }
            int c=0;//carry
            for(int i=0; i<tc+1; i++)
            {
                pAns->d[i]+=c;
                if(pAns->d[i]>=10)
                {
                    c=pAns->d[i]/10;
                    pAns->d[i]%=10;
                }
                else if(pAns->d[i]<0)
                {
                    pAns->d[i]+=10;
                    c=-1;
                }
                else
                {
                    c=0;
                }
            }
            pAns->sd=0;
            for(int i=pAns->space-1; i>=0; i--)
            {
                if(pAns->d[i]!=0)
                {
                    pAns->sd=i+1;
                    break;
                }
            }
            for(int i=0; i<(pAns->sd)/2; i++) //reverse
            {
                int t=pAns->d[i];
                pAns->d[i]=pAns->d[pAns->sd-i-1];
                pAns->d[pAns->sd-i-1]=t;
            }
            pAns->pos=pObj2->pos;
            updbd(pAns);
        }
        else //same digits
        {
            int p1orp2=0;//p1>p2:1 p1<p2:-1 p1==p2:0
            for(int i=pObj1->sd-1; i>=0; i--)
            {
                if(pObj1->d[i]!=pObj2->d[i])
                {
                    if(pObj1->d[i]>pObj2->d[i])
                    {
                        p1orp2=1;
                    }
                    else
                    {
                        p1orp2=-1;
                    }
                    break;
                }
            }
            if(p1orp2>=0)
            {
                int tc=(pObj1->sd>pObj2->sd)?pObj1->sd:pObj2->sd;
                for(int i=0; i<tc; i++)
                {
                    if(i<pObj1->sd)pAns->d[i]+=t1[i];
                    if(i<pObj2->sd)pAns->d[i]-=t2[i];
                }
                int c=0;//carry
                for(int i=0; i<tc+1; i++)
                {
                    pAns->d[i]+=c;
                    if(pAns->d[i]>=10)
                    {
                        c=pAns->d[i]/10;
                        pAns->d[i]%=10;
                    }
                    else if(pAns->d[i]<0)
                    {
                        pAns->d[i]+=10;
                        c=-1;
                    }
                    else
                    {
                        c=0;
                    }
                }
                pAns->sd=0;
                for(int i=pAns->space-1; i>=0; i--)
                {
                    if(pAns->d[i]!=0)
                    {
                        pAns->sd=i+1;
                        break;
                    }
                }
                for(int i=0; i<(pAns->sd)/2; i++) //reverse
                {
                    int t=pAns->d[i];
                    pAns->d[i]=pAns->d[pAns->sd-i-1];
                    pAns->d[pAns->sd-i-1]=t;
                }
                pAns->pos=pObj1->pos;
                updbd(pAns);
            }
            else
            {
                int tc=(pObj1->sd>pObj2->sd)?pObj1->sd:pObj2->sd;
                for(int i=0; i<tc; i++)
                {
                    if(i<pObj1->sd)pAns->d[i]-=t1[i];
                    if(i<pObj2->sd)pAns->d[i]+=t2[i];
                }
                int c=0;//carry
                for(int i=0; i<tc+1; i++)
                {
                    pAns->d[i]+=c;
                    if(pAns->d[i]>=10)
                    {
                        c=pAns->d[i]/10;
                        pAns->d[i]%=10;
                    }
                    else if(pAns->d[i]<0)
                    {
                        pAns->d[i]+=10;
                        c=-1;
                    }
                    else
                    {
                        c=0;
                    }
                }
                pAns->sd=0;
                for(int i=pAns->space-1; i>=0; i--)
                {
                    if(pAns->d[i]!=0)
                    {
                        pAns->sd=i+1;
                        break;
                    }
                }
                for(int i=0; i<(pAns->sd)/2; i++) //reverse
                {
                    int t=pAns->d[i];
                    pAns->d[i]=pAns->d[pAns->sd-i-1];
                    pAns->d[pAns->sd-i-1]=t;
                }
                pAns->pos=pObj2->pos;
                updbd(pAns);
            }
        }
    }
}

// obj1 substract obj2, return -1 if fail
int32_t bigNumSub( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 )
{
    BigNum pt;
    bigNumInit(&pt,pObj2->space);
    pt.sd=pObj2->sd;
    for(int i=0; i<pt.sd; i++)pt.d[i]=pObj2->d[i];
    pt.pos=-pObj2->pos;
    bigNumAdd(pAns,pObj1,&pt);
    bigNumFree(&pt);
}

// obj1 multiply obj2, return -1 if fail
int32_t bigNumMul( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 )
{
    bigNumInit(pAns,pObj1->sd+pObj2->sd);
    pAns->pos=pObj1->pos*pObj2->pos;
    int t1[pObj1->sd];
    int t2[pObj2->sd];
    for(int i=0; i<pObj1->sd; i++)t1[i]=pObj1->d[pObj1->sd-i-1]; //rev
    for(int i=0; i<pObj2->sd; i++)t2[i]=pObj2->d[pObj2->sd-i-1]; //rev
    for(int i=0; i<pAns->space; i++)pAns->d[i]=0; //ini
    for(int i=0; i<pObj1->sd; i++)
    {
        for(int j=0; j<pObj2->sd; j++)
        {
            pAns->d[i+j]+=t1[i]*t2[j];
        }
    }
    int c=0;//carry
    for(int i=0; i<pAns->space; i++)
    {
        pAns->d[i]+=c;
        if(pAns->d[i]>=10)
        {
            c=pAns->d[i]/10;
            pAns->d[i]%=10;
        }
        else
        {
            c=0;
        }
    }
    pAns->sd=0;
    for(int i=pAns->space-1; i>=0; i--)
    {
        if(pAns->d[i]!=0)
        {
            pAns->sd=i+1;
            break;
        }
    }
    for(int i=0; i<(pAns->sd)/2; i++) //reverse
    {
        int t=pAns->d[i];
        pAns->d[i]=pAns->d[pAns->sd-i-1];
        pAns->d[pAns->sd-i-1]=t;
    }
    updbd(pAns);
}

// obj1 divide obj2, return -1 if fail
int32_t bigNumDiv( BigNum *pQuotient, BigNum *pRemainder, const BigNum *pObj1, const BigNum *pObj2 )
{
    bigNumInit(pQuotient,pObj1->sd);
    bigNumInit(pRemainder,pObj1->sd);
    int t1[pObj1->sd],t2[pObj2->sd],q[pObj1->sd];
    int t1n=pObj1->sd,t2n=pObj2->sd;

    for(int i=0; i<t1n; i++)
    {
        t1[i]=pObj1->d[i];
        q[i]=0;
    }
    int sq=0,sr=0;//size of pQuo pRem
    for(int i=0; i<t2n; i++)t2[i]=pObj2->d[i];

    for(int i=0; i+t2n<=t1n; i++)
    {
        sq++;
        int lteq=0;
        for(int j=0; j<i; j++)lteq+=t1[j];
        while(t1[i]>t2[0]||lteq>0)
        {
            q[i]++;
            for(int j=0; j<t2n; j++)
            {
                t1[i+j]-=t2[j];
            }
            int c=0;//carry
            for(int j=t1n-1; j>=0; j--)
            {
                t1[j]+=c;
                if(t1[j]<0)
                {
                    t1[j]+=10;
                    c=-1;
                }
                else
                {
                    c=0;
                }
            }
            lteq=0;
            for(int j=0; j<i; j++)lteq+=t1[j];
        }
        if(t1[i]==t2[0])
        {
            int chek=1;
            for(int j=0; j<t2n; j++)
            {
                if(t1[i+j]<t2[j])
                {
                    chek=0;
                    break;
                }
                if(t1[i+j]>t2[j])
                {
                    break;
                }
            }
            if(chek==1)
            {
                q[i]++;
                for(int j=0; j<t2n; j++)
                {
                    t1[i+j]-=t2[j];
                }
                int c=0;//carry
                for(int j=t1n-1; j>=0; j--)
                {
                    t1[j]+=c;
                    if(t1[j]<0)
                    {
                        t1[j]+=10;
                        c=-1;
                    }
                    else
                    {
                        c=0;
                    }
                }
            }
        }
    }
    for(int i=0; i<t1n; i++)
    {
        if(t1[i]!=0)
        {
            sr=i;
            break;
        }
    }
    for(int i=sr; i<t1n; i++)
    {
        pRemainder->d[i-sr]=t1[i];
    }
    pRemainder->sd=t1n-sr;
    if(sr==0)
    {
        int chekifzr=0;
        for(int i=0; i<pRemainder->sd; i++)chekifzr+=pRemainder->d[i];
        if(chekifzr==0)pRemainder->sd=1;
    }

    sr=0;

    for(int i=0; i<t1n; i++)
    {
        if(q[i]!=0)
        {
            sr=i;
            break;
        }
    }
    for(int i=sr; i<sq; i++)
    {
        pQuotient->d[i-sr]=q[i];
    }
    pQuotient->sd=sq-sr;

    if(pObj1->pos!=pObj2->pos)
    {
        pRemainder->pos=-1;
    }
    updbd(pQuotient);
    updbd(pRemainder);
}

// obj1 to the power obj2, return -1 if fail
int32_t bigNumPow( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 )
{
    if(pObj2->pos<0)return -1;
    bigNumInit(pAns,1);
    bigNumSetDec(pAns,"1");
    BigNum t,tans,t1;
    bigNumInit(&t,pObj1->space);
    bigNumInit(&t1,1);
    bigNumSetDec(&t1,"1");
    for(bigNumSetDec(&t,"1"); bigNumCmp(&t,pObj2)<1;)
    {
        bigNumMul(&tans,pAns,pObj1);
        bigNumInit(pAns,tans.sd);
        pAns->sd=tans.sd;
        for(int i=0; i<pAns->sd; i++)pAns->d[i]=tans.d[i];
        bigNumAdd(&tans,&t,&t1);
        t.sd=tans.sd;
        for(int i=0; i<pAns->sd; i++)t.d[i]=tans.d[i];
    }
    updbd(pAns);
}

// factorial of obj1, return -1 if fail
int32_t bigNumFactorial( BigNum *pAns, const BigNum *pObj )
{
    if(pObj->pos<0)return -1;
    bigNumInit(pAns,1);
    bigNumSetDec(pAns,"1");
    BigNum t,tans,t1;
    bigNumInit(&t,pObj->space);
    bigNumInit(&t1,1);
    bigNumSetDec(&t1,"1");
    for(bigNumSetDec(&t,"1"); bigNumCmp(&t,pObj)<1;)
    {
        bigNumMul(&tans,pAns,&t);
        bigNumInit(pAns,tans.sd);
        pAns->sd=tans.sd;
        for(int i=0; i<pAns->sd; i++)pAns->d[i]=tans.d[i];
        bigNumAdd(&tans,&t,&t1);
        t.sd=tans.sd;
        for(int i=0; i<pAns->sd; i++)t.d[i]=tans.d[i];
    }
    updbd(pAns);
}

// k-permutations of n, return -1 if fail
int32_t bigNumPermutation( BigNum *pAns, const BigNum *pN, const BigNum *pK )
{
    int x=bigNumCmp(pN,pK);
    if(x<0)return -1;
    BigNum n,nmm,t,t0;
    bigNumInit(&t0,1);
    bigNumSetDec(&t0,"0");//printf("t0: ");bigNumPrintDec(&t0);
    bigNumAdd(&n,pN,&t0);//printf("n: ");bigNumPrintDec(&n);
    bigNumSub(&nmm,&n,pK);//printf("nmm: ");bigNumPrintDec(&nmm);

    bigNumFactorial(&t,&n);
    bigNumInit(&n,t.sd);
    n.sd=t.sd;
    for(int i=0; i<n.sd; i++)n.d[i]=t.d[i]; //printf("n!: ");bigNumPrintDec(&n);

    bigNumFactorial(&t,&nmm);
    bigNumInit(&nmm,t.sd);
    nmm.sd=t.sd;
    for(int i=0; i<nmm.sd; i++)nmm.d[i]=t.d[i]; //printf("nmm!: ");bigNumPrintDec(&nmm);

    bigNumDiv(pAns,&t,&n,&nmm);
    updbd(pAns);
}

// k-combinations of n, return -1 if fail
int32_t bigNumCombination( BigNum *pAns, const BigNum *pN, const BigNum *pK )
{
    BigNum p,m,t;
    bigNumPermutation(&p,pN,pK);
    bigNumFactorial(&m,pK);
    bigNumDiv(pAns,&t,&p,&m);
}

// greatest common divisor of obj1 and obj2, return -1 if fail
int32_t bigNumGCD( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 )
{
    if(pObj1->pos<0||pObj2->pos<0)return -1;
    BigNum m,n,t,t0,tQuo;
    bigNumInit(&t0,1);
    bigNumSetDec(&t0,"0");
    bigNumAdd(&m,pObj1,&t0);//NOT bigNum ver.
    bigNumAdd(&n,pObj2,&t0);//int gcd(int m, int n)
    while(bigNumCmp(&n,&t0)>0) //while(n != 0) {
    {
        bigNumDiv(&tQuo,&t,&m,&n);//int r = m % n;
        bigNumAdd(&m,&n,&t0);//m = n;
        bigNumAdd(&n,&t,&t0);//n = r;
    }
    bigNumAdd(pAns,&m,&t0);//return m;}
}

// least common multiple of obj1 and obj2, return -1 if fail
int32_t bigNumLCM( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 )
{
    //p1*p2/gcd
    BigNum t1,t2,t;
    bigNumMul(&t1,pObj1,pObj2);
    bigNumGCD(&t2,pObj1,pObj2);
    bigNumDiv(pAns,&t,&t1,&t2);
}

// check obj is prime, 1 true, 0 false
int32_t isPrime( const BigNum *pObj )
{
    BigNum t,t0,t1,q,r,dest;
    bigNumInit(&t0,1);
    bigNumSetDec(&t0,"0");
    bigNumInit(&t1,1);
    bigNumSetDec(&t1,"1");
    if(bigNumCmp(pObj,&t1)<=0)return 0;
    bigNumInit(&dest,(pObj->sd+2)/2);
    dest.sd=dest.space;
    for(int i=0; i<dest.sd; i++)dest.d[i]=9;
    updbd(&dest);
    bigNumAdd(&t,&t1,&t1);
    while(bigNumCmp(&t,&dest)<0&&bigNumCmp(&t,pObj)<0)
    {
        bigNumDiv(&q,&r,pObj,&t);
        if(bigNumCmp(&r,&t0)==0)
        {
            return 0;
        }
        bigNumAdd(&q,&t,&t1);
        bigNumAdd(&t,&q,&t0);
    }
    return 1;
}

//update value
int32_t updbb(BigNum *pObj ) //update by bin
{
    int i=0;
    //update hex
    pObj->sh=1;
    for(i=0; i<pObj->space; i++)pObj->h[i]=0; //ini
    for(i=0; i<pObj->sb; i++)
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sh; j++)
        {
            pObj->h[j]=(pObj->h[j])*2+c;
            if(pObj->h[j]>=16)
            {
                c=pObj->h[j]/16;
                pObj->h[j]=(pObj->h[j])%16;
                if(j==pObj->sh-1&&c>0)pObj->sh+=1;
                if(pObj->sh>pObj->space)return;
            }
            else
            {
                c=0;
            }
        }
        pObj->h[0]+=pObj->b[i];
    }
    if(pObj->h[0]>=16) //final digit
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sh; j++)
        {
            pObj->h[j]+=c;
            if(pObj->h[j]>=16)
            {
                c=pObj->h[j]/16;
                pObj->h[j]=(pObj->h[j])%16;
                if(j==pObj->sh-1&&c>0)pObj->sh+=1;
                if(pObj->sh>pObj->space)return;
            }
            else
            {
                c=0;
            }
        }
    }
    for(int i=0; i<(pObj->sh)/2; i++) //reverse
    {
        int t=pObj->h[i];
        pObj->h[i]=pObj->h[pObj->sh-i-1];
        pObj->h[pObj->sh-i-1]=t;
    }

    //update dec
    pObj->sd=1;
    for(i=0; i<pObj->space; i++)pObj->d[i]=0; //ini
    for(i=0; i<pObj->sb; i++)
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sd; j++)
        {
            pObj->d[j]=(pObj->d[j])*2+c;
            if(pObj->d[j]>=10)
            {
                c=pObj->d[j]/10;
                pObj->d[j]=(pObj->d[j])%10;
                if(j==pObj->sd-1&&c>0)pObj->sd+=1;
                if(pObj->sd>pObj->space)return;
            }
            else
            {
                c=0;
            }
        }
        pObj->d[0]+=pObj->b[i];
    }
    if(pObj->d[0]>=10) //final digit
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sd; j++)
        {
            pObj->d[j]+=c;
            if(pObj->d[j]>=10)
            {
                c=pObj->d[j]/10;
                pObj->d[j]=(pObj->d[j])%10;
                if(j==pObj->sd-1&&c>0)pObj->sd+=1;
                if(pObj->sd>pObj->space)return;
            }
            else
            {
                c=0;
            }
        }
    }
    for(int i=0; i<(pObj->sd)/2; i++) //reverse
    {
        int t=pObj->d[i];
        pObj->d[i]=pObj->d[pObj->sd-i-1];
        pObj->d[pObj->sd-i-1]=t;
    }
}
int32_t updbd(BigNum *pObj ) //update by dec
{
    int i=0;
    //update hex
    pObj->sh=1;
    for(i=0; i<pObj->space; i++)pObj->h[i]=0; //ini
    for(i=0; i<pObj->sd; i++)
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sh; j++)
        {
            pObj->h[j]=(pObj->h[j])*10+c;
            if(pObj->h[j]>=16)
            {
                c=pObj->h[j]/16;
                pObj->h[j]=(pObj->h[j])%16;
                if(j==pObj->sh-1&&c>0)pObj->sh+=1;
                if(pObj->sh>pObj->space)return;
            }
            else
            {
                c=0;
            }
        }
        pObj->h[0]+=pObj->d[i];
    }
    if(pObj->h[0]>=16) //final digit
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sh; j++)
        {
            pObj->h[j]+=c;
            if(pObj->h[j]>=16)
            {
                c=pObj->h[j]/16;
                pObj->h[j]=(pObj->h[j])%16;
                if(j==pObj->sh-1&&c>0)pObj->sh+=1;
                if(pObj->sh>pObj->space)return;
            }
            else
            {
                c=0;
            }
        }
    }
    for(int i=0; i<(pObj->sh)/2; i++) //reverse
    {
        int t=pObj->h[i];
        pObj->h[i]=pObj->h[pObj->sh-i-1];
        pObj->h[pObj->sh-i-1]=t;
    }

    //update bin
    pObj->sb=1;
    for(i=0; i<pObj->space; i++)pObj->b[i]=0; //ini
    for(i=0; i<pObj->sd; i++)
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sb; j++)
        {
            pObj->b[j]=(pObj->b[j])*10+c;
            if(pObj->b[j]>=2)
            {
                c=pObj->b[j]/2;
                pObj->b[j]=(pObj->b[j])%2;
                if(j==pObj->sb-1&&c>0)pObj->sb+=1;
                if(pObj->sb>pObj->space*4)return;
            }
            else
            {
                c=0;
            }
        }
        pObj->b[0]+=pObj->d[i];
    }
    if(pObj->b[0]>=2) //final digit
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sb; j++)
        {
            pObj->b[j]+=c;
            if(pObj->b[j]>=2)
            {
                c=pObj->b[j]/2;
                pObj->b[j]=(pObj->b[j])%2;
                if(j==pObj->sb-1&&c>0)pObj->sb+=1;
                if(pObj->sb>pObj->space*4)return;
            }
            else
            {
                c=0;
            }
        }
    }
    for(int i=0; i<(pObj->sb)/2; i++) //reverse
    {
        int t=pObj->b[i];
        pObj->b[i]=pObj->b[pObj->sb-i-1];
        pObj->b[pObj->sb-i-1]=t;
    }
}
int32_t updbh(BigNum *pObj ) //update by hex
{
    int i=0;
    //update dec
    pObj->sd=1;
    for(i=0; i<pObj->space; i++)pObj->d[i]=0; //ini
    for(i=0; i<pObj->sh; i++)
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sd; j++)
        {
            pObj->d[j]=(pObj->d[j])*16+c;
            if(pObj->d[j]>=10)
            {
                c=pObj->d[j]/10;
                pObj->d[j]=(pObj->d[j])%10;
                if(j==pObj->sd-1&&c>0)pObj->sd+=1;
                if(pObj->sd>pObj->space)return;
            }
            else
            {
                c=0;
            }
        }
        pObj->d[0]+=pObj->h[i];
    }
    if(pObj->d[0]>=10) //final digit
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sd; j++)
        {
            pObj->d[j]+=c;
            if(pObj->d[j]>=10)
            {
                c=pObj->d[j]/10;
                pObj->d[j]=(pObj->d[j])%10;
                if(j==pObj->sd-1&&c>0)pObj->sd+=1;
                if(pObj->sd>pObj->space)return;
            }
            else
            {
                c=0;
            }
        }
    }
    for(int i=0; i<(pObj->sd)/2; i++) //reverse
    {
        int t=pObj->d[i];
        pObj->d[i]=pObj->d[pObj->sd-i-1];
        pObj->d[pObj->sd-i-1]=t;
    }

    //update bin
    pObj->sb=1;
    for(i=0; i<pObj->space; i++)pObj->b[i]=0; //ini
    for(i=0; i<pObj->sh; i++)
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sb; j++)
        {
            pObj->b[j]=(pObj->b[j])*16+c;
            if(pObj->b[j]>=2)
            {
                c=pObj->b[j]/2;
                pObj->b[j]=(pObj->b[j])%2;
                if(j==pObj->sb-1&&c>0)pObj->sb+=1;
                if(pObj->sb>pObj->space*4)return;
            }
            else
            {
                c=0;
            }
        }
        pObj->b[0]+=pObj->h[i];
    }
    if(pObj->b[0]>=2) //final digit
    {
        int c=0;//carry flag
        for(int j=0; j<pObj->sb; j++)
        {
            pObj->b[j]+=c;
            if(pObj->b[j]>=2)
            {
                c=pObj->b[j]/2;
                pObj->b[j]=(pObj->b[j])%2;
                if(j==pObj->sb-1&&c>0)pObj->sb+=1;
                if(pObj->sb>pObj->space*4)return;
            }
            else
            {
                c=0;
            }
        }
    }
    for(int i=0; i<(pObj->sb)/2; i++) //reverse
    {
        int t=pObj->b[i];
        pObj->b[i]=pObj->b[pObj->sb-i-1];
        pObj->b[pObj->sb-i-1]=t;
    }
}
