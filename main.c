#include <stdio.h>
#include <stdlib.h>

#include "bignum.h"

int main()
{
    BigNum num1, num2, num3, num4;

    // 9756277979052589857
    bigNumInit( &num1, 128 );
    bigNumSetDec(&num1,"42019");
    if(isPrime(&num1))printf("is.\n");
    else
    {
        printf("not.\n");
    }
    bigNumSetHex( &num1, "8765432187654321");//hex8765432187654321
    bigNumPrintDec( &num1 );//myOutPut 1 9756277979052589857
    bigNumPrintBin( &num1 );//myOutPut 2 1000011101100101010000110010000110000111011001010100001100100001
    bigNumPrintHex( &num1 );//myOutPut 3 8765432187654321

    // 1311768465173141112
    bigNumInit( &num2, 128 );
    bigNumSetHex( &num2, "1234567812345678");//hex1234567812345678
    bigNumPrintDec( &num2 );//myOutPut 4 1311768465173141112

    // 11068046444225730969
    bigNumAdd( &num3, &num1, &num2 );
    bigNumPrintDec( &num3 );//myOutPut 5 11068046444225730969

    // 8444509513879448745
    bigNumSub( &num3, &num1, &num2 );
    bigNumPrintDec( &num3 );//myOutPut 6 8444509513879448745

    // 12797977790384330769265737619320900984
    bigNumMul( &num3, &num1, &num2 );
    bigNumPrintDec( &num3 );//myOutPut 7 12797977790384330769265737619320900984

    bigNumDiv( &num3, &num4, &num1, &num2 );
    // 7
    bigNumPrintDec( &num3 );//myOutPut 8 7
    // 573898722840602073
    bigNumPrintDec( &num4 );//myOutPut 9 573898722840602073

    // 38654705673
    bigNumGCD( &num3, &num1, &num2 );
    bigNumPrintDec( &num3 );//myOutPut 10 38654705673

    // 331084600634370241406177208
    bigNumLCM( &num3, &num1, &num2 );
    bigNumPrintDec( &num3 );//myOutPut 11 331084600634370241406177208

    // 88393601556881408918814842533141000142486815892907919024928757521165040585171318827661185841057
    bigNumSetDec( &num2, "5" );
    bigNumPow( &num3, &num1, &num2);
    bigNumPrintDec( &num3 );//myOutPut 12 88393601556881408918814842533141000142486815892907919024928757521165040585171318827661185841057

    // 815915283247897734345611269596115894272000000000
    bigNumSetDec( &num1, "40" );
    bigNumFactorial( &num3, &num1);
    bigNumPrintDec( &num3 );//myOutPut 13 815915283247897734345611269596115894272000000000

    bigNumSetDec( &num2, "20" );
    // 137846528820
    bigNumCombination( &num3, &num1, &num2 );
    bigNumPrintDec( &num3 );//myOutPut 14 137846528820

    // 335367096786357081410764800000
    bigNumPermutation( &num3, &num1, &num2 );
    bigNumPrintDec( &num3 );//myOutPut 15 335367096786357081410764800000

    return 0;
}
