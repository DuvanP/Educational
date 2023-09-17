// incluimos la librería del servomotor
 #include <Servo.h>

  // Le indicamos a la librería que vamos a usar
  // cinco servomotores.

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

  // Creamos algunas variables
  
  // Este grupo le indicará a arduino en donde
  // Estará conectado los 5 sensores flexibles
  
int PinSensorflex1 = A0; // Análogo Dedo pulgar
int PinSensorflex2 = A1; // Análogo Dedo índice
int PinSensorflex3 = A2; // Análogo Dedo corazón
int PinSensorflex4 = A3; // Análogo Dedo anular
int PinSensorflex5 = A4; // Análogo Dedo meñique

  // En este grupo se guardará la información
  // de cada sensor flexible
  
int LecturaSensorflex1;  // Acá guardaremos los datos del dedo pulgar
int LecturaSensorflex2;  // Acá guardaremos los datos del dedo índice
int LecturaSensorflex3;  // Acá guardaremos los datos del dedo corazón
int LecturaSensorflex4;  // Acá guardaremos los datos del dedo anular
int LecturaSensorflex5;  // Acá guardaremos los datos del dedo meñique


int puntaje1_alto = 282; // Nivel Alto del sensor dedo pulgar
int puntaje1_bajo = 137; // Nivel Bajo del sensor dedo pulgar
int puntaje2_alto = 259; // Nivel Alto del sensor dedo índice
int puntaje2_bajo = 135; // Nivel Bajo del sensor dedo índice
int puntaje3_alto = 280; // Nivel Alto del sensor dedo corazón
int puntaje3_bajo = 119; // Nivel Bajo del sensor dedo corazón
int puntaje4_alto = 219; // Nivel Alto del sensor dedo anular
int puntaje4_bajo = 52;  // Nivel Bajo del sensor dedo anular
int puntaje5_alto = 280; // Nivel Alto del sensor dedo meñique
int puntaje5_bajo = 128; // Nivel Bajo del sensor dedo meñique


int Mapeo1;  // Acá guardaremos los datos de los 
int Mapeo2;  // sensores mapeados
int Mapeo3;
int Mapeo4;
int Mapeo5;

void setup() {

//Le indicamos a la librería de los servos cual dedo va conectado
  myservo1.attach(9);  // Dedo Pulgar
  myservo2.attach(8);  // Índice
  myservo3.attach(7);  // Corazón 
  myservo4.attach(6);  // Anular
  myservo5.attach(5);  // Meñique

Serial.begin(9600); // iniciamos la comunicación con arduino

}

void loop() {

LecturaSensorflex1 = analogRead(PinSensorflex1); // Leemos el Sensor flexible
LecturaSensorflex2 = analogRead(PinSensorflex2); // Leemos el Sensor flexible
LecturaSensorflex3 = analogRead(PinSensorflex3); // Leemos el Sensor flexible
LecturaSensorflex4 = analogRead(PinSensorflex4); // Leemos el Sensor flexible
LecturaSensorflex5 = analogRead(PinSensorflex5); // Leemos el Sensor flexible

Mapeo1 = map(LecturaSensorflex1, puntaje1_bajo , puntaje1_alto,0, 180); // hacemos el mapeo
Mapeo2 = map(LecturaSensorflex2, puntaje2_bajo , puntaje2_alto,0, 180); // hacemos el mapeo
Mapeo3 = map(LecturaSensorflex3, puntaje3_bajo , puntaje3_alto,0, 180); // hacemos el mapeo
Mapeo4 = map(LecturaSensorflex4, puntaje4_bajo , puntaje4_alto,0, 180); // hacemos el mapeo
Mapeo5 = map(LecturaSensorflex5, puntaje5_bajo , puntaje5_alto,0, 180); // hacemos el mapeo

myservo1.write(Mapeo1);     // Con estas funciones movemos los dedos dependiendo del cada sensor
myservo2.write(Mapeo2);      
myservo3.write(Mapeo3);        
myservo4.write(Mapeo4);        
myservo5.write(Mapeo5);        


// imprimimos en el puerto serial la información para calibración
Serial.print(" Lec_Sen1 ");       
Serial.print(LecturaSensorflex1);
Serial.print("    Lec_Sen2 "); 
Serial.print(LecturaSensorflex2);
Serial.print("    Lec_Sen3 "); 
Serial.print(LecturaSensorflex3);
Serial.print("    Lec_Sen4 "); 
Serial.print(LecturaSensorflex4);
Serial.print("    Lec_Sen5 "); 
Serial.println(LecturaSensorflex5);

}


