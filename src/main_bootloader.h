//bootloader code
#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

#define __BOOTLOADER_INCLUDED__ TRUE



#endif
//BOOTLOADER AT END
// LOADER_END - This is the end of the general purpose bootload code.
#ifndef LOADER_END
#define LOADER_END      getenv("PROGRAM_MEMORY")-1
#define LOADER_ADDR LOADER_END-LOADER_SIZE
#endif

#define BUFFER_LEN_LOD 44


#define ACKLOD 0x06
#define XON    0x10
#define XOFF   0x11

#define getc_ getc
//#ORG LOADER_ADDR+10, LOADER_END auto=0 default
/*
char getc_(){
 char data=getc();
 putc('f');
 return data;
}*/
void real_load_program (void)
{
   putc('>');
   int1  done=FALSE;
   int8  line_type;
   int16 addr;
   int8  l_addr,h_addr;
   int8  i, count;
   int8  data[16];
   
   while (!done)  // Loop until the entire program is downloaded
   {
      count=getc_();  // Numero de bytes a escribir
      //addr /= 2;  PIC16 uses word addresses Por PC enviado
      H_addr=getc_(); // byte ALTO
      L_addr=getc_(); // Byte BAJO
      line_type=getc_();  // Tipo de  linea
      
      for(i=0;i<count;i++)//maximo de 16 bytes = 8 word
      data[i]=getc_();
      
      addr=make16(h_addr,l_addr);
         if (line_type == 1) 
            done = TRUE;
         if (line_type == 0)                   
          write_program_memory(addr, data, count);
          // putc(0x10); // Corroborando recepcion;
      }
   putc('K');
   getch(); // Recibe char para iniciar
}

