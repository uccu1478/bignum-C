#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _BigNum_
{
    int space;
    int *d;//dec
    int sd;//size of dec
    int *b;//bin
    int sb;//size of bin
    int *h;//hex
    int sh;//size of hex
    int pos;//+:1 -:-1
    /* data */
} BigNum;

// initial big number to n-bit integer, return -1 if fail to initialize
int32_t bigNumInit( BigNum *pNum, int32_t n );

// free a big number
void bigNumFree( BigNum *pObj );

// 0 equal, -1 (obj1 less than obj2), 1 (obj1 bigger than obj2)
int32_t bigNumCmp( const BigNum *pObj1, const BigNum *pObj2 );

// print big number decimal
void bigNumPrintDec( const BigNum *pObj );

// print big number binary
void bigNumPrintBin( const BigNum *pObj );

// print big number hex
void bigNumPrintHex( const BigNum *pObj );

// set big number by decimal string, return -1 if fail or invalid
int32_t bigNumSetDec( BigNum *pObj, const char *decimal );

// set big number by binary string, return -1 if fail or invalid
int32_t bigNumSetBin( BigNum *pObj, const char *binary );

// set big number by hex string, return -1 if fail or invalid
int32_t bigNumSetHex( BigNum *pObj, const char *hex );

// obj1 add obj2, return -1 if fail
int32_t bigNumAdd( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 );

// obj1 substract obj2, return -1 if fail
int32_t bigNumSub( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 );

// obj1 multiply obj2, return -1 if fail
int32_t bigNumMul( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 );

// obj1 divide obj2, return -1 if fail
int32_t bigNumDiv( BigNum *pQuotient, BigNum *pRemainder, const BigNum *pObj1, const BigNum *pObj2 );

// obj1 to the power obj2, return -1 if fail
int32_t bigNumPow( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 );

// factorial of obj1, return -1 if fail
int32_t bigNumFactorial( BigNum *pAns, const BigNum *pObj );

// k-permutations of n, return -1 if fail
int32_t bigNumPermutation( BigNum *pAns, const BigNum *pN, const BigNum *pK );

// k-combinations of n, return -1 if fail
int32_t bigNumCombination( BigNum *pAns, const BigNum *pN, const BigNum *pK );

// greatest common divisor of obj1 and obj2, return -1 if fail
int32_t bigNumGCD( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 );

// least common multiple of obj1 and obj2, return -1 if fail
int32_t bigNumLCM( BigNum *pAns, const BigNum *pObj1, const BigNum *pObj2 );

// check obj is prime, 1 true, 0 false
int32_t isPrime( const BigNum *pObj );

//update value
int32_t updbb(BigNum *pObj );
int32_t updbd(BigNum *pObj );
int32_t updbh(BigNum *pObj );
