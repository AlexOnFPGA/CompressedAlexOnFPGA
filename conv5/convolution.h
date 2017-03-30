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
//R_IN 227, C_IN 227, K 11, R_OUT 55, C_OUT 55, M 96, S 4
void conv (TYPE_T *img_in, TYPE_T fm_out[M][R_OUT][C_OUT], TYPE_T *weight, TYPE_T *bias){

#pragma HLS INTERFACE m_axi port=img_in offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=weight offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=bias offset=slave bundle=gmem2
#pragma HLS INTERFACE bram port=fm_out
//#pragma HLS INTERFACE bram port=fm_in
//#pragma HLS INTERFACE bram port=fm_out
#pragma HLS INTERFACE s_axilite port=return bundle=control


    	TYPE_T fm_in[N][R_IN+2*P][C_IN+2*P];
	#pragma HLS ARRAY_RESHAPE variable=fm_in complete dim=1
    	memcpy(&(fm_in[0][0][0]), img_in, sizeof(TYPE_T)*N*(R_IN+2*P)*(C_IN+2*P));
//    #pragma HLS ARRAY_RESHAPE variable=fm_in complete dim=3
//	#pragma HLS ARRAY_RESHAPE variable=fm_in cyclic dim=3 factor=14
    	TYPE_T buf_bias[M];
    #pragma HLS ARRAY_RESHAPE variable=buf_bias complete dim=1
    memcpy (buf_bias, bias, sizeof(TYPE_T)*M);


    	TYPE_T buf_weight[Tm][Tn][K][K];
#pragma HLS ARRAY_RESHAPE variable=buf_weight complete dim=1
#pragma HLS ARRAY_RESHAPE variable=buf_weight complete dim=2


		L1:for (int to=0; to < M; to+=Tm){
			L0:for (int ti=0; ti < N; ti+=Tn){
		//	 memcpy(&(fm_in[0][0][0]), img_in+ti*R_IN*C_IN, sizeof(TYPE_T)*Tn*(R_IN+2*P)*(C_IN+2*P));
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
                                                fm_out[too+to][trr][tcc] += buf_weight[too][tii][i][j] * fm_in[tii][S * trr + i][S * tcc + j];
                                            }
										}
									}
								}
							}
						}
		}
			L8:for (int j = 0;j<R_OUT;j++)
						          L9:for (int k = 0;k<C_OUT;k++){
						#pragma HLS PIPELINE
						             L10:for (int i = 0;i<Tm;i++){
						                   fm_out[i][j][k]= buf_bias[to+i] + fm_out[i][j][k];
						                 }
						           }
			     // memcpy(conv_out+to*C_OUT*R_OUT, &(fm_out[0][0][0]), sizeof(TYPE_T)*Tm**C_OUT*R_OUT);
			    }
    }


#endif
