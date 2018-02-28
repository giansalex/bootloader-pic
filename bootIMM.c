/*
  Name:  Bootloader PIC16f887 para Windows Phone 8.1
  Author: IMM Corporation
  Date:   18/06/14 19:21
  Description: 
               -Bootloader de 256 bytes de Memoria situados al final de la Flash
               -Reubiacion de los vectores de reset e interrupcion apartir de la direccion 0x0D
               -Las aplicaiones de usuario solo deben incluir el archivo de cabecera "bootIMM.h"
               -Se debe definir USE_START como 1 para usar el modulo USART, preconfigurada del Bootloader(38400 baudios)
*/
#include <main.h>
#define LOADER_SIZE   0x100// Tamaño del Bootloader  0xe8
#define LOADER_END    getenv("PROGRAM_MEMORY")-1
#define LOADER_ADDR   LOADER_END -LOADER_SIZE
#byte RX = 0x1A 
#define START_PROGRAM 0X010
//#build(reset=0x00:0x03)   // Inicio de programa
/**/
#org START_PROGRAM,0x7ff // Bloque 1 de FLASH
void application(void)  {
while(true);
} 

#ORG LOADER_ADDR+10, LOADER_END auto=0 default

#use delay(clock=8M)
#use rs232(UART1,baud=19200,bits=8,stop=1)

#include "main_bootloader.h"

void main()
{
   int8 ACUM=0;
   DO{  // Esperar un tiempo de 2 seg
   if(kbhit()) {
   #ASM
   MOVF RX,W
   #ENDASM
   real_load_program(); 
   ACUM=254;
   }
   delay_ms(15);
   }WHILE(++ACUM<255);
   #ASM
   CLRF 0x0A
   goto START_PROGRAM 
   #ENDASM
  
}

/**/
#ORG default
// Para interrupciones futuras 
#int_global

void isr(void) {
 /*
 // Ir a la funcion de interrrupcion ,saltandose la lectura del pc
 // la cual es 7 posiciones mas del inicio de Interrupt
 */
#ASM
 MOVWF 0X7F   // GUARDA W
 SWAPF 0X03,W // PASA STATUS(0X03)CON NIBLES CAMBIADOS A W
 CLRF  0X03   // BORRA STATUS
 MOVWF 0X21   // GUARDA STATUS
 MOVF  0X0A,W // PASA PC counter a W
 MOVWF 0x20   // Guarda PC counter
 CLRF  0X0A   // BORRA EL PC, Byte supeior
 GOTO  START_PROGRAM + 11  // SALTA A FUNCION INTERRUPT, SALTANDO LA RUTINA ANTERIOR PROPIA DE TODA INTERRUPCION
 // RETORNA DE LA INTERRUPCION
#ENDASM
  //   jump_to_isr(START_PROGRAM+4*(getenv("BITS_PER_INSTRUCTION")/8)); // Ir a la funcion de interrrupcion ,saltandose la lectura del pc                                                                     // la cual es 7 posiciones mas del inicio de Interrupt
 
} 

