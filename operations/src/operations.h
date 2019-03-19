#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include<stdio.h>

void add_128(int* A, int* B, int* result);
void add_32(int* A, int* B, int * result, int* carry);
void add(int *tab_res, int num,...);
int isBiggerOrEqual(int* A, int* B);
void sub_128(int* A, int* B, int* result);
void sub(int *tab_res, int num,...);
void mult_128(int* A, int* B, int* result);
void shiftLeft(int *A, int nb, int* resultat);
//void printDoubleArray(int* A);
