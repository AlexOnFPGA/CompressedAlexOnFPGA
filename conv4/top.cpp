#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "configure.h"
#include "convolution.h"
//#include "bias.h"
//#include "pooling.h"

using namespace std;
void conv (TYPE_T *img_in, TYPE_T *conv_out, TYPE_T *weight);

void CNN (TYPE_T *img_in, TYPE_T *weight4, TYPE_T *conv4_out)
{
    /* define the interface */
#pragma HLS INTERFACE m_axi port=img_in offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=weight4 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=conv4_out offset=slave bundle=gmem2
#pragma HLS INTERFACE s_axilite port=img_in bundle=control
#pragma HLS INTERFACE s_axilite port=weight4 bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control


	//Convolution conv2;
    conv <R_IN4, C_IN4, N4, K4, M4, P4, S4 ,R_OUT4, C_OUT4> (img_in, conv4_out, weight4);
    return;
}
