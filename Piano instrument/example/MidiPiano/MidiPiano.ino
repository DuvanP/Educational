
/*
   Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
   
   Noveno Proyecto Librería "TODO" 
   
    Sketch para crear un sencillo piano Midi.
    Para poder utilizar el sistema Midi debes
    hacer lo siguiente:

      1. Conectar el arduino al computador
      2. Subir este sketck al arduino.
      3. Desconectar el arduino del computador
      4. Mover el seleccionador llamado Midi On
         que esta en la shield Midi que viene con
         el kit de música.
      5. Conectar el Arduino al computador de nuevo
         ahora, el computador reconocerá el arduino
         como un dispositivo midi y no como un 
         arduino natural, por esta razon para poder 
         cargar otro nuevo código al arduino necesitaras
         cambiar el seleccionar a modo Arduino On que se
         encuentra en la shield.
      6. Abrir un programa DAW como LMMS aunque también
         funcionan en otros como por ejemplo Ableton, 
         GarageBand, Ardour, etc.
      7. Configura algun instrumento midi en el software
         como MOCO LUFA el cual es el nombre midi de arduino


     Para mayor información dirigirse a la página "XXXXXXXXXX"


*/



#include <TODO.h>

TODO H;   // Se crea un objeto llamado H para usar el piano


int Parlante1 = 10;
int Parlante2 = 11;
int PinEnvio  = 12;
int Cali = 55;  // Se aconseja dejar este valor a menos que el sistema falle, Mirar ejemplo 2 "Calibración"



void setup() {  
  
  Serial.begin(31250);  // Se ajusta la velocidad de comunicación MIDI:


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

  H.VolumenMidi(40);      // Esta función controla el volumen Midi del piano
  H.CanalMidiPiano(2);    // Esta función controla el Canal midi
  
  H.ModoPiano(Apagar_Piano, Apagar_Sinte, Activar_Midi);   // Esta función es la más importante, 
                                                            // Controla el sistema completo

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




