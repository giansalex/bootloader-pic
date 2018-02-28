/*

  #include "bootIMM.h"  
  Debe incluirse en todos los programas que seran cargados por el Bootloader
  para Pic 16f887

*/
#include <16F887.h>
#device adc=10

#FUSES NOWDT,NODEBUG                    //No Watch Dog Timer
#FUSES HS,INTRC_IO,MCLR                    //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES PUT,NOPROTECT                              //Power Up Timer
#FUSES BROWNOUT,BORV21,BROWNOUT_NOSL    //No brownout reset
#FUSES NOLVP   

#use delay(clock=8M)
#if USE_USART
#use rs232(UART1,baud=19200,bits=8,stop=1)
#endif
// Reservando Recursos para mantener el Bootloader

#define SIZE_BOOT 0x100 // 256 bytes , con Rx
#Define LOAD_STAR 0x00F                           // Inicio de Programa de usuario
#define LOAD_END  getenv("PROGRAM_MEMORY")-1
#build(reset=LOAD_STAR+1, interrupt=LOAD_STAR+5)// Remapeando vector Reset de Usuario e interrupt
#org 0, LOAD_STAR{}                             //Reserva memoria para reset de Bootloader(4 Words)
#org LOAD_END-SIZE_BOOT,LOAD_END {}                           //Reserva Memoria de Bootloader (0xE8)
//Size BootIMM 0x1fff0x100
 
