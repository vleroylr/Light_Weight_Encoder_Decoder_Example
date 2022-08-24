
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Light_Weight_Formatter/Light_Weigth_Formatter.h"

float pi = (float)3.1415548794;
char str[] = "ola k ase";
char * str_2 = "hace debuggging o k ase";
uint8_t u = 255 ;

void print_memory(uint8_t * base, uint8_t length);

void print_memory(uint8_t * base, uint8_t length){
    printf("Memory Contents starting @ %p, %u bytes ahead: ", (void *)base, length);

    for(uint8_t i = 0; i < length; i++){
        printf("[%02X]", base[i]);
        if(i < length - 1){
            printf(",");
        }
    }
    printf("\r\n");
}

uint8_t memory_compare(uint8_t * m1, uint8_t * m2, size_t len){
    uint8_t * aux = m1 + len;
    while(m1 <  aux){
        if(*m1++ != *m2++) return 0;
    }
    return 1;
}


/**
 * @brief All functions prefixes start with LW_Formatter (short for Light_Weight_Formatter)
 * 
 */

/**
 * @brief Light_Weight_Formatter Struct Define
 * 
 */
#define LW_FORMATTER_BUFFER_SIZE 128
typedef struct{
    uint8_t buffer[LW_FORMATTER_BUFFER_SIZE];
    size_t elements;
}Light_Weight_Formatter;
//****************************************

#define LW_DECODER_BUFFER_SIZE 128
typedef struct{
    uint8_t * buffer;
    size_t buffer_size;
    size_t read_pointer;
}Light_Weight_Decoder;

Light_Weight_Decoder Lw_Decoder;

/**
 * @brief Function Prototypes
 * 
 * @param formatter_instance 
 */

void LW_Formatter_Init(Light_Weight_Formatter * formatter_instance);
void LW_Formatter_Add_Variable_Interface(Light_Weight_Formatter * formatter_instance, uint8_t * base, size_t bytes_number);
uint8_t * LW_Formatter_Get_Buffer(Light_Weight_Formatter * formatter_instance);
void LW_Formatter_Print_Contents(Light_Weight_Formatter * formatter_instance);
void LW_Formatter_Print_Contents_Hex_Raw(Light_Weight_Formatter * formatter_instance);
void LW_Decoder_Print_Contents_Hex_Raw(Light_Weight_Decoder * decoder_instance);
/**
 * @brief Macros
 * 
 */

/**
 * @name LW_Formatter_Add_N_Bytes
 * @brief Adds the contents of the specified variable to the formatter instance buffer
 * 
 */

#define LW_Formatter_Add_Variable(formatter, var) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)&var, sizeof(var))

#define LW_Formatter_Add_1_Byte_Signed(formatter, var) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)&var, 1)
#define LW_Formatter_Add_1_Byte_Unsigned(formatter, var) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)&var, 1)

#define LW_Formatter_Add_2_Byte_Signed(formatter, var) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)&var, 2)
#define LW_Formatter_Add_2_Byte_Unsigned(formatter, var) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)&var, 2)

#define LW_Formatter_Add_4_Byte_Signed(formatter, var) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)&var, 4)
#define LW_Formatter_Add_4_Byte_Unsigned(formatter, var) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)&var, 4)

#define LW_Formatter_Add_Float(formatter, var) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)&var, 4)
#define LW_Formatter_Add_Double(formatter, var) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)&var, 8)
#define LW_Formatter_Add_Str(formatter, var, size) LW_Formatter_Add_Variable_Interface(formatter, (uint8_t *)var, size)
//#define LW_Formatter_Add_Array(formatter, var) LW_Formatter_Add_Variable(formatter, var)
void LW_Decoder_Print_Contents_Hex_Raw(Light_Weight_Decoder * decoder_instance);

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

#define debug_memory_contents(var) print_memory((uint8_t *)(&var), sizeof(var));

Light_Weight_Formatter IOT_Formatter;
Light_Weight_Formatter Specialized_Formatter;



typedef struct{
    uint8_t u_byte;
    uint32_t u_4byte;
    float f;
    char * string;
    char * string_2;
    double d;
}IOT_Message;
IOT_Message iot_message_decoded;
IOT_Message iot_message_encoder;

void IOT_Message_Print(IOT_Message iot_message){
    printf("IOT Message Contents: \r\n");
    printf("%u\t%u\t%f\t%s\t%f\t%s\r\n", iot_message.u_byte, iot_message.u_4byte, iot_message.f, iot_message.string, iot_message.d, iot_message.string_2);
    printf("==========\r\n");
}

void LW_Decoder_Init(Light_Weight_Decoder * lw_decoder, uint8_t * buffer, size_t buffer_size){
    lw_decoder->buffer = buffer;
    lw_decoder->buffer_size = buffer_size;
    lw_decoder->read_pointer = 0;
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

void LW_Formatter_Restart(Light_Weight_Formatter * lw_decoder){
    lw_decoder->elements = 0;
}

int main(){

    //LW_Formatter_Init(&IOT_Formatter);
    LW_Formatter_Init(&Specialized_Formatter);

    uint8_t * decoder_buffer_pointer = Specialized_Formatter.buffer;
    size_t decoder_buffer_size = Specialized_Formatter.elements;

    LW_Decoder_Init(&Lw_Decoder, decoder_buffer_pointer, decoder_buffer_size);

    for(uint8_t i = 0; i < 3 ; i++){

        

        iot_message_encoder.u_byte = 123 + i;
        iot_message_encoder.u_4byte = 4519871;
        iot_message_encoder.string = str;
        iot_message_encoder.d = 45133.645987;
        iot_message_encoder.f = 3.1415548794;
        iot_message_encoder.string_2 = str_2;
        /*
        LW_Formatter_Add_Variable(&IOT_Formatter, i);
        LW_Formatter_Add_Variable(&IOT_Formatter, u);
        LW_Formatter_Add_Variable(&IOT_Formatter, pi);
        LW_Formatter_Add_Variable(&IOT_Formatter, str);
        LW_Formatter_Add_Variable(&IOT_Formatter, d);
        */

        //Codificacion
        printf("Encoding IOT Message...\r\n");
        IOT_Message_Print(iot_message_encoder);
        
        LW_Formatter_Restart(&Specialized_Formatter);
        LW_Formatter_Add_1_Byte_Unsigned(&Specialized_Formatter, iot_message_encoder.u_byte);
        LW_Formatter_Add_4_Byte_Unsigned(&Specialized_Formatter, iot_message_encoder.u_4byte);
        LW_Formatter_Add_Float(&Specialized_Formatter, iot_message_encoder.f);
        LW_Formatter_Add_Str(&Specialized_Formatter, iot_message_encoder.string, strlen(iot_message_encoder.string) + 1);
        LW_Formatter_Add_Double(&Specialized_Formatter, iot_message_encoder.d);
        LW_Formatter_Add_Str(&Specialized_Formatter, iot_message_encoder.string_2, strlen(iot_message_encoder.string_2) + 1);

        //Decodificacion
        printf("Decoding IOT Message...\r\n");
        LW_Decoder_Restart(&Lw_Decoder);
        iot_message_decoded.u_byte = LW_Decoder_Decode_1_Byte_Unsigned(&Lw_Decoder);
        iot_message_decoded.u_4byte = LW_Decoder_Decode_4_Byte_Unsigned(&Lw_Decoder);
        iot_message_decoded.f = LW_Decoder_Decode_Float(&Lw_Decoder);
        iot_message_decoded.string = LW_Decoder_Decode_String(&Lw_Decoder);
        iot_message_decoded.d =  LW_Decoder_Decode_Double(&Lw_Decoder);
        iot_message_decoded.string_2 = LW_Decoder_Decode_String(&Lw_Decoder);

        IOT_Message_Print(iot_message_decoded);

        //LW_Formatter_Print_Contents_Hex_Raw(&IOT_Formatter);
        LW_Formatter_Print_Contents_Hex_Raw(&Specialized_Formatter);
        LW_Decoder_Print_Contents_Hex_Raw(&Lw_Decoder);
        
        if(memory_compare(Specialized_Formatter.buffer, Lw_Decoder.buffer, Lw_Decoder.read_pointer)){
            printf("Encoded data succesfully decoded!");
        }else{
            printf("Data error");
        }
    }
}