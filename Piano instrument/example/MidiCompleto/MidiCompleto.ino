/*
   Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
   
   Treceavo Proyecto Librería "TODO" 
   
    Sketch para usar todo el sistema midi
    lo que incluye el piano midi, tres interruptores
    y dos potenciometros.

      1. Conectar el arduino al computador
      2. Subir este sketck al arduino.
      3. Desconectar el arduino del computador
      4. Mover el seleccionador llamado Midi On
         que esta en la shield Midi que viene con
         el kit de música.
      5. Conectar el Arduino al computador de nuevo
         ahora, el computador reconocerá el arduino
         como un dispositivo midi y no como un 
         arduino natural, por esta razón para poder 
         cargar otro nuevo código al arduino necesitaras
         cambiar el seleccionar a modo Arduino On que se
         encuentra en la shield.
      6. Abrir un programa DAW como LMMS aunque también
         funcionan en otros como por ejemplo Ableton, 
         GarageBand, Ardour, etc.
      7. Configura algún instrumento midi en el software
         como MOCO LUFA el cual es el nombre midi de arduino

      Nota: DAW = Digital Audio Workstation
                = Estación de trabajo de audio digital



   Conecta los interruptores de la siguiente manera:

            _[]_
    pin -----  ----|
                   |
                   |
                   Gnd

    Los interruptores y pulsadores necesitan una
  resistencia para que funcionen correctamente, esta 
  se utiliza para impedir que el sistema tenga errores. 
  Con el fin de evitar usar mas componentes electrónicos
  se usará la resistencia interna de los pines digitales 
  llamada:
    
    "Resistencia de Pull UP"

    Esta se activa con la función ActivarResistencia.


 La librería permite usar solo 6 interruptores.


     Para mayor información dirigirse a la página "XXXXXXXXXX"


*/



#include <TODO.h>

TODO H;   // Se crea un objeto llamado H para usar el piano

int Parlante1 = 10;
int Parlante2 = 11;
int PinEnvio  = 12;
int Cali = 55;  // Se aconseja dejar este valor a menos que el sistema falle, Mirar ejemplo 2 "Calibración"

int Sw1 = 14;   // Interruptor 1
int Sw2 = 15;   // Interruptor 2
int Sw3 = 16;   // Interruptor 3
int Po1 = 17;   // Potenciometro 1
int Po2 = 18;   // Potenciometro 2

void setup() {  
  
  Serial.begin(31250);  // Se ajusta la velocidad de comunicacion MIDI:

  H.ActivarResistencia(Sw1);  // Activamos la resistencia interna en el pin 14 de arduino
  H.ActivarResistencia(Sw2);  // Activamos la resistencia interna en el pin 15 de arduino
  H.ActivarResistencia(Sw3);  // Activamos la resistencia interna en el pin 16 de arduino

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

  int VaSw1 = digitalRead(Sw1);   // Leemos los pines analogos y digitales de los interruptores
  int VaSw2 = digitalRead(Sw2);   // y pulsadores
  int VaSw3 = digitalRead(Sw3);
  int VaPo1 = analogRead(Po1);
  int VaPo2 = analogRead(Po2);

                                                    // las funciones Pulsador, Nopulsador y
  if(VaSw1 == true) {  H.Pulsador1(1, 16, 40); }    // Potenciometro, son las que se comunican
  else{ H.NoPulsador1(); }                          // con el programa DAW LMMS. Para mayor    
                                                    // informacion, lea los proyectos diez y
  if(VaSw2 == true) {  H.Pulsador2(1, 17, 40); }    // once.
  else{ H.NoPulsador2(); }                        
                                                    // Interruptor 1 ---> 16    
  if(VaSw3 == true) {  H.Pulsador3(1, 18, 40); }    // Interruptor 2 ---> 17
  else{ H.NoPulsador3(); }                          // Interruptor 3 ---> 18  
                                                    // Potenciometro 1 ---> 19
  H.Potenciometro1(1,19,VaPo1);                     // Potenciometro 2 ---> 20
  
  H.Potenciometro2(1,20,VaPo2);



      // La rutina para el piano es sencilla, si se oprime alguna de las teclas del piano
    // entonces sonará la nota pero si no se oprime se debe apagar todo
  if( H.Nota1() | H.Nota2() | H.Nota3() | H.Nota4() | H.Nota5() | H.Nota6() | H.Nota7() | H.Nota8() )
  {

   H.playPiano();

  }   

  else{H.noTono();}
  
}




