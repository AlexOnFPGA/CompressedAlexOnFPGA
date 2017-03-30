//
//  convolution.cpp
//  cnn_2
//
//  Created by tqy on 3/10/17.
//  Copyright ? 2017 tqy. All rights reserved.
//

#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__

#include <stdio.h>
#include "configure.h"
#include <string.h>


template<int R_IN, int C_IN, int N, int K, int M, int P, int S, int R_OUT, int C_OUT>

void conv (TYPE_T *img_in, TYPE_T *conv_out, TYPE_T *weight){

#pragma HLS INTERFACE m_axi port=img_in offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=weight offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=conv_out offset=slave bundle=gmem2
//#pragma HLS INTERFACE bram port=fm_in
//#pragma HLS INTERFACE bram port=fm_out
#pragma HLS INTERFACE s_axilite port=return bundle=control


    	TYPE_T fm_in[N][R_IN+2*P][C_IN+2*P];
	#pragma HLS ARRAY_PARTITION variable=fm_in cyclic dim=1 factor=24
//    #pragma HLS ARRAY_RESHAPE variable=fm_in complete dim=3
//	#pragma HLS ARRAY_RESHAPE variable=fm_in cyclic dim=3 factor=14
    	memcpy(&(fm_in[0][0][0]), img_in, sizeof(TYPE_T)*N*(R_IN+2*P)*(C_IN+2*P));
    	TYPE_T bias[M]={0};
    #pragma HLS ARRAY_PARTITION variable=bias complete dim=1
    	TYPE_T fm_out[M][R_OUT][C_OUT];
    #pragma HLS ARRAY_PARTITION variable=fm_out cyclic dim=1 factor=32

    	TYPE_T buf_weight[Tm][Tn][K][K];
#pragma HLS ARRAY_RESHAPE variable=buf_weight complete dim=1
#pragma HLS ARRAY_RESHAPE variable=buf_weight complete dim=2


		L1:for (int to=0; to<M; to+=Tm){
			L0:for (int ti=0; ti < N;ti+=Tn){
			 memcpy(buf_weight, weight+to*N*K*K+ti*K*K,sizeof(TYPE_T)*Tm*Tn*K*K);
			L2:for(int i = 0; i < K; i++) {
                            L3:for(int j = 0; j < K; j++) {
                                L4:for (int trr = 0;trr <  R_OUT; trr++) {

                                	L5:for (int tcc = 0; tcc < C_OUT; tcc++) {
                        #pragma HLS PIPELINE
                        #pragma HLS INLINE OFF
                                    	L6:for (int too = 0; too < Tm; too++) {
                        #pragma HLS UNROLL
                                        	L7:for(int tii = 0; tii < Tn; tii++) {
                        #pragma HLS UNROLL
                                                fm_out[to+too][trr][tcc] += buf_weight[too][tii][i][j] * fm_in[ti+tii][S * trr + i][S * tcc + j];
                                        }}}}}}}}
      L8:for (int j = 0;j<R_OUT;j++)
          L9:for (int k = 0;k<C_OUT;k++){
#pragma HLS PIPELINE
             L10:for (int i = 0;i<M;i++){
                   fm_out[i][j][k]= bias[i] + fm_out[i][j][k];
				   if (fm_out[i][j][k] < 0) fm_out[i][j][k] = 0;
                 }
           }
      memcpy(conv_out, &(fm_out[0][0][0]), sizeof(TYPE_T)*M*R_OUT*C_OUT);
    }

#endif
