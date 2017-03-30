#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "configure.h"
#include "convolution.h"
//#include "bias.h"
//#include "pooling.h"

using namespace std;


void CNN (TYPE_T *img_in, TYPE_T *weight3, TYPE_T *conv3_out)
{
    /* define the interface */
#pragma HLS INTERFACE m_axi port=img_in offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=weight3 offset=slave bundle=gmem2
//#pragma HLS INTERFACE m_axi port=bias3 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=conv3_out offset=slave bundle=gmem3
#pragma HLS INTERFACE s_axilite port=img_in bundle=control
#pragma HLS INTERFACE s_axilite port=weight3 bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control


	//Convolution conv2;
    conv <R_IN3, C_IN3, N3, K3, M3, P3,S3,R_OUT3, C_OUT3> (img_in, conv3_out, weight3);
    return;
}
