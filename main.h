#include <16F887.h>
#device adc=10

#FUSES NOWDT,NODEBUG                    //No Watch Dog Timer
#FUSES HS,INTRC_IO,MCLR                    //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES PUT,NOPROTECT                              //Power Up Timer
#FUSES BROWNOUT,BORV21,BROWNOUT_NOSL    //No brownout reset
#FUSES NOLVP   


