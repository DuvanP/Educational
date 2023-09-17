
// Incluimos las librerias del sensor infrarrojo 
// y del servomotor.

#include <IRremote.h>
#include <Servo.h>


// Creamos 5 variables para el programa

int RECV_PIN = 11;    // Pin del Sensor infrarrojo
int Pin_servo = 9;    // Pin del servomotor
int VELOCIDAD = 250;  // Indicamos la velocidad de la moto
int GIRO = 90;        // Indicamos el giro a 90 grados
int ENCENDIDO = 0;    // Variable para guardar el estado de la moto.


// Estos son los codigos de mi control remoto. Escribe los
// Codigos de tu control remoto

long ARRIBA      = 0xFF18E7;
long ABAJO       = 0xFF4AB5;
long DERECHA     = 0xFF5AA5;
long IZQUIERDA   = 0xFF10EF;
long CENTRO      = 0xFF38C7;


// Indicamos configuraciones para las librerias
// del servomotor y del sensor IR.

IRrecv irrecv(RECV_PIN);
decode_results results;
Servo myservo1;



/*-------------------PROGRAMA-----------------------------------*/

void setup() {

  //Configuramos iniciales de la moto.
  
  myservo1.attach(Pin_servo); // Indicamos el pin del servomotor
  irrecv.enableIRIn();        // Empezamos la recepción  por IR
  pinMode(4,OUTPUT);          // Pin para activar la moto 
  digitalWrite(4,ENCENDIDO);  // Apagamos la moto al iniciar el programa
  analogWrite(5,VELOCIDAD);   // Configuramos la velocidad hacia adelante
  analogWrite(6,0);           // Configuramos la velocidad haca atraz
  myservo1.write(GIRO);       // iniciamos la moto con el volante recto
}


void loop() {

  // Funciones que controlan el giro y el estado de la moto
  
    myservo1.write(GIRO);    // Movemos el servo motor para el giro
    digitalWrite(4,ENCENDIDO);    // Esta funcion controla si la moto se
                             // enciende o se apaga.       


  // Este grupo de funciones reconoce los datos que envia el control
  // remoto y actua segun la tecla que se oprima.
  if(irrecv.decode(&results))
  {

   if(results.value == ARRIBA){analogWrite ( 5, VELOCIDAD);analogWrite(6, 0);} 
   if(results.value == ABAJO) {analogWrite ( 6, VELOCIDAD);analogWrite(5, 0);} 
   if(results.value == DERECHA)  {if(GIRO < 180){GIRO = GIRO +30;}} 
   if(results.value == IZQUIERDA){if(GIRO > 0){GIRO = GIRO -30;}} 
   if(results.value == CENTRO)   {ENCENDIDO = ~ENCENDIDO;}
    
   irrecv.resume(); 
  }
}





