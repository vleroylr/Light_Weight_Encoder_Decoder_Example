/**
 * @file main.c
 * @author Victor Le Roy Brito (vleroy@tekroy.cl)
 * @brief 
 * @version 0.1
 * @date 2022-08-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "Light_Weight_Formatter/Light_Weigth_Formatter.h"
#include "Light_Weight_Decoder/Light_Weight_Decoder.h"

/*********************************************/
/** USAGE EXAMPLE **/
/*********************************************/

//  1) Define a Struct containing all the data of the message that you will send/receive (encode and decode)
typedef struct{
    uint8_t u_byte;
    uint32_t u_4byte;
    float f;
    char * string;
    char * string_2;
    double d;
}IOT_Message;

//  2)Create instances of the struct as if it was a message holder
IOT_Message iot_message_decoded; //Create a message holder with the struct where you will be receiving the data
IOT_Message iot_message_encoder; //Create a message holder with the struct where you will be sending the data

//  3) Create the formatter or decoder
Light_Weight_Formatter Specialized_Formatter;   //Create a Formatter from where you will be sending the data
Light_Weight_Decoder Lw_Decoder;                //Create a Decoder from where you will be receiving the data

/*********************************************/


/*********************************************/
/** Some "Debugging" Tools for the example **/
/*********************************************/

/**
 * 
 * @brief Prints the memory contents in HEX format from addr base untill length bytes
 * 
 * @param base 
 * @param length 
 * 
 */
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

/**
 * @brief Compares the memory contents of two locations starting from address m1 untill len
 * 
 * @param m1 
 * @param m2 
 * @param len 
 * @return uint8_t 
 */
uint8_t memory_compare(uint8_t * m1, uint8_t * m2, size_t len);

uint8_t memory_compare(uint8_t * m1, uint8_t * m2, size_t len){
    uint8_t * aux = m1 + len;
    while(m1 <  aux){
        if(*m1++ != *m2++) return 0;
    }
    return 1;
}

/**
 * @brief Prints memory content of the variable var
 * 
 */
#define debug_memory_contents(var) print_memory((uint8_t *)(&var), sizeof(var));

/**
 * @brief Prints the contents of the IOT_Message Struct Passed by value
 * 
 * @param iot_message 
 */
void IOT_Message_Print(IOT_Message iot_message){
    printf("IOT Message Contents: \r\n");
    printf("%u\t%u\t%f\t%s\t%f\t%s\r\n", iot_message.u_byte, iot_message.u_4byte, iot_message.f, iot_message.string, iot_message.d, iot_message.string_2);
    printf("==========\r\n");
}
/*********************************************/


/*********************************************/
/** Some data used in the example, you can change the values **/
/*********************************************/
float pi = (float)3.1415548794;
char str[] = "ola k ase";
char * str_2 = "hace debuggging o k";
uint8_t u = 255 ;
/*********************************************/

int main(){
    
    LW_Formatter_Init(&Specialized_Formatter); //Initialize the formatter

    uint8_t * decoder_buffer_pointer = Specialized_Formatter.buffer;
    size_t decoder_buffer_size = Specialized_Formatter.elements;

    LW_Decoder_Init(&Lw_Decoder, decoder_buffer_pointer, decoder_buffer_size);

    for(uint8_t i = 0; i < 3 ; i++){

        iot_message_encoder.u_byte = 123 + i*1000;
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

        //Encode
        printf("Encoding IOT Message...\r\n");
        IOT_Message_Print(iot_message_encoder);
        
        LW_Formatter_Restart(&Specialized_Formatter);
        LW_Formatter_Add_1_Byte_Unsigned(&Specialized_Formatter, iot_message_encoder.u_byte);
        LW_Formatter_Add_4_Byte_Unsigned(&Specialized_Formatter, iot_message_encoder.u_4byte);
        LW_Formatter_Add_Float(&Specialized_Formatter, iot_message_encoder.f);
        LW_Formatter_Add_Str(&Specialized_Formatter, iot_message_encoder.string, strlen(iot_message_encoder.string) + 1);   //For Strings it is necesary to add strlen to the 
        LW_Formatter_Add_Double(&Specialized_Formatter, iot_message_encoder.d);                                             //string and + 1 to add the null character to the buffer
        LW_Formatter_Add_Str(&Specialized_Formatter, iot_message_encoder.string_2, strlen(iot_message_encoder.string_2) + 1); //Should it be hardcoded to the library?, you tell me :)

        //Decode
        printf("Decoding IOT Message...\r\n");
        LW_Decoder_Restart(&Lw_Decoder);
        iot_message_decoded.u_byte = LW_Decoder_Decode_1_Byte_Unsigned(&Lw_Decoder);
        iot_message_decoded.u_4byte = LW_Decoder_Decode_4_Byte_Unsigned(&Lw_Decoder);
        iot_message_decoded.f = LW_Decoder_Decode_Float(&Lw_Decoder);
        iot_message_decoded.string = LW_Decoder_Decode_String(&Lw_Decoder);
        iot_message_decoded.d =  LW_Decoder_Decode_Double(&Lw_Decoder);
        iot_message_decoded.string_2 = LW_Decoder_Decode_String(&Lw_Decoder);
        
        //Notice how you should encode and decode in the same order and assigning each element in the same order
        //As the struct's members are defined
        
        IOT_Message_Print(iot_message_decoded); //Prints the decoded message

        LW_Formatter_Print_Contents_Hex_Raw(&Specialized_Formatter);    //Prints the raw contents in HEX Format of the formater buffer
        LW_Decoder_Print_Contents_Hex_Raw(&Lw_Decoder);                 //Prints the raw contents in HEX Format of the decoder buffer
        
        //If you decoded correctly the messages will print the same content results with the same byte size
        
        //Now we compare the memory contents
        if(memory_compare(Specialized_Formatter.buffer, Lw_Decoder.buffer, Lw_Decoder.read_pointer)){
            //If they are the same then congrats!
            printf("Encoded data succesfully decoded!");
        }else{
            //If they are not the same then:
            //  1) Check that you are encoding and decoding correctly
            //  2) If its a bug then please open an issue on GitHub
            printf("Data error");
        }
    }
}