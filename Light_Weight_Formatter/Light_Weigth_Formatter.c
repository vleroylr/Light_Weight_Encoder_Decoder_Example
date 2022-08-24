#include "Light_Weigth_Formatter.h"

uint8_t asl = 2;


void LW_Formatter_Init(Light_Weight_Formatter * formatter_instance){
    formatter_instance->elements = 0;
}

void LW_Formatter_Add_Variable_Interface(Light_Weight_Formatter * formatter_instance, uint8_t * base, size_t bytes_number){
    for(uint8_t i = 0; i < bytes_number; i++){
        formatter_instance->buffer[formatter_instance->elements++] = *base++;
    }
}

uint8_t * LW_Formatter_Get_Buffer(Light_Weight_Formatter * formatter_instance){
    return formatter_instance->buffer;
}

void LW_Formatter_Print_Contents(Light_Weight_Formatter * formatter_instance){
    printf("Formatter Buffer Contents: \r\n");

    for(uint8_t i = 0; i < formatter_instance->elements; i++){
        printf("[%02X]", formatter_instance->buffer[formatter_instance->elements - 1 - i]);
    }
    printf("\r\n================");
}

void LW_Formatter_Print_Contents_Hex_Raw(Light_Weight_Formatter * formatter_instance){
    printf("Formatter Buffer Contents: \r\n");

    for(uint8_t i = 0; i < formatter_instance->elements; i++){
        //printf("%02X", formatter_instance->buffer[formatter_instance->elements - 1 - i]);
        printf("%02X", formatter_instance->buffer[i]);
    }
    printf("\r\nBytes Used: %lu", formatter_instance->elements);
    printf("\r\n================\r\n");
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