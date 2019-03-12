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

void add_128(int* A, int* B, int* C);
void add(int *tab_res, int num,...);

int main(void){
	// A = 0 x 00000000000000000000000000000100 00000000000000000000000000001111 00000000000000000000000000001001 00000000000000000000000000001000
	// B = 0 x 00000000000000000000000000000000 00000000000000000000000000000001 00000000000000000000000000000000 00000000000000000000000000000001

	// A = 316912650333758500000000000000
	// B = 18446744073709552000
	// A + B = 316912650352205244073709552000

	// Pas de retenues possibles pour le dernier tour
	int A[5] = {0b00000000000000000000000000000100, 0b00000000000000000000000000000111, 0b01000000000000000000000000000110, 0b00000000000000000000000000000011, 0b00000000000000000000000000000000};
	int B[5] = {0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b01000000000000000000000000000100, 0b00000000000000000000000000000000, 0b00000000000000000000000000000001};
	int C[5];

	add_128(A, B, C);

	int D[5] = {0b00000000000000000000000000000010, 0b00000000000000000000000000000000, 0b01000000000000000000000000000100, 0b00000000000000000000000000000000, 0b00000000000000000000000000000001};

	int C2[5];
	add_128(C, D, C2);
///*
//	int result = 0;
//	int power = 0;
//	for (int j = 4; j >= 0; j--) {
//		result += C[j] * pow(2,power);
//		//printf("C[i] = %d, pow = %f, res = %f\n",C[j], pow(2,power), C[j] * pow(2,power));
//		power += 31;
//	}
//	printf("result = %d\n", result);
//*/
	int tab_res[5] = {0, 0, 0, 0, 0};

	add(tab_res, 3, A, B, D);
	//printf("attendu = %d, %d, %d, %d, %d\n", C[0],C[1],C[2],C[3], C[4] );
	printf("attendu = %d, %d, %d, %d, %d\n", C2[0],C2[1],C2[2],C2[3], C2[4] );
   printf("resulat = %d, %d, %d, %d, %d\n", tab_res[0],tab_res[1],tab_res[2],tab_res[3], tab_res[4] );
   //printf("Average of 5, 10, 15 = %f\n", average(3, 5,10,15));

	fflush(stdout);

	return 0;
}

void add(int *tab_res, int num,...) {

   va_list valist;
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);
   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
	   //tab_res += va_arg(valist, int*);
	   add_128(va_arg(valist, int*), tab_res, tab_res );
   }

   /* clean memory reserved for valist */
   va_end(valist);
}

void add_128(int* A, int* B, int* C) {
	int carry = 0;

	for (int i = 5 - 1; i >= 0; i--) {
		//printf("i = %d\n", i);
		C[i] = A[i] + B[i] + carry;
		if (C[i]<0) {
			C[i] = C[i] + pow(2,31);
			carry = 1;
		}
		else
			carry = 0;
		//printf("A[i] = %d, B[i] = %d, C[i] = %d, carry = %d\n",A[i], B[i], C[i], carry);
	}
	if (C[4]<0)
		printf("problem detected!\n");
}

