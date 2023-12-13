//
// Created by alireza on 10/6/23.
//

#ifndef FVLLMONTITRANSFORMER_MATMULC_H
#define FVLLMONTITRANSFORMER_MATMULC_H


#include <stddef.h>
#include "param.h"
#include "cgra.h"

#define BLOCK_SIZE 4

typedef struct {
} MatMul;

void MatMul_multiply(size_t seq_len, quant_bit_width* input, quant_bit_width* weight, quant_bit_width* output, size_t input_size, size_t output_size, cgra_t * cgra, uint8_t cgra_slot);
void MatMul_scale(quant_bit_width* input, int shift_scale, size_t mat_size);
void MatMul_multiply_blocks(size_t seq_len, quant_bit_width* input, quant_bit_width* weight, quant_bit_width* output, size_t input_size, size_t output_size);


#endif //FVLLMONTITRANSFORMER_MATMULC_H
