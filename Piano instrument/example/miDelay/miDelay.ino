/*
   Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
   
   Septimo Proyecto Librería "TODO" 
    Sketch para controlar el delay del piano
    por medio de un potenciometro.

    El delay es un efecto de sonido que produce 
    repeticiones en una nota. Para poder usarlo
    es necesario que el sustain este desactivado


    Para controlar el tiempo del Delay se puede usar
    Un potenciometro conectado a alguno de los canales
    analogos, como se ve en el siguiente circuito:

                                       _____
    GND -------  --/     \
    Pin -------  --  (O)  |   Potenciometro
    5v  -------  --\_____/


  Para mayor informacion consultar la siguiente pagina web
        XXXXXXXXXXXXXXXXXX


*/




#include <TODO.h>

TODO H;   // Se crea un objeto llamado H para usar el piano


int Parlante1 = 10;
int Parlante2 = 11;
int PinEnvio  = 12;
int Cali = 55;  // Se aconseja dejar este valor a menos que el sistema falle, Mirar ejemplo Calibración

int Nivel;

int Pot1 = 17;   // Potenciometro1 en el pin 3 analogo o en el pin 17 usado como analogo 


void setup() {  
  
  
  H.Fiesta(Parlante1,Parlante2,PinEnvio);  // Calibra el pin de parlante1, parlante2, y senPin
  H.Calibracion(Cali);                     // Esta función calibra el sensor
  
  H.Tecla1( 2,  Nota_Do_4   );               // Le asignamos el pin 2  de recepción y una frecuencia de Do4.  
  H.Tecla2( 3,  Nota_Re_4   );               // Le asignamos el pin 3  de recepción y una frecuencia de Re4.  
  H.Tecla3( 4,  Nota_Mi_4   );               // Le asignamos el pin 4  de recepción y una frecuencia de Mi4.  
  H.Tecla4( 5,  Nota_Fa_4   );               // Le asignamos el pin 5  de recepción y una frecuencia de Fa4.  
  H.Tecla5( 6,  Nota_Sol_4  );               // Le asignamos el pin 6  de recepción y una frecuencia de Sol4.  
  H.Tecla6( 7,  Nota_La_4   );               // Le asignamos el pin 7  de recepción y una frecuencia de La4.  
  H.Tecla7( 8,  Nota_Si_4   );               // Le asignamos el pin 8  de recepción y una frecuencia de Si4.  
  H.Tecla8( 9,  Nota_Do_5   );               // Le asignamos el pin 9  de recepción y una frecuencia de Do5.


  H.ModoPiano(Activar_Piano, Activar_Sinte, Apagar_Midi);   // Esta función es la más importante, 
                                                            // Controla el sistema completo

  H.Syntetizador(Apagar_Sustain , Apagar_Vibrato , Activar_Delay);  // Esta función controla al sintetizador
                                                                      
}

void loop() {


  Nivel = analogRead(Pot1);   // Leemos el potenciometro desde el pin analogo  
  H.TiempoDelay(Nivel);    // Esta funcion permite controlar el efecto del Vibrato

     
    // La rutina para el piano es sencilla, si se oprime alguna de las teclas del piano
    // entonces sonará la nota pero si no se oprime se debe apagar todo
  if( H.Nota1() | H.Nota2() | H.Nota3() | H.Nota4() | H.Nota5() | H.Nota6() | H.Nota7() | H.Nota8() )
  {

   H.playPiano();

  }   

  else{H.noTono();}

}




