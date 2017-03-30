

#include <ap_fixed.h>
//#define	DEBUG			0
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

typedef			unsigned int				TYPE_PINT;
//typedef		double						TYPE_T;
//typedef			float						TYPE_T;
typedef		ap_fixed<16, 15, AP_TRN_ZERO>	TYPE_T;
//typedef		ap_fixed<20, 12, AP_TRN_ZERO>	TYPE_T;

#define Tr 13
#define Tc 13
#define Tm 32
#define Tn 16

#define R_IN1 227
#define C_IN1 227
#define N1 3
#define K1 11
#define P1 0
#define R_OUT1 55
#define C_OUT1 55
#define M1 96
#define S1 4

#define POOL_R1 3
#define POOL_C1 3
#define POOL_S1 2

#define R_IN2 27
#define C_IN2 27
#define N2 96
#define K2 5
#define P2 2
#define R_OUT2 27
#define C_OUT2 27
#define M2 256
#define S2 1

#define POOL_R2 3
#define POOL_C2 3
#define POOL_S2 2

#define R_IN3 13
#define C_IN3 13
#define N3 256
#define K3 3
#define P3 1
#define R_OUT3 13
#define C_OUT3 13
#define M3 384
#define S3 1

#define R_IN4 13
#define C_IN4 13
#define N4 384
#define K4 3
#define P4 1
#define R_OUT4 13
#define C_OUT4 13
#define M4 384
#define S4 1

#define R_IN5 13
#define C_IN5 13
#define N5 384
#define K5 3
#define P5 1
#define R_OUT5 13
#define C_OUT5 13
#define M5 256
#define S5 1

#define POOL_R5 3
#define POOL_C5 3
#define POOL_S5 2
