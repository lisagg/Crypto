/*
*****************************************************************************

  File        : main.cpp

  The MIT License (MIT)
  Copyright (c) 2019 STMicroelectronics

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*****************************************************************************
*/

#include<stdio.h>
#include <math.h>
#include <stdarg.h>

void add_128(int* A, int* B, int* result);
void add(int *tab_res, int num,...);
int isBiggerOrEqual(int* A, int* B);
void sub_128(int* A, int* B, int* result);
void sub(int *tab_res, int num,...);


int main(void){
	// Pas de retenues possibles pour le dernier tour
	// Bit de signe ï¿½ '0' en dï¿½but de chaque ï¿½lï¿½ment du tableau
	int A[5] = {0b00000000000000000000000000000100, 0b00000000000000000000000000000111, 0b01000000000000000000000000000110, 0b00000000000000000000000000000011, 0b00000000000000000000000000000000};
	int B[5] = {0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b01000000000000000000000000000100, 0b00000000000000000000000000000000, 0b00000000000000000000000000000001};
	int C[5] = {0b00000000000000000000000000000010, 0b00000000000000000000000000000000, 0b01000000000000000000000000000100, 0b00000000000000000000000000000000, 0b00000000000000000000000000000001};
	int tab_res[5] = {0, 0, 0, 0, 0};

	sub(tab_res, 3, A, B, C);
	printf("resulat = %d, %d, %d, %d, %d\n", tab_res[0],tab_res[1],tab_res[2],tab_res[3], tab_res[4] );

	fflush(stdout);

	return 0;
}

/* additionne 2 entiers de 128 bits représentés en tableaux de 32bits*/
void add_128(int* A, int* B, int* result) {
	int carry = 0;

	for (int i = 4; i >= 0; i--) {
		result[i] = A[i] + B[i] + carry;
		if (result[i]<0) {
			result[i] = result[i] + pow(2,31);
			carry = 1;
		}
		else
			carry = 0;
	}
	if (result[4]<0)
		printf("problem detected!\n");
}

/* soustrait 2 entiers de 128 bits représentés en tableaux de 32bits*/
void sub_128(int* A, int* B, int* result) {
	int carry = 0;

	// Si A > B, on effectue la soustraction
	if (isBiggerOrEqual(A, B)) {
		for (int i = 4; i >= 0; i--) {
			if (A[i] < B[i] + carry) {
				result[i] = pow(2,31) + A[i] - B[i] - carry;
				carry = 1;
			}
			else {
				result[i] = A[i] - B[i] - carry;
				carry = 0;
			}
		}
		if (result[4]<0)
			printf("problem detected!\n");
	}
	else
		printf("A doit ï¿½tre supï¿½rieur ou ï¿½gal ï¿½ B.");
}



/*Fonction pour additionner 2 ou plus 128 bits représentés en tableaux de 32bits*/
void add(int *tab_res, int num,...) {
   va_list valist;
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);
   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
	   add_128(va_arg(valist, int*), tab_res, tab_res );
   }
   /* clean memory reserved for valist */
   va_end(valist);
}

/*Fonction pour soustraire 2 ou plus 128 bits représentés en tableaux de 32bits
 * exemple sub(res, 3, A, B, C) met dans res A-B-C
 * */
void sub(int *tab_res, int num,...) {
   va_list valist;
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);
   add_128(tab_res, va_arg(valist, int*), tab_res);
   /* access all the arguments assigned to valist */
   for (i = 1; i < num; i++) {
	   sub_128( tab_res, va_arg(valist, int*), tab_res );
   }
   /* clean memory reserved for valist */
   va_end(valist);
}

// retourne 1 si A >= B, 0 sinon
int isBiggerOrEqual(int* A, int* B) {
	for (int i = 0; i <= 4; i++) {
		if (A[i] > B[i])
			return 1;
		else if (A[i] < B[i])
			return 0;
	}
	return 1;
}
