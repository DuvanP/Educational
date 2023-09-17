/*
   Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
   
   Doceavo Proyecto Librería "TODO" 
   
    Sketch para crear cinco controles midi, en esta
    ocasión se trata de 2 interrupotres y un pulsador para
    controlar algún valor Midi que deseemos y
    2 potenciometros para controlar algun
    volumen.

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

int Sw1 = 14;   // Interruptor 1
int Po1 = 15;   // Potenciometro 1
int Sw2 = 16;   // Interruptor 2
int Po2 = 17;   // Potenciometro 2
int Sw3 = 18;   // Pulsador 1

void setup() {  
  
  Serial.begin(31250);  // Se ajusta la velocidad de comunicacion MIDI:

  H.ActivarResistencia(Sw1);  // Activamos la resistencia interna en el pin 14 de arduino
  H.ActivarResistencia(Sw2);  // Activamos la resistencia interna en el pin 15 de arduino
  H.ActivarResistencia(Sw3);  // Activamos la resistencia interna en el pin 16 de arduino

  
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
                                                    // Interruptor 1 ---> Controlador Midi 16    
  if(VaSw3 == true) {  H.Pulsador3(1, 18, 40); }    // Interruptor 2 ---> Controlador Midi 17
  else{ H.NoPulsador3(); }                          // Interruptor 3 ---> Controlador Midi 18  
                                                    // Potenciometro 1 ---> Controlador Midi 19
  H.Potenciometro1(1,19,VaPo1);                     // Potenciometro 2 ---> Controlador Midi 20
  
  H.Potenciometro2(1,20,VaPo2);
  
}




