#ifndef STRUCTS_DATA
#define STRUCTS_DATA


//~ IMPORTANT : We take 'phi = 1 << WORD_SIZE'
#define WORD_SIZE 64
#define POLY_DEG 9
#define NB_COEFF 10
#define NB_ADD_MAX 0

#define RHO_LOG2 57
//~ We will take : rho = 1 << RHO_LOG2.


typedef __int128 int128;
typedef unsigned __int128 uint128;


static uint64_t amns_rho;

//~ will contain a representative of 'rho' in the amns
//~ important : this initial value is that of 'rho*phi'; correct value will be put during initialization step
static int32_t rho_rep[NB_COEFF][5] = {{0, 0, 0, 2345927, 994003494}, {0, 0, 0, 3701063, 1560735811}, {0b1, 0, 0b1, 0b1111111111110101000100001100101, 0b0011000111111111011000101111000}, {0, 0, 0, 2853894, 1120778867}, {0b1, 0, 0b1, 0b1111111111010110010011111001011, 0b0101010101011000101110010001011}, {0, 0, 0, 415458, 765687663}, {0, 0, 0, 701044, 498016866}, {0b1, 0, 0b1, 0b1111111111111001001011110111110, 0b1100011010011101011000100000110}, {0b1, 0, 0b1, 0b1111111111100011000110110100000, 0b1100000101101101101101100010100}, {0b1, 0, 0b1, 0b1111111111100011011101011100101, 0b0101111101000100100111001100000}};




//~ representatives of (RHO)^i (for i=2,4,...) in the amns (for conversions : int to amns)
static int64_t RHO_POWS[(NB_COEFF - 2)][NB_COEFF];

static mpz_t modul_p;
static mpz_t gama_pow[POLY_DEG];

#endif

