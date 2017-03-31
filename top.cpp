#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "configure.h"
#include "convolution.h"
//#include "bias.h"
#include "pooling.h"

using namespace std;


void CNN (TYPE_T *conv2_in, TYPE_T *weight2, TYPE_T *bias2, TYPE_T *pool2_out, TYPE_T *conv3_in, TYPE_T *weight3, TYPE_T *bias3, TYPE_T *conv3_out)
{
    /* define the interface */
#pragma HLS INTERFACE m_axi port=conv2_in offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=weight2 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=bias2 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=pool2_out offset=slave bundle=gmem3
#pragma HLS INTERFACE s_axilite port=conv2_in bundle=control
#pragma HLS INTERFACE s_axilite port=weight2 bundle=control
#pragma HLS INTERFACE s_axilite port=bias2 bundle=control
#pragma HLS INTERFACE s_axilite port=pool2_out bundle=control
#pragma HLS INTERFACE m_axi port=conv3_in offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=weight3 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=bias3 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=conv3_out offset=slave bundle=gmem3
#pragma HLS INTERFACE s_axilite port=conv3_in bundle=control
#pragma HLS INTERFACE s_axilite port=weight3 bundle=control
#pragma HLS INTERFACE s_axilite port=bias3 bundle=control
#pragma HLS INTERFACE s_axilite port=conv3_out bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control
    
    
    /*****************conv2*****************/
    /*	
        TYPE_T conv2_out[256][27][27];
     #pragma HLS ARRAY_RESHAPE variable=conv2_out cyclic dim=1 factor=32
     
     conv_bram_out <R_IN2, C_IN2, N2, K2, M2, P2,S2,R_OUT2, C_OUT2> (conv2_in, conv2_out, weight2, bias2);
     MaxPooling <R_OUT2, C_OUT2,M2, POOL_R2, POOL_C2,POOL_S2> pool2;
	    pool2.pool_forward(conv2_out, pool2_out);
     */
    
    /*****************conv3*****************/
    conv_axi_out <R_IN3, C_IN3, N3, K3, M3, P3,S3,R_OUT3, C_OUT3> (conv3_in, conv3_out, weight3,bias3);
    
    return;
}
