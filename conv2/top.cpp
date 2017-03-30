#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "configure.h"
#include "convolution.h"
//#include "bias.h"
#include "pooling.h"

using namespace std;


void CNN (TYPE_T *img_in, TYPE_T *weight2, TYPE_T *bias2, TYPE_T *pool2_out)
{
    /* define the interface */
#pragma HLS INTERFACE m_axi port=img_in offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=weight2 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=bias2 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=pool2_out offset=slave bundle=gmem3
#pragma HLS INTERFACE s_axilite port=img_in bundle=control
#pragma HLS INTERFACE s_axilite port=weight2 bundle=control
#pragma HLS INTERFACE s_axilite port=bias2 bundle=control
#pragma HLS INTERFACE s_axilite port=pool2_out bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control


	//Convolution conv2;
	TYPE_T conv2_out[256][27][27];
#pragma HLS ARRAY_RESHAPE variable=conv2_out cyclic dim=1 factor=32

    conv <R_IN2, C_IN2, N2, K2, M2, P2,S2,R_OUT2, C_OUT2> (img_in, conv2_out, weight2, bias2);
    MaxPooling <R_OUT2, C_OUT2,M2, POOL_R2, POOL_C2,POOL_S2> pool2;
    pool2.pool_forward(conv2_out, pool2_out);
    return;
}
