/*
 *  Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
 *  
 *  Primer Proyecto Libreria "TODO" 
 *  
 *  
 *  Este es un piano Capacitivo que funciona con trozos de algun metal
 *  y el contacto de los dedos.
 * 
 *  Tiene la capacidad de reproducir dos sonidos al mismo tiempo
 *  pero ten cuidado por que si intentas tocar 3 sonidos al mismo
 *  tiempo el sistema tendra errores.
 *  
 *  Para mayor informacion dirigirse a la pagina "XXXXXXXXXX"
 *  
 */




#include <TODO.h>

TODO H; // Se crea un objeto llamado H para usar el piano

int Parlante1 = 10;       
int Parlante2 = 11;       
int PinEnvio  = 12;     // Este pin es necesario para que funcione la libreria capacitiva


void setup() {  

            
  H.Fiesta(Parlante1,Parlante2,PinEnvio);  // Configurá los pines del parlante1, parlante2, y senPin
  
  H.Tecla1( 2,  Nota_Do_4   );               // Le asignamos el pin 3  de recepcion y una frecuencia de Do4.  
  H.Tecla2( 3,  Nota_Re_4   );               // Le asignamos el pin 4  de recepcion y una frecuencia de Re4.  
  H.Tecla3( 4,  Nota_Mi_4   );               // Le asignamos el pin 5  de recepcion y una frecuencia de Mi4.  
  H.Tecla4( 5,  Nota_Fa_4   );               // Le asignamos el pin 6  de recepcion y una frecuencia de Fa4.  
  H.Tecla5( 6,  Nota_Sol_4  );               // Le asignamos el pin 7  de recepcion y una frecuencia de Sol4.  
  H.Tecla6( 7,  Nota_La_4   );               // Le asignamos el pin 8  de recepcion y una frecuencia de La4.  
  H.Tecla7( 8,  Nota_Si_4   );               // Le asignamos el pin 9  de recepcion y una frecuencia de Si4.  
  H.Tecla8( 9, Nota_Do_5   );               // Le asignamos el pin 10 de recepcion y una frecuencia de Do5.

  H.ModoPiano(Activar_Piano, Apagar_Sinte, Apagar_Midi);   // Esta funcion es la mas importante, Controla el sistema completo
                                                         // ella tiene tres configuraciones
                            /*              
                                  H.ModoPiano( Control de Piano, Control de Sintetizador, Control de MIDI );

                                  Se activan con la palabra     Activar_Piano, Activar_Sinte, Activar_Midi
                                  Se desactiva con la palabra   Apagar_Piano,  Apagar_Sinte,  Apagar_Midi
                           */  


} 

void loop() {


    // La rutina para el piano es sencilla, si se oprime alguna de las teclas del piano
    // entonces sonará la nota pero si no se oprime se debe apagar todo
  if( H.Nota1() | H.Nota2() | H.Nota3() | H.Nota4() | H.Nota5() | H.Nota6() | H.Nota7() | H.Nota8() )
  {

   H.playPiano();

  }   

  else{H.noTono();}
 
}




