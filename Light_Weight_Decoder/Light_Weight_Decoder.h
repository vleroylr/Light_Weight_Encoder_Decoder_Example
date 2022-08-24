/**
 * @file Light_Weight_Decoder.h
 * @author Victor Le Roy Brito (vleroy@tekroy.cl)
 * @brief 
 * @version 0.1
 * @date 2022-08-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _LIGHT_WEIGHT_DECODER
#define _LIGHT_WEIGHT_DECODER

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LW_DECODER_BUFFER_SIZE 128
typedef struct{
    uint8_t * buffer;
    size_t buffer_size;
    size_t read_pointer;
}Light_Weight_Decoder;

void LW_Decoder_Init(Light_Weight_Decoder * lw_decoder, uint8_t * buffer, size_t buffer_size);

void LW_Decoder_Print_Contents_Hex_Raw(Light_Weight_Decoder * decoder_instance);

void LW_Decoder_Restart(Light_Weight_Decoder * lw_decoder);

uint8_t LW_Decoder_Decode_1_Byte_Unsigned(Light_Weight_Decoder * lw_decoder);

uint16_t LW_Decoder_Decode_2_Byte_Unsigned(Light_Weight_Decoder * lw_decoder);

uint32_t LW_Decoder_Decode_4_Byte_Unsigned(Light_Weight_Decoder * lw_decoder);

int8_t LW_Decoder_Decode_1_Byte_Signed(Light_Weight_Decoder * lw_decoder);

int16_t LW_Decoder_Decode_2_Byte_Signed(Light_Weight_Decoder * lw_decoder);

int32_t LW_Decoder_Decode_4_Byte_Signed(Light_Weight_Decoder * lw_decoder);

float LW_Decoder_Decode_Float(Light_Weight_Decoder * lw_decoder);

double LW_Decoder_Decode_Double(Light_Weight_Decoder * lw_decoder);

char * LW_Decoder_Decode_String(Light_Weight_Decoder * lw_decoder);
#endif