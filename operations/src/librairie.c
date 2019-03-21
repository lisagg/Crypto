3/*
 * librairie.c
 *
 *  Created on: 16 mars 2019
 *      Author: lisag
 */
#include "librairie.h"
#include "operations.h"

#define NB_COEFF 10
#define WORD_SIZE 64

//rop et op sont des polynomes représentés en pmns et suivant notre base donc se sont des tableau du type rop[NB_COEFF][5]
void internal_reduction(int *rop, int *op) { // int 64 et int 128

	int tmp_q[NB_COEFF][5]; //uint64_t sans [5]
	int tmp_zero[NB_COEFF][5]; //int 128 sans [5]
	int tempo_res[NB_COEFF][5];
	int tempo_res2[5];
	int tmp_mult[NB_COEFF][5] = {0};

//~ computation of : op*neg_inv_ri_rep_coeff mod((X^n - c), mont_phi)
	int constantes[10][5] = {{0,0,3,265232453,1301075987},
								{0,0,2,1966732964,382641100},
								{0,0,1,463745936,29416710},
								{0,0,0,566067269,1998375154},
								{0,0,0,857916278,688778796},
								{0,0,2,614080720,1951589506},
								{0,0,1,2127892607,1859236758},
								{0,0,1,1380410500,1747721376},
								{0,0,1,1844767645,1907583688},
								{0,0,2,2050867106,1873368180}
	};

	int constante_mult[5] = {0,0, 3, 2147483647, 2147483646};
	int indice = 0;
	for (int j = 0; j < NB_COEFF; j ++) {
		for(int i = 0 ; i < NB_COEFF; i ++){
			indice = i - j;
			if(indice < 0){
				indice = indice + NB_COEFF;
			}
			mult_128(&op[i], constantes[indice],tempo_res[i]);
		}
		add(tempo_res2 ,10, tempo_res[0],tempo_res[1],tempo_res[2],tempo_res[3],tempo_res[4],tempo_res[5],tempo_res[6],tempo_res[7],tempo_res[8],tempo_res[9]);
		if(j < 8) {
			mult_128(&tmp_q[j][0], tempo_res2, constante_mult);
		}

	}


//~ computation of : tmp_q*red_int_coeff mod(X^n - c)
	int constantes2[10][5] ={	{0,0,0,417928,566989053},
							{0,0,0, 502366, 631043372},
							{0,0,0, 385707, 586693830},
							{0,0,0, 494195, 168469458},
							{0,0,0,797746, 1154618716},
							{0,0,0, 1197261, 370139154},
							{0,0,0,859125,578910610},
							{0,0,0,1256881,965507168},
							{0,0,0,511533,1153479332},
							{0,0,0,511533,1153479332}
	};
	int coeff[10] = {0, 1, 1, 0, 1, 0, 1, 1, 1, 0};  // 0 correspond à un - et 1 à un +
	int j;

	// Tableau pour faire la multiplication *2
	int deux[5] = {0, 0, 0, 0, 2};

	for(int i = 0; i < NB_COEFF; i ++) {
		// Update les constantes * tmp_q
		for(int j = 0; j< NB_COEFF; j ++) {
			indice = i - j;
			if(indice < 0){
				indice = indice + NB_COEFF;
			}
			mult_128(constantes2[indice], tmp_q[j], tempo_res[j]);
		}


		// Addition sans *2
		for(j = 0; j < i + 1; j ++) {
			indice = i - j;
			if(indice < 0){
				indice = indice + NB_COEFF;
			}
			if(coeff[indice] == 0) {
				add_128(tmp_zero[i], tempo_res[j], tmp_zero[i]);
			}
		}

		// Addition avec * 2
		// * 2 à faire
		for(j= i+1; j < NB_COEFF; j ++) {
			indice = i - j;
			if(indice < 0){
				indice = indice + NB_COEFF;
			}
			if(coeff[indice] == 1){
				if(i < 8){
					mult_128(tmp_zero[i], deux, tmp_mult[i]);
					add_128(tmp_zero[i], tmp_mult[j], tmp_zero[i]);
				}
				else
					add_128(tmp_zero[i], tempo_res[j], tmp_zero[i]);
			}
		}

		// Soustraction sans *2
		for(j = 0; j < i + 1; j ++) {
			indice = i - j;
			if(indice < 0){
				indice = indice + NB_COEFF;
			}
			if(coeff[indice] == 1) {
				sub_128(tmp_zero[i], tempo_res[j], tmp_zero[i]);
			}
		}

		// Soustraction avec * 2
		// * 2 à faire
		for(j= i+1; j < NB_COEFF; j ++) {
			indice = i - j;
			if(indice < 0){
				indice = indice + NB_COEFF;
			}
			if(coeff[indice] == 0){
				if(i < 8){
					mult_128(tmp_zero[i], deux, tmp_mult[i]);
					sub_128(tmp_zero[i], tmp_mult[j], tmp_zero[i]);
				}
				else
					sub_128(tmp_zero[i], tempo_res[j], tmp_zero[i]);
			}
		}
	}

//~ computation of : (op + tmp_zero)/mont_phi
	for(int i = 0; i < NB_COEFF; i++) {
		add_128(&op[i], tmp_zero[i], &rop[i]);
		shiftLeft(&rop[i], WORD_SIZE, &rop[i]);
	}
}
