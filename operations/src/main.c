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

#include "operations.h"


int main(void){
	// Pas de retenues possibles pour le dernier tour
	// Bit de signe � '0' en d�but de chaque �l�ment du tableau
	int A[5] = {0b00000000000000000000000000000100, 0b00000000000000000000000000000111, 0b01000000000000000000000000000110, 0b00000000001000000000000000000011, 0b00000100000000100000000000000000};
	int B[5] = {0b00000000000000000000000000000010, 0b00000000000000001000000000000000, 0b01000000000000000000000000000100, 0b00000000010000000000000000100000, 0b00100000010000000000100000000001};
	int C[5] = {0b00000000000000000000000000100010, 0b00000100000000000000000000000000, 0b01000000000000000000000000000100, 0b00000000000000000000000000000000, 0b00000000000000000000000000000001};
	int tab_res[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	mult_128(A, B, tab_res);

	fflush(stdout);

	return 0;
}
