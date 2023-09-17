#include <Servo.h>

// Incluimos la librería infrarroja
#include <IRremote.h>

// indicamos el pin donde el sensor estará
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);

// creamos una variable para la recepción
// de los  códigos.
decode_results results;
Servo myservo1;

int GIRO = 90;
long DERECHA     = 0xFF5AA5;
long IZQUIERDA   = 0xFF10EF;

// habilitamos la recepción de los datos
// y la comunicación entre arduino y el 
// computador.
void setup() {
 myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
irrecv.enableIRIn();
Serial.begin(9600);
}

// Si recibimos datos entonces
// los mostrará en el monitor serial
void loop(){

        myservo1.write(GIRO);              // tell servo to go to position in variable 'pos'

if(irrecv.decode(&results))
   {
    Serial.println(results.value, HEX);
    delay(40);
       
   if(results.value == DERECHA)  {if(GIRO < 180){GIRO = GIRO +40;}} 
   
   if(results.value == IZQUIERDA){if(GIRO > 0){GIRO = GIRO -40;}} 
    irrecv.resume();

    }

   
}

