#include "operations.h"

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

/* additionne deux entiers signé de 32bits*/
void add_32(int* A, int* B, int * result, int* carry) {
	*result = *A + *B;
	if( *result < 0){
		*result = *result + pow(2,31);
		*carry = 1;
	} else {
		carry =0;
	}
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

void mult_128(int* A, int* B, int* result) {
	int64_t tempo;
	int tab[25][10] = {0};
	int compteur = 0;
	// On fait : A0 * B0, A1 * B0, A2 * B0, ... A4 * B4.
	for (int i = 4; i >= 0; i--) {
		for (int j = 4; j >= 0; j--) {
			tempo = (int64_t)A[j]*(int64_t)B[i];
			// Pour chaque multiplication, on récupère les bits de poids forts et les bits de poids faibles
			tab[compteur][9+i+j-8] = tempo & 0x7FFFFFFF; // Récupération des bits de poids faibles en mettant les bits de poids forts à 0
			tab[compteur][9+i+j-9] = tempo >> 31; // Récupération des bits de poids forts en décalant vers la gauche
			compteur += 1;
		}
	}
	// On additionne les différents résultats intérmédiaires
	// Par exemple, (A0B0)poids faible + 0, puis (A0*B0*)poids fort + (A1*B0)poids faible + (A0*B1)poids faible, ...
	int tempCarry = 0;
	int carry = 0;
	// Le résultat sera stocké dans l'array result
	result = (int [10]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // On réinitialise le tableau contenant le résultat au cas où
	// On réalise les différentes additions
	for (int k = 9; k >= 0; k--) {
		result[k] = carry;
		carry = 0;
		for (int l = 0; l < 25; l++) {
			add_32(&result[k], &tab[l][k], &result[k], &tempCarry);
			carry = carry + tempCarry;
			tempCarry = 0;
		}
	}
	// Affichage du résultat
	for (int i = 0; i < 10; i++)
		printf("%d ", result[i]);
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
