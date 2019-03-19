#include "operations.h"

/* additionne 2 entiers de 128 bits repr�sent�s en tableaux de 32bits*/
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

/* additionne deux entiers sign� de 32bits*/
void add_32(int* A, int* B, int * result, int* carry) {
	*result = *A + *B;
	if( *result < 0){
		*result = *result + pow(2,31);
		*carry = 1;
	} else {
		carry =0;
	}
}

/* soustrait 2 entiers (A-B) de 128 bits repr�sent�s en tableaux de 32bits*/
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
		printf("A doit �tre sup�rieur ou �gal � B.");
}



/*Fonction pour additionner 2 ou plus 128 bits repr�sent�s en tableaux de 32bits*/
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

/*Fonction pour soustraire 2 ou plus 128 bits repr�sent�s en tableaux de 32bits
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

void mult_128(int* A, int* B, int* result) {
	int64_t tempo;
	int tab[25][10] = {0};
	int compteur = 0;
	// On fait : A0 * B0, A1 * B0, A2 * B0, ... A4 * B4.
	for (int i = 4; i >= 0; i--) {
		for (int j = 4; j >= 0; j--) {
			tempo = (int64_t)A[j]*(int64_t)B[i];
			// Pour chaque multiplication, on r�cup�re les bits de poids forts et les bits de poids faibles
			tab[compteur][9+i+j-8] = tempo & 0x7FFFFFFF; // R�cup�ration des bits de poids faibles en mettant les bits de poids forts � 0
			tab[compteur][9+i+j-9] = tempo >> 31; // R�cup�ration des bits de poids forts en d�calant vers la gauche
			compteur += 1;
		}
	}
	// On additionne les diff�rents r�sultats int�rm�diaires
	// Par exemple, (A0B0)poids faible + 0, puis (A0*B0*)poids fort + (A1*B0)poids faible + (A0*B1)poids faible, ...
	int tempCarry = 0;

	int carry = 0;
	// Le r�sultat sera stock� dans l'array tempoResult
	int tempoResult[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // On r�initialise le tableau contenant le r�sultat au cas o�
	// On r�alise les diff�rentes additions
	for (int k = 9; k >= 0; k--) {
		tempoResult[k] = carry;
		carry = 0;
		for (int l = 0; l < 25; l++) {
			add_32(&tempoResult[k], &tab[l][k], &tempoResult[k], &tempCarry);
			carry = carry + tempCarry;
			tempCarry = 0;
		}
	}

	// on veut que les 5 premier de r�sultat car au vu du code cela ne devrait rester sous 128bits
	result[0] = tempoResult[5];
	result[1] = tempoResult[6];
	result[2] = tempoResult[7];
	result[3] = tempoResult[8];
	result[4] = tempoResult[9];
}

void shiftLeft(int *A, int nb, int* resultat) {
	int zero[5] = {0, 0, 0, 0, 0};
	add_128(A, zero, resultat);
	printf("resultat %d\n", resultat[4]);
	int deux[5] = {0, 0, 0, 0, 2};
	for(int i = 0; i < nb; i ++) {
		mult_128(resultat, deux, resultat);
		printf("resultat %d\n", resultat[4]);
	}

}

// Fonction aide pour afficher matrice
//void printDoubleArray(int** A) {
//	for (int i = 0; i < sizeof(A)/sizeof(A[0]); i++) {
//		printf("i = %d\n", i);
//		printf("%d ", A[0]);
//		for (int j = 0; j < sizeof(A[0])/sizeof(A[0][0]); j++) {
//			printf("%d ", &A[i][j]);
//		}
//		printf("\n");
//	}
//}
