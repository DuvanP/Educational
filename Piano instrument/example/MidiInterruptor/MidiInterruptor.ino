/*
   Desarrollado por Creatvra S.A.S. - Ing Duvan Camilo Puerto - Bogota - Colombia
   
   Onceavo Proyecto Librería "TODO" 
   
    Sketch para crear un control midi, en esta
    ocasión se trata de un interruptor para
    controlar algún valor Midi que deseemos,
    como por ejemplo activar la batería de una
    pista.

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



   Conecta un interruptor de la siguiente manera:

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

int Sw1 = 14;   // Interruptor en el pin 14 digital o en el Pin 0 análogo (Son lo mismo)


void setup() {  
  
  Serial.begin(31250);  // Se ajusta la velocidad de comunicación MIDI:
  
  H.ActivarResistencia(Sw1);  // Activamos la resistencia interna en el pin 14 de arduino

  
  H.ModoPiano(Apagar_Piano, Apagar_Sinte, Activar_Midi);   // Esta función es la más importante, 
                                                            // Controla el sistema completo

}

void loop() {
  

  int VaSw1 = digitalRead(Sw1);   // Leemos el valor del interruptor
  
  if(VaSw1 == true) {  H.Pulsador1(1, 16, 40); }    // Pulsador1 y Nopulsador1 son las funciones
  else{ H.NoPulsador1(); }                      // que se encargan de comunicarse con el programa
                                                /* Daw LMMS, por esta razon es importante entender
                                                   la estructura:


                                                   Pulsador1(  Canal Midi, Controlador, Intensidad) ;

                                                   En este caso, vamos a usar el canal 1, el controlador 16
                                                   y en la intensidad de 40 para indicar un valor alto.
                                                    
                                                   De esta misma forma debemos configurar en LMMS los valores
                                                   Midi
                                                   
                                                */    
                                                
  }




