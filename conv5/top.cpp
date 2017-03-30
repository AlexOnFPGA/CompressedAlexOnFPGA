#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "configure.h"
#include "convolution.h"
//#include "bias.h"
#include "pooling.h"

using namespace std;


void CNN (TYPE_T *img_in, TYPE_T *weight5, TYPE_T *bias5, TYPE_T *pool5_out)
{
    /* define the interface */
#pragma HLS INTERFACE m_axi port=img_in offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=weight5 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=bias5 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=pool5_out offset=slave bundle=gmem3
#pragma HLS INTERFACE s_axilite port=img_in bundle=control
#pragma HLS INTERFACE s_axilite port=weight5 bundle=control
#pragma HLS INTERFACE s_axilite port=bias5 bundle=control
#pragma HLS INTERFACE s_axilite port=pool5_out bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control


	//Convolution conv2;
	TYPE_T conv5_out[384][13][13];
#pragma HLS ARRAY_RESHAPE variable=conv5_out cyclic dim=1 factor=32

    conv <R_IN5, C_IN5, N5, K5, M5, P5, S5,R_OUT5, C_OUT5> (img_in, conv5_out, weight5, bias5);
    MaxPooling <R_OUT5, C_OUT5, M5, POOL_R5, POOL_C5,POOL_S5> pool5;
    pool5.pool_forward(conv5_out, pool5_out);
    return;
}
