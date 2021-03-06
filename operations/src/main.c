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
#include "librairie.h"
#include "stdlib.h"

int main(void){
	// Pas de retenues possibles pour le dernier tour
	// Bit de signe � '0' en d�but de chaque �l�ment du tableau
//	int A[5] = {0b00000000000000000000000000000100, 0b00000000000000000000000000000111, 0b01000000000000000000000000000110, 0b00000000001000000000000000000011, 0b00000100000000100000000000000000};
//	int B[5] = {0b00000000000000000000000000000010, 0b00000000000000001000000000000000, 0b01000000000000000000000000000100, 0b00000000010000000000000000100000, 0b00100000010000000000100000000001};
//	int C[5] = {0b00000000000000000000000000100010, 0b00000100000000000000000000000000, 0b01000000000000000000000000000100, 0b00000000000000000000000000000000, 0b00000000000000000000000000000001};
//	int tab_res[5] = { 0, 0, 0, pow(2,30), 2};
	//mult_128(A, B, tab_res);
	//shiftLeft(tab_res, 2, tab_res);
//	int rop[10][5] ={ {0,0,0, 0b1001010011011001101001, 0b0000110011000001101100100011110}, {0, 0, 0, 0b1001110011111010011100, 0b0000000011001100001111110100110},
//			{0, 0, 0, 0b1110100101001011101110, 0b0000000100011111011000001101100}, {0, 0, 0b11, 0b1111111111111111110010010110010, 0b1111101101100101111111001110000},
//			{0, 0, 0, 0b110011111111100110, 0b1101000111100001101010100010001}, {0,0,0, 0b100011110100000101101, 0b1011100101010110100100000010111},
//			{0, 0, 0b11, 0b1111111111111000011110110100000, 0b0101100100011111101111010011011}, {0,0,0, 0b101100001100101100110, 0b0000101011110011111101010010110},
//			{0, 0, 0, 0b110000011000100111, 0b1010111111100101000110101111011}, {0,0,0b11, 0b1111111111101011111111110111001, 0b0101110010000000011101011111110}};
	int **rop;
	int i;
	rop = malloc( 10 * sizeof(int*));
	for( i = 0 ; i < 10 ; i++ ) {
		rop[i] = calloc (5, sizeof(int));
	}

	int **tempsum;

	tempsum = malloc( 10 * sizeof(int*));
	for( i = 0 ; i < 10 ; i++ ) {
		tempsum[i] = calloc (5, sizeof(int));
	}

	for(i = 0; i < 10; i++){
		tempsum[i][0] = 0;
		tempsum[i][1] = 0;
	}


	tempsum[0][2] = 0b11;
	tempsum[0][3] = 0b1000100010000000001100010111110;
	tempsum[0][4] = 0b0101001111001011010001100000000;

	tempsum[1][2] = 0b10;
	tempsum[1][3] = 0b0100010011010111100001111110101;
	tempsum[1][4] = 0b1110101111001001101000101000110;

	tempsum[2][2] = 0b1;
	tempsum[2][3] = 0b0100010111100100100001011111110;
	tempsum[2][4] = 0b1110100001110101101010111010000;

	tempsum[3][2] = 0b11;
	tempsum[3][3] = 0b0111100010000100010100110010001;
	tempsum[3][4] = 0b0100110010000110000011111111111;

	tempsum[4][2] = 0;
	tempsum[4][3] = 0b110011001010101010100001010110;
	tempsum[4][4] = 0b1001000001001001100000011011000;

	tempsum[5][2] = 0;
	tempsum[5][3] = 0b1100101000101111111100110010100;
	tempsum[5][4] = 0b0101010001101000000101001100001;

	tempsum[6][2] = 0b1;
	tempsum[6][3] = 0b0010100100001000001111111010011;
	tempsum[6][4] = 0b0100100111001101110100111110110;

	tempsum[7][2] = 0b11;
	tempsum[7][3] = 0b1110101000000001000110100110011;
	tempsum[7][4] = 0b1010010100110001011011110101011;

	tempsum[8][2] = 0b11;
	tempsum[8][3] = 0b1100100111110101110101101001011;
	tempsum[8][4] = 0b0011111111101110110100000010010;

	tempsum[9][2] = 0b0;
	tempsum[9][3] = 0b1110011000100001001111110011;
	tempsum[9][4] = 0b0000001111001010011101011011101;


	//int rop[10][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
//	tempsum[10][5] = { {0, 0, 0b10, 0b1111011011110010111101010100010, 0b1100010001111100110010010011110},  {0, 0, 0b11, 0b0011111111111101101100000110001, 0b1010001001110000101010001001000},
//			{0, 0, 0b10, 0b0010100101000101111100001011101, 0b0011001101110001111111010001111}, {0, 0, 0, 0b1101000101011000111110000111001, 0b0111100101010100000101100101011},
//			{0, 0, 0b11, 0b1111100101011100010010001111101, 0b0010111100001011101011011110100}, {0, 0, 0, 0b1111100011100000000000001000101, 0b0111110101110100001110111001011},
//			{0, 0, 0b11, 0b0100001011110000101110000001111, 0b0010101001101110000101010110111}, {0, 0, 0b1, 0b1100010111111010010001010011100, 0b0001010110101101010000110110100},
//			{0, 0, 0, 0b1001011011010000111110101110000, 0b1010101110001100010010101100100}, {0, 0, 0b10, 0b0101101010010110011010111001111, 0b1011010000111101000100111000011}};

	internal_reduction(rop, tempsum);
	printf("%d, %d, %d, %d, %d", rop[0][0], rop[0][1], rop[0][2], rop[0][3], rop[0][4]);

	fflush(stdout);

	return 0;
}
