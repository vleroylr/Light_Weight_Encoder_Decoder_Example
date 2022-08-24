/**
 * @file Light_Weigth_Formatter.h
 * @author Victor Le Roy Brito (vleroy@tekroy.cl)
 * @brief 
 * @version 0.1
 * @date 2022-08-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _LIGHT_WEIGHT_FORMATTER
#define _LIGHT_WEIGHT_FORMATTER

#include <stdint.h>
#include <stdio.h>

//****************************************
#define LW_FORMATTER_BUFFER_SIZE 128
typedef struct{
    uint8_t buffer[LW_FORMATTER_BUFFER_SIZE];
    size_t elements;
}Light_Weight_Formatter;
/**
 * @brief Function Prototypes
 * 
 * @param formatter_instance 
 */

/**
 * @brief Initializes the formater Struct
 * 
 * @param formatter_instance 
 */
void LW_Formatter_Init(Light_Weight_Formatter * formatter_instance);

/**
 * @brief Interface for adding data to the formatter's buffer, Specialized by macros
 * 
 * @param formatter_instance 
 * @param base 
 * @param bytes_number 
 */
void LW_Formatter_Add_Variable_Interface(Light_Weight_Formatter * formatter_instance, uint8_t * base, size_t bytes_number);

/**
 * @brief Returns a pointer to the formatter's buffer
 * 
 * @param formatter_instance 
 * @return uint8_t* 
 */
uint8_t * LW_Formatter_Get_Buffer(Light_Weight_Formatter * formatter_instance);

/**
 * @brief Prints the formatter data in human readable format
 * 
 * @param formatter_instance 
 */
void LW_Formatter_Print_Contents(Light_Weight_Formatter * formatter_instance);

/**
 * @brief Prints the formatter data in Hex format
 * 
 * @param formatter_instance 
 */
void LW_Formatter_Print_Contents_Hex_Raw(Light_Weight_Formatter * formatter_instance);

/**
 * @brief Resets the number of elements in the formatter
 * 
 * @param lw_decoder 
 */
void LW_Formatter_Restart(Light_Weight_Formatter * lw_decoder);
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
#endif