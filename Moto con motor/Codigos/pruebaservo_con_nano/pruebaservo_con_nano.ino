 // incluimos la libreria del servomotor
 #include <Servo.h>

  // Le indicamos a la libreria que vamos a usar
  // un solo servomotor.
Servo myservo1;

  // Creamos una variable para guardar el giro del 
  // servomotor
int pos;


// esta parte es para configurar el pin del servomotor
void setup() {

  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
}

// Esta seccion se repite infinitamente
void loop() {

    // El programa girará al servomotor a 0 grados, esperará 2 segundos
    // luego lo hará girar a 180 grados, esperará otros 2 segundos y asi 
    // sucesivamente.
    
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    pos =0;
    delay(2000);
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    pos = 90;
    delay(2000);
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    pos = 180;
    delay(2000);
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    pos = 90;
    delay(2000);


}
