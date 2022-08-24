#include "Light_Weight_Decoder.h"

void LW_Decoder_Init(Light_Weight_Decoder * lw_decoder, uint8_t * buffer, size_t buffer_size){
    lw_decoder->buffer = buffer;
    lw_decoder->buffer_size = buffer_size;
    lw_decoder->read_pointer = 0;
}

void LW_Decoder_Print_Contents_Hex_Raw(Light_Weight_Decoder * decoder_instance){
    printf("Decoder Buffer Contents: \r\n");

    for(uint8_t i = 0; i < decoder_instance->read_pointer ; i++){
        //printf("%02X", decoder_instance->buffer[decoder_instance->read_pointer - 1 - i]);
        printf("%02X", decoder_instance->buffer[i]);
    }
    printf("\r\nBytes Used: %lu", decoder_instance->read_pointer);
    printf("\r\n================\r\n");
}

void LW_Decoder_Restart(Light_Weight_Decoder * lw_decoder){
    lw_decoder->read_pointer = 0;
}

uint8_t LW_Decoder_Decode_1_Byte_Unsigned(Light_Weight_Decoder * lw_decoder){
    uint8_t aux_return;
    aux_return = lw_decoder->buffer[lw_decoder->read_pointer];
    lw_decoder->read_pointer += 1;
    return aux_return;
}

uint16_t LW_Decoder_Decode_2_Byte_Unsigned(Light_Weight_Decoder * lw_decoder){
    uint16_t aux_return;
    aux_return = *( (uint16_t *)(&lw_decoder->buffer[lw_decoder->read_pointer]) );
    lw_decoder->read_pointer += 2;
    return aux_return;
}

uint32_t LW_Decoder_Decode_4_Byte_Unsigned(Light_Weight_Decoder * lw_decoder){
    uint32_t aux_return;
    aux_return = *( (uint32_t *)(&lw_decoder->buffer[lw_decoder->read_pointer]) );
    lw_decoder->read_pointer += 4;
    return aux_return;
}

int8_t LW_Decoder_Decode_1_Byte_Signed(Light_Weight_Decoder * lw_decoder){
    int8_t aux_return;
    aux_return = lw_decoder->buffer[lw_decoder->read_pointer];
    lw_decoder->read_pointer += 1;
    return aux_return;
}

int16_t LW_Decoder_Decode_2_Byte_Signed(Light_Weight_Decoder * lw_decoder){
    int16_t aux_return;
    aux_return = *( (int16_t *)(&lw_decoder->buffer[lw_decoder->read_pointer] ));
    lw_decoder->read_pointer += 2;
    return aux_return;
}

int32_t LW_Decoder_Decode_4_Byte_Signed(Light_Weight_Decoder * lw_decoder){
    int32_t aux_return;
    aux_return = *( (int32_t *)(&lw_decoder->buffer[lw_decoder->read_pointer] )) ;
    lw_decoder->read_pointer += 4;
    return aux_return;
}

float LW_Decoder_Decode_Float(Light_Weight_Decoder * lw_decoder){
    float aux_return;
    aux_return = *( (float *)(&lw_decoder->buffer[lw_decoder->read_pointer] ));
    lw_decoder->read_pointer += 4;
    return aux_return;
}

double LW_Decoder_Decode_Double(Light_Weight_Decoder * lw_decoder){
    double aux_return;

    aux_return = *( (double *)(&lw_decoder->buffer[lw_decoder->read_pointer] ));
    lw_decoder->read_pointer += 8;
    return aux_return;
}

char * LW_Decoder_Decode_String(Light_Weight_Decoder * lw_decoder){
    char * aux_return;

    aux_return = &lw_decoder->buffer[lw_decoder->read_pointer];
    lw_decoder->read_pointer += (strlen(aux_return) + 1);

    return aux_return;
}