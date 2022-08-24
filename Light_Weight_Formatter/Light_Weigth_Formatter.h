#ifndef _LIGHT_WEIGHT_FORMATTER
#define _LIGHT_WEIGHT_FORMATTER

#include <stdint.h>
#include <stdio.h>
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
#endif