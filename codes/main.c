#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <gmp.h>

#include "structs_data.h"
#include "add_mult_poly.c"
#include "useful_functs.c"
#include "amns_init.c"

#define BILLION 1000000000L


//~ Compilation command : gcc -Wall -O2 main.c -o main -lgmp
//~ Execution command : ./main

//~ Important : polynomials representations form is P(X) = a0 + ... + an.X^n = (a0, ..., an).


int main(void){

	int i, nbiter;
	mpz_t A, B, C, E, S;
	mpz_inits (A, B, C, E, S, NULL);

	int64_t pa[NB_COEFF];
	int64_t pb[NB_COEFF];
	int64_t pc[NB_COEFF];
	int64_t ps[NB_COEFF];

	struct timespec start1, end1;
	struct timespec start2, end2;
	struct timespec start3, end3;
	uint64_t diff1, diff2, diff3;

	unsigned long seed = time(NULL);
	gmp_randstate_t r;
	gmp_randinit_default(r);
	gmp_randseed_ui(r, seed);


	init_data();

	nbiter = 1 << 15;

	mpz_urandomm(A, r, modul_p);
	mpz_set(B, A);
	//~ mpz_urandomm(B, r, modul_p);


	mpz_mod (A, A, modul_p);
	mpz_mod (B, B, modul_p);
	from_int_to_amns(pa, A);
	from_int_to_amns(pb, B);


	diff1 = 0;
	for (i=0; i<nbiter; i++) {
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &start1);

		mpz_mul (E, A, B);
		mpz_mod (E, E, modul_p);

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &end1);
		diff1 += BILLION * (end1.tv_sec - start1.tv_sec) + (end1.tv_nsec - start1.tv_nsec);
	}

	diff2 = 0;
	for (i=0; i<nbiter; i++) {
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &start2);

		mult_mod_poly(pc, pa, pb);

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &end2);
		diff2 += BILLION * (end2.tv_sec - start2.tv_sec) + (end2.tv_nsec - start2.tv_nsec);
	}

	diff3 = 0;
	for (i=0; i<nbiter; i++) {
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &start3);

		square_mod_poly(ps, pa);

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &end3);
		diff3 += BILLION * (end3.tv_sec - start3.tv_sec) + (end3.tv_nsec - start3.tv_nsec);
	}

	from_amns_to_int(C, pc);
	from_amns_to_int(S, ps);

	printf("\n");
	gmp_printf("gmp  : A   = %Zd\n", A);
	gmp_printf("gmp  : B   = %Zd\n", B);
	gmp_printf("gmp  : A*B = %Zd\n", E);
	gmp_printf("amns : A*B = %Zd\n", C);
	gmp_printf("amns : A*A = %Zd\n", S);
	printf("\nnbiter = %d\n", nbiter);
	printf("time using gmp       = %lu  nanoseconds\n", diff1);
	printf("time using amns prod = %lu  nanoseconds\n", diff2);
	printf("time using amns sqre = %lu  nanoseconds\n", diff3);


	mpz_clears (A, B, C, E, S, NULL);
	gmp_randclear(r);
	free_data();
	return 0;
}

