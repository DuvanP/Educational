	
	
	
	/*
	Project developed by Ing Duvan Camilo Puerto Barajas
	Creatvra SAS. Bogota Colombia 2019
	Please visit us at : https://creaturaestudio.com/
	Github: https://github.com/DuvanP
	
	This project is released over the GNU General Public License, version 2
	and is created for the Arduino Uno platform.
	
	Overview:
	
	This code is intented to make a funtional Piano instrument with 8 keys
	The current sound effects that it supports are:
	
	1 Calibration of touch sensor
	2 Delay
	3 Midi connections.
	4 Midi controll buttons
	5 Midi Interruptor
	6 Midi Potentiometer
	4 Sustain
	5 Vibrato
	6 plain piano
	7 octave effects
	

*/



 #include "TODO.h"
 #include <Arduino.h>
 #include <avr/interrupt.h>
 #include <avr/pgmspace.h>
 #include <pins_arduino.h>
 
 
 // Variables para controlar los pines de los timers dentro de las interrupciones
volatile int32_t timer1_toggle_count;		
volatile uint8_t *timer1_pin_port;
volatile uint8_t timer1_pin_mask;
volatile int32_t timer2_toggle_count;
volatile uint8_t *timer2_pin_port;
volatile uint8_t timer2_pin_mask;

int8_t PIN_RX;		// pin que transmite
int8_t PIN_TX;		// pin que recive		


// Variables Para la parte Capacitiva
	unsigned long  CS_Timeout_Millis;	// tiempo limite de espera en las teclas
	unsigned int   loopTimingFactor;	// Usado para modificar el CS_Timeout_Millis
    
	uint8_t _pin_timer1;		// Pines para de salida para el Timer1 y Timer2
	uint8_t _pin_timer2;


	int8_t _error = 0;		// Error para determinar si se escribieron mal los pines 
					

	
	int32_t _CALI;		// CALI se refiere al numero de calibracion que compara
						// el valor de los sensores capacitivos 
	int32_t _veces;		// Se refiere al numero de veces que se ejecuta la
						// funcion Onecycle();
						
	unsigned long  _total;	// esta variable es de suma importancia, es la que guarda el tiempo que demora la funcion
							// Onecycle, este tiempo es el que genera la deteccion de la tecla.
							
							
							
	float _frecuencia1;		// Estas variables guarda la frecuencia de las 8 teclas
	float _frecuencia2;
	float _frecuencia3;
	float _frecuencia4;
	float _frecuencia5;
	float _frecuencia6;
	float _frecuencia7;
	float _frecuencia8;

	
	uint8_t frecuencia1_midi;	// Estas variables guarda tambien la frecuencia de las 8 teclas pero en formato midi
	uint8_t frecuencia2_midi;	
	uint8_t frecuencia3_midi;
	uint8_t frecuencia4_midi;
	uint8_t frecuencia5_midi;
	uint8_t frecuencia6_midi;
	uint8_t frecuencia7_midi;
	uint8_t frecuencia8_midi;



	
	uint8_t _receivePin1 =150;	// Estas variables guardan los pines digitales de cada tecla del piano
	uint8_t _receivePin2 =150;
	uint8_t _receivePin3 =150;
	uint8_t _receivePin4 =150;
	uint8_t _receivePin5 =150;
	uint8_t _receivePin6 =150;
	uint8_t _receivePin7 =150;
	uint8_t _receivePin8 =150;

	
	// Las siguientes son punteros y variables usados para controlar los pines de la antigua forma, como se hacia en ATMEL
	// Estos se usan para optimizar tiempo al momento usar la parte capacitiva de la tecla
	uint8_t sBit;   // send pin's ports and bitmask 
	volatile uint8_t *sReg;
	uint8_t rBit;    // receive pin's ports and bitmask
	volatile uint8_t *rReg;
	
	
	
	uint32_t _ocr;	//Las siguientes son variables usadas para guardar el registro OCR de cada frecuencia y generar el TIMER
	uint32_t _ocr1;
	uint32_t _ocr2;
	uint32_t _ocr3;
	uint32_t _ocr4;
	uint32_t _ocr5;
	uint32_t _ocr6;
	uint32_t _ocr7;
	uint32_t _ocr8;
	
	uint8_t  _presc; // Estas variables guardan el Numero Prescaler para poder obtener la frecuencia adecuada en la salida del TIMER
	uint8_t  _presc1;
	uint8_t  _presc2;
	uint8_t  _presc3;
	uint8_t  _presc4;
	uint8_t  _presc5;
	uint8_t  _presc6;
	uint8_t  _presc7;
	uint8_t  _presc8;
	
	
	long PEPE1;	// PEPE es quiza la variable mas importante, es la que se encarga de obtener el tiempo que demora CADA tecla por eso hay 8
	long PEPE2;
	long PEPE3;
	long PEPE4;
	long PEPE5;
	long PEPE6;
	long PEPE7;
	long PEPE8;
	
	bool _clave1; // las claves determinan si se ha tocado una tecla o no, estas son comparadas con el valor de PEPE y CALI
	bool _clave2;
	bool _clave3;
	bool _clave4;
	bool _clave5;
	bool _clave6;
	bool _clave7;
	bool _clave8;
	
	
	uint8_t ESTADO_TECLA1; // la variable ESTADO_TECLA determina si la tecla esta siendo oprimida o si fue liberada
	uint8_t ESTADO_TECLA2;
	uint8_t ESTADO_TECLA3;
	uint8_t ESTADO_TECLA4;
	uint8_t ESTADO_TECLA5;
	uint8_t ESTADO_TECLA6;
	uint8_t ESTADO_TECLA7;
	uint8_t ESTADO_TECLA8;
	
	
	
	int TIMER_ULTIMO_USADO; // Guarda el valor del ultimo timer usado, para de esta manera poder usar el segundo timer disponible
	
	volatile int TIMER1_DE_TECLA;	// Estas dos variables determinan cual fue la ultima tecla que uso el timer
	volatile int TIMER2_DE_TECLA;
	
	uint8_t TECLAS_AL_TIEMPO; // Esta variable evita que se toquen mas de 2 teclas al tiempo, pues solo se tienen 2 timers

	
	
	bool _SUSTAIN = 0;		// Inicia desactivando el Sustain en modo piano, es 0 por la logica del pulsador que lo activa.
	bool DELAY_FUN = 0;		// Inicia desactivado 
	volatile uint8_t VIBRATO = 0; // Inicia desactivado el Vibrato, es 0 por la logica del pulsador
	volatile int tiempo_vibrato = 300; // DEtermina un tiempo inicial para el vibrato, pero este cambia con la funcion vibrato
	
	
	uint16_t duracion = 100;  // Se inicializa en 100 ms y es el tiempo que dura sonando una tecla en piano modo normal

	
	float numero_stev;		//numero usado para conseguir el medio tono superior o inferior
	
	
	
	
	// Variables usadas para poder generar la señal cuadrada en el TIMER 1
	// Algunas de estas son usadas para evitar colapsar el timer con muchos datos
	// y de esta forma evitar que el timer toque dos veces una misma nota, sin necesidad
	volatile float	 ocr_actual_t1;
	volatile double  valor_sup_t1;
	volatile double  valor_inf_t1;
	volatile float 	 ocr_t1;
	volatile float 	 ocr_sup_t1;
	volatile float 	 ocr_inf_t1;
	volatile uint8_t etapa_t1; 
	volatile uint16_t pres_t1;		
	volatile uint16_t frec_t1;		
	
	// Variables usadas para poder generar la señal cuadrada en el TIMER 2
	// Algunas de estas son usadas para evitar colapsar el timer con muchos datos
	// y de esta forma evitar que el timer toque dos veces una misma nota, sin necesidad	
	volatile float	 ocr_actual_t2;
	volatile double  valor_sup_t2;
	volatile double  valor_inf_t2;
	volatile float 	 ocr_t2;
	volatile float 	 ocr_sup_t2;
	volatile float 	 ocr_inf_t2;
	volatile uint8_t etapa_t2; 
	volatile uint16_t pres_t2;		
	volatile uint16_t frec_t2;	
	
	
		
	volatile float timer1_toggle_delay; 	// variable usada para generar la señal cuadrada dependiendo de un delay
	volatile float timer1_tiempo;			// variable usada para guardar el tiempo que necesita el delay
	volatile float timer1_toggle_count_delay; // variable usada para controlar el desborde del timer 1 en modo delay
	volatile uint8_t FIN_DELAY_T1 = 0;		// Variable que guarda el fin del tiempo del delay
	volatile uint8_t repeticiones_t1 = 0;	// variable guarda el numer de repeticiones que debe tener el delay
	volatile uint8_t parte_alta_t1;			// Esta variable es la que fisicamente cambia el valor del Timer en modo Delay
	
	volatile float timer2_toggle_delay;
	volatile float timer2_tiempo;
	volatile float timer2_toggle_count_delay;
	volatile uint8_t FIN_DELAY_T2 = 0;
	volatile uint8_t repeticiones_t2 = 0;
	volatile uint8_t parte_alta_t2;	
	
	
	uint16_t duracion_delay = 300;		// Variable usada para inicializar el tiempo del delay en 300ms
	int repeticiones_delay = 5; 		// El Delay por defecto solo se repetira 5 veces	
										// No existe una funcion que controle este numero

			

	// MIDI VARIABLES
	
	bool _PianoON = 1;		// Variable que controla si el piano suena o no, Inicia activado
	bool _SynthOn = 0;		// Variable que controla si el Sintetizador esta activado o no, inicia desactivado
	bool _MidiOn  = 0;		// Variable que controla si el modo midi esta activado o no , inicia desactivado
	
	
	bool Tecla_midiOff1 = 0;	// Tecla Midioff y tecla MidiOn generan el sonido Midi del piano en algun Software DAW
	bool Tecla_midiOn1  = 1;
	bool Tecla_midiOff2 = 0;
	bool Tecla_midiOn2  = 1;
	bool Tecla_midiOff3 = 0;
	bool Tecla_midiOn3  = 1;
	bool Tecla_midiOff4 = 0;
	bool Tecla_midiOn4  = 1;
	bool Tecla_midiOff5 = 0;
	bool Tecla_midiOn5  = 1;
	bool Tecla_midiOff6 = 0;
	bool Tecla_midiOn6  = 1;
	bool Tecla_midiOff7 = 0;
	bool Tecla_midiOn7  = 1;
	bool Tecla_midiOff8 = 0;
	bool Tecla_midiOn8  = 1;

	uint8_t _canalConComando = 0b10010000;		// Varialbe que guarda el comando del canal 
	uint8_t _Velocidad_teclas = 30;				// Determina el volumen de las teclas en modo MIDI cuando las reproduce algun software DAW
	uint8_t _modo_NoteOn = 0b10010000;			// Esta variable se usa para hacer una mascara y generar el modo On en midi que practicamente toca el piano
	uint8_t _modo_BankOn = 0b10110000;			// Esta variable se usa para hacer una mascara y generar el modo ControlChange
	
// Initialize our pin count


	uint8_t _switchOn1 = 1;		// SwitchOn y Switchoff son variables para prender o apagar las notas midi
	uint8_t _switchOff1;
	uint8_t _switchOn2 = 1;
	uint8_t _switchOff2;
	uint8_t _switchOn3 = 1;
	uint8_t _switchOff3;
	uint8_t _switchOn4 = 1;
	uint8_t _switchOff4;
	uint8_t _switchOn5 = 1;
	uint8_t _switchOff5;
	uint8_t _switchOn6 = 1;
	uint8_t _switchOff6;
	
	
		
		// Las siguientes funcionan controlan el banco, el canal y el volumen de las 3 funciones de pulsador disponibles
	uint8_t _Banco1;	
	uint8_t	_Canal1;
	uint8_t _VelocitY1; 
	
	uint8_t _Banco2;
	uint8_t	_Canal2;
	uint8_t _VelocitY2; 
	
	uint8_t _Banco3;
	uint8_t	_Canal3;
	uint8_t _VelocitY3; 
	
	uint8_t _Banco4;
	uint8_t	_Canal4;
	uint8_t _VelocitY4; 

	uint8_t _Banco5;
	uint8_t	_Canal5;
	uint8_t _VelocitY5; 

	uint8_t _Banco6;
	uint8_t	_Canal6;
	uint8_t _VelocitY6; 
	

	uint8_t tiempo_descanso = 20;	// este tiempo es para controlar cada cuanto se lee el potenciometro en las funciones de potenciometro
	
	// Estas tambien controlan el tiempo que el potenciometro es leido
	long tiempoX1;
	long tiempoX1_Pa = millis();
	long tiempoX2;
	long tiempoX2_Pa = millis();
	long tiempoX3;
	long tiempoX3_Pa = millis();
	long tiempoX4;
	long tiempoX4_Pa = millis();
	long tiempoX5;
	long tiempoX5_Pa = millis();
	long tiempoX6;
	long tiempoX6_Pa = millis();
	
	






void TODO :: Fiesta (int8_t tonePin1, int8_t tonePin2, int8_t sendPin)

{
		/* En esta funcion se definen los pines del parlante, tambien
		se define que pin sera el transmisor para la parte Capacitiva
		se define el tiempo maximo que tardara la funcion capacitiva
		cuando se este esperando el valor en el pin re recepcion
		
		Tambien se configuraran los timers, se colocaran en cero
		sus respectivos registro para solo el timer 1 y el timer 2
		como tambien sus mascaras y punteros para poder trabajarlos
		con interrupciones
		Por ultimo se configuraran los pines del parlante o los 
		pines que son del timer, como salida y se les dara un LOW*/
		


	if( (tonePin1 <0) || (tonePin1 >= 20) || (tonePin2 <0) || (tonePin2 >= 20) || (sendPin <0) || (sendPin >= 20)){_error = -1;} 
	

	
	if (_error == 0) 		
	{


		
		
		
	PIN_TX = sendPin;
	loopTimingFactor = 310;		// determined empirically -  a hack
	CS_Timeout_Millis = (2000 * (float)loopTimingFactor * (float)F_CPU) / 16000000;  //


	_pin_timer1 = tonePin1;
	_pin_timer2 = tonePin2;


	          // 8 bit timer
        TCCR2A = 0;
        TCCR2B = 0;
		OCR2A  = 0;
		
        bitWrite(TCCR2A, WGM21, 1);		// Modo CTC comparado con OCR2A	
        //bitWrite(TCCR2B, CS20, 1);
        timer2_pin_port = portOutputRegister(digitalPinToPort(_pin_timer2));
        timer2_pin_mask = digitalPinToBitMask(_pin_timer2);
		

		// 16 bit timer
        TCCR1A = 0;
        TCCR1B = 0;
		OCR1AL = 0;
        bitWrite(TCCR1B, WGM12, 1);	// Modo CTC comparado con OCR1A
        //bitWrite(TCCR1B, CS10, 1);
        timer1_pin_port = portOutputRegister(digitalPinToPort(_pin_timer1));
        timer1_pin_mask = digitalPinToBitMask(_pin_timer1);
		
		
		pinMode(PIN_TX, OUTPUT);
		digitalWrite(PIN_TX,LOW);
		
		pinMode(_pin_timer1, OUTPUT);
		pinMode(_pin_timer2, OUTPUT);
	}
	
	_CALI = 55; 		// CALI se refiere al numero de calibracion que compara
						// el valor de los sensores capacitivos
	
	_veces = 8;		// Se refiere al numero de veces que se ejecuta la
						// funcion Onecycle();
						// Estos numeros se obtuvieron de la experiencia CALI =55 y veces = 8

						
	sBit = PIN_TO_BITMASK(sendPin);					// get send pin's ports and bitmask
	sReg = PIN_TO_BASEREG(sendPin);		
	
	numero_stev = pow(2,(float)1/12);		//numero para conseguir el medio tono superior o inferior

	
	//ModoPiano ( true, false, false);
	
}




void TODO :: Calibracion (int32_t CALI)
{
	

	_CALI = CALI;
	
	

	
}


void TODO :: Tecla1 (int8_t receivePin1, uint16_t frecuencia1){
	
	frecuencia1_midi = frecuencia1;
	
	_frecuencia1 = ConverMidiToFrecu (frecuencia1_midi);
	
	_receivePin1 = receivePin1;
	pinMode(_receivePin1, INPUT);	
	frecuencia(_frecuencia1);
	_ocr1   = _ocr;
	_presc1 = _presc;

}

void TODO :: Tecla2 (int8_t receivePin2, uint16_t frecuencia2){
	
	frecuencia2_midi = frecuencia2;
	_frecuencia2 = ConverMidiToFrecu (frecuencia2_midi);
	
	_receivePin2 = receivePin2;
	pinMode(_receivePin2, INPUT);
	frecuencia(_frecuencia2);
	_ocr2   = _ocr;
	_presc2 = _presc;		
}

void TODO :: Tecla3 (int8_t receivePin3, uint16_t frecuencia3){
	
	frecuencia3_midi = frecuencia3;
	_frecuencia3 = ConverMidiToFrecu (frecuencia3_midi);
		
	_receivePin3 = receivePin3;
	pinMode(_receivePin3, INPUT);	
	frecuencia(_frecuencia3);
	_ocr3   = _ocr;
	_presc3 = _presc;	
}

void TODO :: Tecla4 (int8_t receivePin4, uint16_t frecuencia4){
	
	frecuencia4_midi = frecuencia4;
	_frecuencia4 = ConverMidiToFrecu (frecuencia4_midi);
		
	_receivePin4 = receivePin4;
	pinMode(_receivePin4, INPUT);
	frecuencia(_frecuencia4);
	_ocr4   = _ocr;
	_presc4 = _presc;	
}

void TODO :: Tecla5 (int8_t receivePin5, uint16_t frecuencia5){
	
	frecuencia5_midi = frecuencia5;
	_frecuencia5 = ConverMidiToFrecu (frecuencia5_midi);
		
	_receivePin5 = receivePin5;
	pinMode(_receivePin5, INPUT);
	frecuencia(_frecuencia5);
	_ocr5   = _ocr;
	_presc5 = _presc;	
}

void TODO :: Tecla6 (int8_t receivePin6, uint16_t frecuencia6){
	
	frecuencia6_midi = frecuencia6;
	_frecuencia6 = ConverMidiToFrecu (frecuencia6_midi);
		
	_receivePin6 = receivePin6;
	pinMode(_receivePin6, INPUT);
	frecuencia(_frecuencia6);
	_ocr6   = _ocr;
	_presc6 = _presc;	
}

void TODO :: Tecla7 (int8_t receivePin7, uint16_t frecuencia7){
	
	frecuencia7_midi = frecuencia7;
	_frecuencia7 = ConverMidiToFrecu (frecuencia7_midi);
		
	_receivePin7 = receivePin7;
	pinMode(_receivePin7, INPUT);	
	frecuencia(_frecuencia7);
	_ocr7   = _ocr;
	_presc7 = _presc;
}
void TODO :: Tecla8 (int8_t receivePin8, uint16_t frecuencia8){
	
	frecuencia8_midi = frecuencia8;
	_frecuencia8 = ConverMidiToFrecu (frecuencia8_midi);
		
	_receivePin8 = receivePin8;
	pinMode(_receivePin8, INPUT);
	frecuencia(_frecuencia8);
	_ocr8   = _ocr;
	_presc8 = _presc;	
}





float TODO :: ConverMidiToFrecu ( float MidiFrecu ){
	
	float _MidiFrecu;
	
	_MidiFrecu = MidiFrecu;
	
	_MidiFrecu = _MidiFrecu - 9;
	_MidiFrecu =  (float)13.75*(pow(numero_stev,_MidiFrecu));

	//Serial.print(_MidiFrecu);
	
		//Serial.print("   ");
	_MidiFrecu = round(_MidiFrecu);
	
	//Serial.println(_MidiFrecu);
	
	return _MidiFrecu;
	
	
}


void TODO :: frecuencia ( uint16_t frequency)
{
	_ocr = F_CPU / frequency / 2 - 1; // funcion prescaler 1
    _presc = 0b001;  
	
    if (_ocr > 255)
    {
		_ocr = F_CPU / frequency / 2 / 8 - 1; // funcion prescaler 8
        _presc = 0b010;  
		if((frequency >= 3892)&&(frequency <=4185) ){_ocr = 500;} // esto obligara a tomar el sig prescaler
	}


	if (_ocr > 255)
	{
		_ocr = F_CPU / frequency / 2 / 64 - 1; // funcion prescaler 64
		_presc =  0b011;
		
		if((frequency >= 487)&&(frequency <=522) ){_ocr = 500;} // esto obligara a tomar el sig prescaler
	}
	
	if (_ocr > 255)
	{
		
		_ocr = F_CPU / frequency / 2 / 256 - 1; // funcion prescaler 256
		_presc = 0b100;
		
		if((frequency >= 122)&&(frequency <=130) ){_ocr = 500;} // esto obligara a tomar el sig prescaler
	}

	if (_ocr > 255)
	{
		_ocr = F_CPU / frequency / 2 / 1024 - 1; // funcion prescaler 1024
		_presc = 0b101;
	}
	

}




bool TODO :: Nota1 (void){

	PEPE1 = Prueba(_receivePin1); 
	//DEBUGIN4(PEPE);
	if(PEPE1  > _CALI){_clave1 = 1;TECLAS_AL_TIEMPO++;return true;}
	else{_clave1 = 0; return false;}}

bool TODO :: Nota2 (void){

	PEPE2 = Prueba(_receivePin2);
	//DEBUGIN4(PEPE);
	if(PEPE2  > _CALI){_clave2 = 1;TECLAS_AL_TIEMPO++;return true;}
	else{_clave2 = 0; return false;}}
	
bool TODO :: Nota3 (void){

	PEPE3 = Prueba(_receivePin3);
	//DEBUGIN4(PEPE);
	if(PEPE3  > _CALI){_clave3 = 1;TECLAS_AL_TIEMPO++;return true;}
	else{_clave3 = 0; return false;}}
	
bool TODO :: Nota4 (void){

	PEPE4 = Prueba(_receivePin4);
	//DEBUGIN4(PEPE);
	if(PEPE4  > _CALI){_clave4 = 1;TECLAS_AL_TIEMPO++;return true;}
	else{_clave4 = 0; return false;}}

bool TODO :: Nota5 (void){

	PEPE5 = Prueba(_receivePin5);
	//DEBUGIN4(PEPE);
	if(PEPE5  > _CALI){_clave5 = 1;TECLAS_AL_TIEMPO++;return true;}
	else{_clave5 = 0; return false;}}
	
bool TODO :: Nota6 (void){

	PEPE6 = Prueba(_receivePin6);
	//DEBUGIN4(PEPE);
	if(PEPE6  > _CALI){_clave6 = 1;TECLAS_AL_TIEMPO++;return true;}
	else{_clave6 = 0; return false;}}
	
bool TODO :: Nota7 (void){

	PEPE7 = Prueba(_receivePin7);
	//DEBUGIN4(PEPE);
	if(PEPE7  > _CALI){_clave7 = 1;TECLAS_AL_TIEMPO++;return true;}
	else{_clave7 = 0; return false;}}
	
bool TODO :: Nota8 (void){

	PEPE8 = Prueba(_receivePin8);
	//DEBUGIN4(PEPE);
	//Serial.println(" ");
	if(PEPE8  > _CALI){_clave8 = 1;TECLAS_AL_TIEMPO++;return true;}
	else{_clave8 = 0; return false;}}







long TODO::Prueba(int8_t _pin )
{
	unsigned long PEPE;

	// Serial.print("receivePin: ");
	// Serial.print(_receivePin1);
	// Serial.print(" CALI: ");
	// Serial.print(_CALI);
	// Serial.print(" veces: ");
	// Serial.println(_veces);
	
	rBit = PIN_TO_BITMASK(_pin);				// get receive pin's ports and bitmask
	rReg = PIN_TO_BASEREG(_pin);
	
	// if (_veces == 0) {return 0;}		// devuelve 0 si veces es configurada como 0 
	// if (_error == -1){return -1;}	// devuelve -1 si algun pin definido esta fuera del rando 0-19 que son los pines digitales
	 
	// if ((_pin < 0)||(_pin >= 20)){return -2;} // devuelve -2 si el pin de la tecla esta fuera del rango 0 -19 

	
	for(int i = 0; i <= _veces; i++){SenseOneCycle();}
	PEPE = _total;
	_total = 0;
	 PEPE /= (_veces*2);  // promedio de las señales
	 // PEPE = (PEPE)-(0.95*PEPE);
	 // PEPE = PEPE * 100;
	return PEPE;
}


void TODO::SenseOneCycle(void)
{
	// Serial.print("SenseOneCycle(2): ");
	// Serial.println(_total);
    cli();		// No interrupciones
	DIRECT_WRITE_LOW(sReg, sBit);	// sendPin Register low
	DIRECT_MODE_INPUT(rReg, rBit);	// receivePin to input (pullups are off)
	DIRECT_MODE_OUTPUT(rReg, rBit); // receivePin to OUTPUT
	DIRECT_WRITE_LOW(rReg, rBit);	// pin is now LOW AND OUTPUT
	delayMicroseconds(10);
	DIRECT_MODE_INPUT(rReg, rBit);	// receivePin to input (pullups are off)
	DIRECT_WRITE_HIGH(sReg, sBit);	// sendPin High
    sei();

	while ( !DIRECT_READ(rReg, rBit) && (_total < CS_Timeout_Millis) ) {  // while receive pin is LOW AND _total is positive value
		_total++;
	}
	//Serial.print("SenseOneCycle(1): ");
	//Serial.println(_total);

	// if (_total > CS_Timeout_Millis) {
		// return -2;         //  _total variable over timeout
	// }

	// set receive pin HIGH briefly to charge up fully - because the while loop above will exit when pin is ~ 2.5V
    cli();
	DIRECT_WRITE_HIGH(rReg, rBit);
	DIRECT_MODE_OUTPUT(rReg, rBit);  // receivePin to OUTPUT - pin is now HIGH AND OUTPUT
	DIRECT_WRITE_HIGH(rReg, rBit);
	DIRECT_MODE_INPUT(rReg, rBit);	// receivePin to INPUT (pullup is off)
	DIRECT_WRITE_LOW(sReg, sBit);	// sendPin LOW
    sei();


	while ( DIRECT_READ(rReg, rBit) && (_total < CS_Timeout_Millis) ) {  // while receive pin is HIGH  AND _total is less than timeout
		_total++;
	}

//////////////////////


    cli();
	DIRECT_WRITE_LOW(sReg, sBit);	// sendPin Register low
	DIRECT_MODE_INPUT(rReg, rBit);	// receivePin to input (pullups are off)
	DIRECT_MODE_OUTPUT(rReg, rBit); // receivePin to OUTPUT
	DIRECT_WRITE_LOW(rReg, rBit);	// pin is now LOW AND OUTPUT
	delayMicroseconds(10);
	DIRECT_MODE_INPUT(rReg, rBit);	// receivePin to input (pullups are off)
	DIRECT_WRITE_HIGH(sReg, sBit);	// sendPin High
    sei();

	while ( !DIRECT_READ(rReg, rBit) && (_total < CS_Timeout_Millis) ) {  // while receive pin is LOW AND _total is positive value
		_total++;
	}
	//Serial.print("SenseOneCycle(1): ");
	//Serial.println(_total);

	// if (_total > CS_Timeout_Millis) {
		// return -2;         //  _total variable over timeout
	// }

	// set receive pin HIGH briefly to charge up fully - because the while loop above will exit when pin is ~ 2.5V
    cli();
	DIRECT_WRITE_HIGH(rReg, rBit);
	DIRECT_MODE_OUTPUT(rReg, rBit);  // receivePin to OUTPUT - pin is now HIGH AND OUTPUT
	DIRECT_WRITE_HIGH(rReg, rBit);
	DIRECT_MODE_INPUT(rReg, rBit);	// receivePin to INPUT (pullup is off)
	DIRECT_WRITE_LOW(sReg, sBit);	// sendPin LOW
    sei();


	while ( DIRECT_READ(rReg, rBit) && (_total < CS_Timeout_Millis) ) {  // while receive pin is HIGH  AND total is less than timeout
		_total++;
	}


	// if (_total >= CS_Timeout_Millis) {
		// return -2;     // _total variable over timeout
	// } else {
		// return 1;
	// }
	
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////    /)/)                                              ///////////////////////////
/////////////////////////////////  \( o_o) /      EXISTEN COSAS EN LA VIDA QUE NADIE   ///////////////////////////
/////////////////////////////////   (")__(")               PUEDE EXPLICAR              ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Interrupt routines

// Estas interrupciones se usan para poder controlar los modulos Timer que trae el Microcontrolador ATMEGA328p
// Por esta razon esta libreria solo funciona para este microcontrolador o para los que compartan similitudes(ver Datasheet). 



ISR(TIMER1_COMPA_vect)
{
  if (timer1_toggle_count != 0)
  {
    // toggle the pin
    *timer1_pin_port ^= timer1_pin_mask;

    if (timer1_toggle_count > 0)
	{timer1_toggle_count--;return;}
	
	
	else
	{
			  
		if( VIBRATO == 1)
		{
			//Serial.println(tiempo_vibrato);
			valor_sup_t1 = ((((float)numero_stev-1)*F_CPU)/((pow(frec_t1,2))*pres_t1*tiempo_vibrato))*1000;
			valor_inf_t1 = valor_sup_t1/numero_stev;
		
			switch(etapa_t1)
			{
				case 1 :					
					ocr_actual_t1 = ocr_actual_t1 + valor_sup_t1;
					OCR1AL = ocr_actual_t1;
					if(ocr_actual_t1 >= ocr_sup_t1){etapa_t1 = 2;}
					return;	
				case 2 :
					ocr_actual_t1 = ocr_actual_t1 - valor_sup_t1;
					OCR1AL = ocr_actual_t1;
					if(ocr_actual_t1 <= ocr_t1){etapa_t1 = 3;}
					return;					
				case 3 :
					ocr_actual_t1 = ocr_actual_t1 - valor_inf_t1;
					OCR1AL = ocr_actual_t1;
					if(ocr_actual_t1 <= ocr_inf_t1){etapa_t1 = 4;}
					return;	
				case 4 :
					ocr_actual_t1 = ocr_actual_t1 + valor_inf_t1;
					OCR1AL = ocr_actual_t1;
					if(ocr_actual_t1 >= ocr_t1){etapa_t1 = 1;}
					return;			
					
			}
		}
		
		else{ OCR1AL = ocr_t1;}
	}
		
	return;
  }	
  else 	
  {
	 
		
		timer1_toggle_delay = (float)(duracion_delay)/(2000*repeticiones_delay);
		
	  if((DELAY_FUN == 1) && (FIN_DELAY_T1 == 0) && (duracion_delay != 0))
	  {
		  
		  timer1_toggle_count_delay =  (float)timer1_toggle_count_delay + timer1_tiempo;
		  
		  //Serial.println(timer1_toggle_count_delay,10);
		  //Serial.println(parte_alta_t1);
		  
		  if (timer1_toggle_count_delay >= timer1_toggle_delay )
		  {
				
				parte_alta_t1 = ~parte_alta_t1;
				timer1_toggle_count_delay = 0;
				repeticiones_t1 ++;
		  }
		  
		  if(parte_alta_t1 )
		  {
			//Serial.println("hola");
			 *timer1_pin_port ^= timer1_pin_mask;		
		  }
		  
		  else{*timer1_pin_port &= ~(timer1_pin_mask);}

		  
		  if ( repeticiones_t1 == (repeticiones_delay*2) ){FIN_DELAY_T1 = 1;}
		  return;
	  }
	  else
	  {
	  
	  
	  
	    TIMSK1 &= ~(1 << OCIE1A);			    // Deshabilita la interrupcion
	    TCCR1B = (TCCR1B & 0b11111000) | 1; 	// Deshabilita el timer2
 	    *timer1_pin_port &= ~(timer1_pin_mask);	// Pone un cero logico en el pin.
		OCR1AL = 0;
	    TIMER1_DE_TECLA = 0;
		return;
	  }
  }
}



ISR(TIMER2_COMPA_vect)
{

  if (timer2_toggle_count != 0)
  {
    // toggle the pin
    *timer2_pin_port ^= timer2_pin_mask;

    if (timer2_toggle_count > 0)
	{timer2_toggle_count--;}
	else
	{
		if( VIBRATO == 1)
		{
			//Serial.println(tiempo_vibrato);
			valor_sup_t2 = ((((float)numero_stev-1)*F_CPU)/((pow(frec_t2,2))*pres_t2*tiempo_vibrato))*1000;
			valor_inf_t2 = valor_sup_t2/numero_stev;
		
			switch(etapa_t2)
			{
				case 1 :					
					ocr_actual_t2 = ocr_actual_t2 + valor_sup_t2;
					OCR2A = ocr_actual_t2;
					if(ocr_actual_t2 >= ocr_sup_t2){etapa_t2 = 2;}
					return;	
				case 2 :
					ocr_actual_t2 = ocr_actual_t2 - valor_sup_t2;
					OCR2A = ocr_actual_t2;
					if(ocr_actual_t2 <= ocr_t2){etapa_t2 = 3;}
					return;					
				case 3 :
					ocr_actual_t2 = ocr_actual_t2 - valor_inf_t2;
					OCR2A= ocr_actual_t2;
					if(ocr_actual_t2 <= ocr_inf_t2){etapa_t2 = 4;}
					return;	
				case 4 :
					ocr_actual_t2 = ocr_actual_t2 + valor_inf_t2;
					OCR2A = ocr_actual_t2;
					if(ocr_actual_t2 >= ocr_t2){etapa_t2 = 1;}
					return;			
					
			}
		}
		else{ OCR2A = ocr_t2;}
			
	}
  
  return;
  }
  else
  {		timer2_toggle_delay = (float)(duracion_delay)/(2000*repeticiones_delay);
		
	  if((DELAY_FUN == 1) && (FIN_DELAY_T2 == 0))
	  {
		  
		  timer2_toggle_count_delay =  (float)timer2_toggle_count_delay + timer2_tiempo;
		  
		  //Serial.println(timer1_toggle_count_delay,10);
		  //Serial.println(parte_alta_t1);
		  
		  if (timer2_toggle_count_delay >= timer2_toggle_delay )
		  {
				
				parte_alta_t2 = ~parte_alta_t2;
				timer2_toggle_count_delay = 0;
				repeticiones_t2 ++;
		  }
		  
		  if(parte_alta_t2 )
		  {
			//Serial.println("hola");
			 *timer2_pin_port ^= timer2_pin_mask;		
		  }
		  
		  else{*timer2_pin_port &= ~(timer2_pin_mask);}

		  
		  if ( repeticiones_t2 == (repeticiones_delay*2) ){FIN_DELAY_T2 = 1;}
		  return;
	  }
	  else
	  {
	  
	  
	  
	   TIMSK2 &= ~(1 << OCIE2A);			  // Deshabilita la interrupcion
	   TCCR2B = (TCCR2B & 0b11111000) | 1; // Deshabilita el timer1
	   *timer2_pin_port &= ~(timer2_pin_mask);	  
	   OCR2A = 0;
	   TIMER2_DE_TECLA = 0;
	   return;
	  }

	   
  }
}




void TODO :: playPiano (void)
{
	
	//DEBUGIN2();
	
	noTono_interno();
	
	if(_MidiOn == 1)
	{
		if(_clave1)
		{
			if(Tecla_midiOn1 == 1)
			{
				noteOn(_canalConComando, frecuencia1_midi, _Velocidad_teclas);
				Tecla_midiOn1 = 0;
				Tecla_midiOff1 = 1;
			}
		}
		else{if(Tecla_midiOff1 == 1){noteOn(_canalConComando, frecuencia1_midi, 0);Tecla_midiOff1 =0;Tecla_midiOn1 =1;}}
				
		if(_clave2)
		{
			if(Tecla_midiOn2 == 1)
			{
				noteOn(_canalConComando, frecuencia2_midi, _Velocidad_teclas);
				Tecla_midiOn2 = 0;
				Tecla_midiOff2 = 1;
			}
		}else{if(Tecla_midiOff2 == 1){noteOn(_canalConComando, frecuencia2_midi, 0);Tecla_midiOff2 =0;Tecla_midiOn2 =1;}}
		
		if(_clave3)
		{
			if(Tecla_midiOn3 == 1)
			{
				noteOn(_canalConComando, frecuencia3_midi, _Velocidad_teclas);
				Tecla_midiOn3 = 0;
				Tecla_midiOff3 = 1;
			}
		}else{if(Tecla_midiOff3 == 1){noteOn(_canalConComando, frecuencia3_midi, 0);Tecla_midiOff3 =0;Tecla_midiOn3 =1;}}		
		
		if(_clave4)
		{
			if(Tecla_midiOn4 == 1)
			{
				noteOn(_canalConComando, frecuencia4_midi, _Velocidad_teclas);
				Tecla_midiOn4 = 0;
				Tecla_midiOff4 = 1;
			}
		}else{if(Tecla_midiOff4 == 1){noteOn(_canalConComando, frecuencia4_midi, 0);Tecla_midiOff4 =0;Tecla_midiOn4 =1;}}

		if(_clave5)
		{
			if(Tecla_midiOn5 == 1)
			{
				noteOn(_canalConComando, frecuencia5_midi, _Velocidad_teclas);
				Tecla_midiOn5 = 0;
				Tecla_midiOff5 = 1;
			}
		}else{if(Tecla_midiOff5 == 1){noteOn(_canalConComando, frecuencia5_midi, 0);Tecla_midiOff5 =0;Tecla_midiOn5 =1;}}

		if(_clave6)
		{
			if(Tecla_midiOn6 == 1)
			{
				noteOn(_canalConComando, frecuencia6_midi, _Velocidad_teclas);
				Tecla_midiOn6 = 0;
				Tecla_midiOff6 = 1;
			}
		}else{if(Tecla_midiOff6 == 1){noteOn(_canalConComando, frecuencia6_midi, 0);Tecla_midiOff6 =0;Tecla_midiOn6 =1;}}

		if(_clave7)
		{
			if(Tecla_midiOn7 == 1)
			{
				noteOn(_canalConComando, frecuencia7_midi, _Velocidad_teclas);
				Tecla_midiOn7 = 0;
				Tecla_midiOff7 = 1;
			}
		}else{if(Tecla_midiOff7 == 1){noteOn(_canalConComando, frecuencia7_midi, 0);Tecla_midiOff7 =0;Tecla_midiOn7 =1;}}

		if(_clave8)
		{
			if(Tecla_midiOn8 == 1)
			{
				noteOn(_canalConComando, frecuencia8_midi, _Velocidad_teclas);
				Tecla_midiOn8 = 0;
				Tecla_midiOff8 = 1;
			}
		}else{if(Tecla_midiOff8 == 1){noteOn(_canalConComando, frecuencia8_midi, 0);Tecla_midiOff8 =0;Tecla_midiOn8 =1;}}

	}
			

	
	

	if(_PianoON == 1)
	{
	
	if(TECLAS_AL_TIEMPO >= 3){TECLAS_AL_TIEMPO = 0; return;} // esto evita que se toquen 3 teclas al tiempo
		
	if (_SUSTAIN == 1) // sustain desactivado, se programa asi por la logica del pulsador
		
	{
 
		
		if(_clave1){COCONIO(1,_presc1,_ocr1,_frecuencia1);}

		if(_clave2){COCONIO(2,_presc2,_ocr2,_frecuencia2);}

		if(_clave3){COCONIO(3,_presc3,_ocr3,_frecuencia3);}
	
		if(_clave4){COCONIO(4,_presc4,_ocr4,_frecuencia4);}	
	
		if(_clave5){COCONIO(5,_presc5,_ocr5,_frecuencia5);}	
	
		if(_clave6){COCONIO(6,_presc6,_ocr6,_frecuencia6);}	
	
		if(_clave7){COCONIO(7,_presc7,_ocr7,_frecuencia7);}	

		if(_clave8){COCONIO(8,_presc8,_ocr8,_frecuencia8);}	
	
	}
	
	else	// la variable ESTADO_TECLA determina si la tecla esta siendo oprimida o si fue liberada
	{
		if(_clave1)	{	if( ESTADO_TECLA1 == 0){COCONIO(1,_presc1,_ocr1,_frecuencia1);	ESTADO_TECLA1 = 1;}	}
		else{ ESTADO_TECLA1 = 0;}
		
		if(_clave2)	{	if( ESTADO_TECLA2 == 0){COCONIO(2,_presc2,_ocr2,_frecuencia2);	ESTADO_TECLA2 = 1;}	}
		else{ ESTADO_TECLA2 = 0;}
		
		if(_clave3)	{	if( ESTADO_TECLA3 == 0){COCONIO(3,_presc3,_ocr3,_frecuencia3);	ESTADO_TECLA3 = 1;}	}
		else{ ESTADO_TECLA3 = 0;}
		
		if(_clave4)	{	if( ESTADO_TECLA4 == 0){COCONIO(4,_presc4,_ocr4,_frecuencia4);	ESTADO_TECLA4 = 1;}	}
		else{ ESTADO_TECLA4 = 0;}
		
		if(_clave5)	{	if( ESTADO_TECLA5 == 0){COCONIO(5,_presc5,_ocr5,_frecuencia5);	ESTADO_TECLA5 = 1;}	}
		else{ ESTADO_TECLA5 = 0;}
		
		if(_clave6)	{	if( ESTADO_TECLA6 == 0){COCONIO(6,_presc6,_ocr6,_frecuencia6);	ESTADO_TECLA6 = 1;}	}
		else{ ESTADO_TECLA6 = 0;}
		
		if(_clave7)	{	if( ESTADO_TECLA7 == 0){COCONIO(7,_presc7,_ocr7,_frecuencia7);	ESTADO_TECLA7 = 1;}	}
		else{ ESTADO_TECLA7 = 0;}
		
		if(_clave8)	{	if( ESTADO_TECLA8 == 0){COCONIO(8,_presc8,_ocr8,_frecuencia8);	ESTADO_TECLA8 = 1;}	}
		else{ ESTADO_TECLA8 = 0;}
		

	
		
	}
	
	}

	

	

	
}


	
int TODO :: TIMER_ACTIVO (int VALOR_TECLA)

{
	if( (TIMSK2 & (1 << OCIE2A)) &&  (TIMSK1 & (1 << OCIE1A)) ) // si los los timers estan activos
	{
		if((TIMER1_DE_TECLA == VALOR_TECLA) | (TIMER2_DE_TECLA == VALOR_TECLA))	{return 0;/*Hacer nada*/}
		else
		{
			if(TIMER_ULTIMO_USADO == 2){return 1;}//retorna 1 para usar timer1
			if(TIMER_ULTIMO_USADO == 1){return 2;}//retorna 2 para usar timer2
		}
		
	}
	
	
	if( TIMSK2 & (1 << OCIE2A) ) // si el timer 2 esta siendo usado
	{
		if(TIMER2_DE_TECLA == VALOR_TECLA){TIMER_ULTIMO_USADO = 2;return 0;}
		else
		{
			if(TIMER_ULTIMO_USADO == 2){return 1;}//retorna 1 para usar timer1
			if(TIMER_ULTIMO_USADO == 1){return 2;}//retorna 2 para usar timer2
		}
		
	}	
	
	
	
	if( TIMSK1 & (1 << OCIE1A) ) // si el timer 1 esta siendo usado
	{
		if(TIMER1_DE_TECLA == VALOR_TECLA){TIMER_ULTIMO_USADO = 1;return 0;}
		else
		{
			if(TIMER_ULTIMO_USADO == 2){return 1;}//retorna 1 para usar timer1
			if(TIMER_ULTIMO_USADO == 1){return 2;}//retorna 2 para usar timer2
		}
		
	}	
	
	return 1;	// Si ningun timer esta siendo usado retorne 1 para usar timer1
	
}	


void TODO :: COCONIO (int _VALOR_TECLA,uint8_t _prescalarbits, uint16_t OCRVALOR,uint16_t frecuencia)

{

	uint8_t TIMER_AVAILABLE;
	
	uint8_t		VALOR_TECLA = _VALOR_TECLA;
	uint8_t 	prescalarbits = _prescalarbits;
	uint16_t 	_OCRVALOR = OCRVALOR;


	
	TIMER_AVAILABLE = 	TIMER_ACTIVO(VALOR_TECLA);									 		
															 		
	
	if( TIMER_AVAILABLE == 1)
	
	{	PlayTimer1(prescalarbits,_OCRVALOR,VALOR_TECLA,frecuencia);return; }
	
	if( TIMER_AVAILABLE == 2)
	
	{	PlayTimer2(prescalarbits,_OCRVALOR,VALOR_TECLA,frecuencia);return; }
	

		
}





void TODO::noTono_interno(void)
{
	

	if(_SUSTAIN == 1){
		

		if((TIMSK2 & (1 << OCIE2A)) &&  (TIMSK1 & (1 << OCIE1A))) // Timer 1 y Timer 2 estan activos
		{
			PARAR_POR_TIMER(TIMER1_DE_TECLA,1);
			PARAR_POR_TIMER(TIMER2_DE_TECLA,0);
			return;
		}

		if(TIMSK1 & (1 << OCIE1A)) // Timer 1 esta activo
		{
			PARAR_POR_TIMER(TIMER1_DE_TECLA,1);
			return;
			

		}
		
		if(TIMSK2 & (1 << OCIE2A) ) // Timer 2 esta activo
		
		{
			PARAR_POR_TIMER(TIMER2_DE_TECLA,0);
			return;
		}
	}
	
	else{
		// Serial.print(" timer1_toggle_count:  ");
		// Serial.print(timer1_toggle_count);
		// Serial.print(" timer2_toggle_count:  ");
		// Serial.println(timer1_toggle_count);
		
		if((timer1_toggle_count < 0) | (timer2_toggle_count < 0))
		{
			Parar(0);	//detiene timer 2
			Parar(1);	//detiene timer 1
			timer1_toggle_count = 0; // Se colocan en 0 para asegurar que no se detengan cuando se oprimen 2
			timer2_toggle_count = 0; // teclas al tiempo y el sustain este en 1 y pase a 0	
		}
		
		
	}
	

		
	
}	

	


void TODO :: PlayTimer1 (uint16_t prescalarbits, uint16_t _OCRVALOR, int VALOR_TECLA,uint16_t frecuencia){
	
	    
		
		OCR1AL = _OCRVALOR;
		OCR1AH = 0;
		TCCR1B = (TCCR1B & 0b11111000) | prescalarbits;
		
		if( _SUSTAIN == 1)
		{timer1_toggle_count = -1; }
		else {
		timer1_toggle_count = (long)2 * frecuencia * duracion / 1000;
		
			if(DELAY_FUN == 1)
			{
				
				
				timer1_tiempo = (float)1/(2*frecuencia);
				timer1_toggle_count_delay = 0;
				FIN_DELAY_T1 = 0;
				repeticiones_t1 = 0;
				parte_alta_t1 = 0;
				
				
				
				// Serial.println(frecuencia);
				// Serial.println(timer1_toggle_delay,10);
				// Serial.println(timer1_tiempo,10);
				
			}
		}		

        bitWrite(TIMSK1, OCIE1A, 1); // Activamos las interrupciones
		
		if( VIBRATO == 1)
		{

			if( prescalarbits == 2 ){ pres_t1 = 8;}
			if( prescalarbits == 3 ){ pres_t1 = 64;}
			if( prescalarbits == 4 ){ pres_t1 = 256;}
			if( prescalarbits == 5 ){ pres_t1 = 1024;}
		
			
			ocr_t1 =  (float)F_CPU / frecuencia / 2 / pres_t1 - 1; 
			ocr_sup_t1 = ocr_t1 * numero_stev;
			ocr_inf_t1 = ocr_t1 / numero_stev;

			frec_t1 = frecuencia;
			
			ocr_actual_t1 = ocr_t1;
			etapa_t1 = 1;
		
		}
		else{ocr_t1 = _OCRVALOR;}
		
		TIMER_ULTIMO_USADO = 1;
		TIMER1_DE_TECLA = VALOR_TECLA; //indica que el timer1 fue usado por tecla X

		

}

void TODO :: PlayTimer2 (uint16_t prescalarbits, uint16_t _OCRVALOR, int VALOR_TECLA,uint16_t frecuencia){
	
		
		
		if(prescalarbits >= 4) prescalarbits = prescalarbits + 2;
		if(prescalarbits == 3) prescalarbits++;
		
		
		
	    OCR2A = _OCRVALOR;
		TCCR2B = (TCCR2B & 0b11111000) | prescalarbits;
		
		if( _SUSTAIN == 1)
		{timer2_toggle_count = -1; }
		else {
		timer2_toggle_count = (long)2 * frecuencia * duracion / 1000;
		
					if(DELAY_FUN == 1)
			{
				
				
				timer2_tiempo = (float)1/(2*frecuencia);
				timer2_toggle_count_delay = 0;
				FIN_DELAY_T2 = 0;
				repeticiones_t2 = 0;
				parte_alta_t2 = 0;
				
				
				
				//Serial.println(frecuencia);
				//Serial.println(timer1_toggle_delay,10);
				//Serial.println(timer1_tiempo,10);
				
			}
		}		
		//timer2_toggle_count = (F_CPU*duracion) / (1000*prescalarbits*_OCRVALOR);
        //timer2_toggle_count = -1; 	// Con esto el timer estara hasta que se apague manualmente
        bitWrite(TIMSK2, OCIE2A, 1); // Activamos las interrupciones
		
		  if( VIBRATO == 1)
		{
			if( prescalarbits == 2 ){ pres_t2 = 8;}
			if( prescalarbits == 4 ){ pres_t2 = 64;}
			if( prescalarbits == 6 ){ pres_t2 = 256;}
			if( prescalarbits == 7 ){ pres_t2 = 1024;}
		
			
			ocr_t2 =  (float)F_CPU / frecuencia / 2 / pres_t2 - 1; 
			ocr_sup_t2 = ocr_t2 * numero_stev;
			ocr_inf_t2 = ocr_t2 / numero_stev;

			frec_t2 = frecuencia;
			
			ocr_actual_t2 = ocr_t2;
			etapa_t2 = 1;	
		}
		else{ocr_t2 = _OCRVALOR;}
		
		TIMER_ULTIMO_USADO = 2;
		TIMER2_DE_TECLA = VALOR_TECLA;



}




void TODO :: noTono (void)

{
	
	if(_SUSTAIN == 1){
	Parar(0);	//detiene timer 2
	Parar(1);	//detiene timer 1
	}
	
	else{
	
	ESTADO_TECLA1 = 0;
	ESTADO_TECLA2 = 0;
	ESTADO_TECLA3 = 0;
	ESTADO_TECLA4 = 0;
	ESTADO_TECLA5 = 0;
	ESTADO_TECLA6 = 0;
	ESTADO_TECLA7 = 0;
	ESTADO_TECLA8 = 0;
	
	}
	
	
	apagar_Midi();
	
	
}


void TODO :: apagar_Midi (void)
{
	
	
	if(_MidiOn == 0)
	{
		return;
	}
	else
	{
		if (Tecla_midiOff1 == 1)
		{ 
			noteOn(_canalConComando, frecuencia1_midi, 0);
			Tecla_midiOn1 = 1;
			Tecla_midiOff1 = 0;
		}
		
		if (Tecla_midiOff2 == 1)
		{ 
			noteOn(_canalConComando, frecuencia2_midi, 0);
			Tecla_midiOn2 = 1;
			Tecla_midiOff2 = 0;
		}
		
		if (Tecla_midiOff3 == 1)
		{ 
			noteOn(_canalConComando, frecuencia3_midi, 0);
			Tecla_midiOn3 = 1;
			Tecla_midiOff3 = 0;
		}
		
		if (Tecla_midiOff4 == 1)
		{ 
			noteOn(_canalConComando, frecuencia4_midi, 0);
			Tecla_midiOn4 = 1;
			Tecla_midiOff4 = 0;
		}
		
		if (Tecla_midiOff5 == 1)
		{ 
			noteOn(_canalConComando, frecuencia5_midi, 0);
			Tecla_midiOn5 = 1;
			Tecla_midiOff5 = 0;
		}
		
		if (Tecla_midiOff6 == 1)
		{ 
			noteOn(_canalConComando, frecuencia6_midi, 0);
			Tecla_midiOn6 = 1;
			Tecla_midiOff6 = 0;
		}
		
		if (Tecla_midiOff7 == 1)
		{ 
			noteOn(_canalConComando, frecuencia7_midi, 0);
			Tecla_midiOn7 = 1;
			Tecla_midiOff7 = 0;
		}
		
		if (Tecla_midiOff8 == 1)
		{ 
			noteOn(_canalConComando, frecuencia8_midi, 0);
			Tecla_midiOn8 = 1;
			Tecla_midiOff8 = 0;
		}
			
	}

}



void TODO :: PARAR_POR_TIMER ( int timer_de_tecla, int timer_a_apagar)

{					

			switch(timer_de_tecla)
			{
				

			
			case 1:  if(_clave1){ return;/*Hacer nada*/} else{Parar(timer_a_apagar);}return;		
			case 2:  if(_clave2){ return;/*Hacer nada*/} else{Parar(timer_a_apagar);}return;			
			case 3:  if(_clave3){ return;/*Hacer nada*/} else{Parar(timer_a_apagar);}return;			
			case 4:  if(_clave4){ return;/*Hacer nada*/} else{Parar(timer_a_apagar);}return;			
			case 5:  if(_clave5){ return;/*Hacer nada*/} else{Parar(timer_a_apagar);}return;			
			case 6:  if(_clave6){ return;/*Hacer nada*/} else{Parar(timer_a_apagar);}return;			
			case 7:  if(_clave7){ return;/*Hacer nada*/} else{Parar(timer_a_apagar);}return;			
			case 8:  if(_clave8){ return;/*Hacer nada*/} else{Parar(timer_a_apagar);}return;
			}
}


void TODO::Parar(uint8_t timer_desactivado)
{
  switch (timer_desactivado)
  {

    case 0:
      TIMSK2 &= ~(1 << OCIE2A);			  // Deshabilita la interrupcion
	  TCCR2B = (TCCR2B & 0b11111000) | 1; // Deshabilita el timer1
	  digitalWrite(_pin_timer2, LOW);  
	  OCR2A = 0;
	  TIMER2_DE_TECLA = 0;
      return; 
	  
	  
    case 1:
      TIMSK1 &= ~(1 << OCIE1A);			    // Deshabilita la interrupcion
	  TCCR1B = (TCCR1B & 0b11111000) | 1; 	// Deshabilita el timer2
 	  digitalWrite(_pin_timer1, LOW);  
	  OCR1AL = 0;
	  TIMER1_DE_TECLA = 0;
      return; 

  }


}


void TODO :: VolumenMidi ( uint8_t _VolumPianoMidi){
	
	_Velocidad_teclas = _VolumPianoMidi;	
	
}

void TODO :: CanalMidiPiano ( uint8_t _CanalPianoMidi)
{
	
	_canalConComando = _CanalPianoMidi;
	_canalConComando --;
	_canalConComando &= 0b00001111;
	_canalConComando |= _modo_NoteOn;
	
	
}

void TODO :: ModoPiano ( bool _PianoON_, bool _SynthOn_, bool _MidiOn_)
{
	
	_PianoON = _PianoON_;
	_SynthOn = _SynthOn_;
	_MidiOn = _MidiOn_;
	
}

void TODO :: Syntetizador (bool Sustain, bool Vibrate, bool _efecto_delay)
{
	if(_SynthOn == 1){
	_SUSTAIN = Sustain;
	VIBRATO = Vibrate;
	DELAY_FUN = _efecto_delay;
	}
	


	
}	


void TODO :: TiempoVibrato (uint16_t vibratos)

{

	tiempo_vibrato = map(vibratos,0,1024,65,2000);
	
}
		

void TODO :: TiempoDelay (uint16_t tiempo_para_delay)
{
	
	//duracion_delay = 3000;
	
	if(tiempo_para_delay <= 50){duracion_delay = 0;}
	else
	{duracion_delay = map(tiempo_para_delay,100,1024,0,3000);}
	
	
	
	
}
		
	
void TODO :: Sustain (bool _sustain)
{
	if(_SynthOn == 1){

	if( _sustain == 1){ _SUSTAIN = 1;}
	else{_SUSTAIN = 0;}
	
	}

}	

void TODO :: Vibrato (bool _ViBrato)
{
	
	if(_ViBrato == 1){VIBRATO = true;}
	else {VIBRATO = false;}
	
	
}
		
void TODO :: Octavas (void)
{
	delay(200); //mientras suelta el boton
	
	int _AnD = 108;
	int _BnD = 72;
	
	frecuencia1_midi = frecuencia1_midi + 12;
	
	if(frecuencia1_midi >= _AnD){frecuencia1_midi = frecuencia1_midi -_BnD;}
	_frecuencia1 = ConverMidiToFrecu(frecuencia1_midi);
	frecuencia(_frecuencia1);
	_ocr1   = _ocr;
	_presc1 = _presc;		
		
	
	frecuencia2_midi = frecuencia2_midi + 12;
	
	if(frecuencia2_midi >= _AnD){frecuencia2_midi = frecuencia2_midi -_BnD;}
	_frecuencia2 = ConverMidiToFrecu(frecuencia2_midi);
	frecuencia(_frecuencia2);
	_ocr2   = _ocr;
	_presc2 = _presc;
	
	frecuencia3_midi = frecuencia3_midi + 12;
	
	if(frecuencia3_midi >= _AnD){frecuencia3_midi = frecuencia3_midi -_BnD;}
	_frecuencia3 = ConverMidiToFrecu(frecuencia3_midi);
	frecuencia(_frecuencia3);
	_ocr3   = _ocr;
	_presc3 = _presc;	


	frecuencia4_midi = frecuencia4_midi + 12;
	
	if(frecuencia4_midi >= _AnD){frecuencia4_midi = frecuencia4_midi -_BnD;}
	_frecuencia4 = ConverMidiToFrecu(frecuencia4_midi);
	frecuencia(_frecuencia4);
	_ocr4   = _ocr;
	_presc4 = _presc;


	frecuencia5_midi = frecuencia5_midi + 12;
	
	if(frecuencia5_midi >= _AnD){frecuencia5_midi = frecuencia5_midi -_BnD;}
	_frecuencia5 = ConverMidiToFrecu(frecuencia5_midi);
	frecuencia(_frecuencia5);
	_ocr5   = _ocr;
	_presc5 = _presc;


	frecuencia6_midi = frecuencia6_midi + 12;
	
	if(frecuencia6_midi >= _AnD){frecuencia6_midi = frecuencia6_midi -_BnD;}
	_frecuencia6 = ConverMidiToFrecu(frecuencia6_midi);
	frecuencia(_frecuencia6);
	_ocr6   = _ocr;
	_presc6 = _presc;


	frecuencia7_midi = frecuencia7_midi + 12;
	
	if(frecuencia7_midi >= _AnD){frecuencia7_midi = frecuencia7_midi -_BnD;}
	_frecuencia7 = ConverMidiToFrecu(frecuencia7_midi);
	frecuencia(_frecuencia7);
	_ocr7   = _ocr;
	_presc7 = _presc;


	frecuencia8_midi = frecuencia8_midi + 12;
	
	if(frecuencia8_midi >= _AnD){frecuencia8_midi = frecuencia8_midi -_BnD;}
	_frecuencia8 = ConverMidiToFrecu(frecuencia8_midi);
	frecuencia(_frecuencia8);
	_ocr8   = _ocr;
	_presc8 = _presc;

	
		

	
}
	
		
		
void TODO :: noteOn(int cmd, int pitch, int velocity) {
	
	// if(velocity == 0) 
	// { 
		// Serial.print("Se apago la tecla:   ");
		// Serial.println(pitch);
	// }
	
	// else 
	// {
		// Serial.print("Se prendio la tecla:   ");
		// Serial.println(pitch);
	// }
		

	
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}		
		
		
		
		
		
void TODO ::  Pulsador1(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_)
{
	

	
	if(_MidiOn == 1)
	{
	    if(_switchOn1 == 1){  
		
		_Banco1 = _Banco_;
		_Canal1 = _Canal_;
		_VelocitY1 = _VelocitY_;
	
		delayMicroseconds(800);
	
		_Canal1 --;_Canal1 &= 0b00001111;	_Canal1 |= _modo_BankOn;_Banco1 --;_VelocitY1 --;
	
		noteOn(_Canal1, _Banco1, _VelocitY1);
	
		_switchOn1 = 0;
		_switchOff1 = 1;
		}	
	
	}

}	

void TODO :: NoPulsador1()
{
		
	if(_MidiOn == 1)
	{
		if (_switchOff1 == 1)
		{    
		delayMicroseconds(2000);
		noteOn(_Canal1, _Banco1, 0);  
			_switchOn1 = 1; 
			_switchOff1 = 0;
		}
	}
}


		
		
		
		
		
void TODO ::  Pulsador2(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_)
{
	

	
	if(_MidiOn == 1)
	{
	    if(_switchOn2 == 1){  
		
		_Banco2 = _Banco_;
		_Canal2 = _Canal_;
		_VelocitY2 = _VelocitY_;
	
		delayMicroseconds(800);
	
		_Canal2 --;_Canal2 &= 0b00001111;	_Canal2 |= _modo_BankOn;_Banco2 --;_VelocitY2 --;
	
		noteOn(_Canal2, _Banco2, _VelocitY2);
	
		_switchOn2 = 0;
		_switchOff2 = 1;
		}	
	
	}

}	

void TODO :: NoPulsador2()
{
		
	if(_MidiOn == 1)
	{
		if (_switchOff2 == 1)
		{    
			delayMicroseconds(2000);
			noteOn(_Canal2, _Banco2, 0);  
			_switchOn2 = 1; 
			_switchOff2 = 0;
		}
	}
}



void TODO ::  Pulsador3(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_)
{
	

	
	if(_MidiOn == 1)
	{
	    if(_switchOn3 == 1){  
		
		_Banco3 = _Banco_;
		_Canal3 = _Canal_;
		_VelocitY3 = _VelocitY_;
	
		delayMicroseconds(800);
	
		_Canal3 --;_Canal3 &= 0b00001111;	_Canal3 |= _modo_BankOn;_Banco3 --;_VelocitY3 --;
	
		noteOn(_Canal3, _Banco3, _VelocitY3);
	
		_switchOn3 = 0;
		_switchOff3 = 1;
		}	
	
	}

}	

void TODO :: NoPulsador3()
{
		
	if(_MidiOn == 1)
	{
		if (_switchOff3 == 1)
		{    
			delayMicroseconds(2000);
			noteOn(_Canal3, _Banco3, 0);  
			_switchOn3 = 1; 
			_switchOff3 = 0;
		}
	}
}

void TODO ::  Pulsador4(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_)
{
	

	
	if(_MidiOn == 1)
	{
	    if(_switchOn4 == 1){  
		
		_Banco4 = _Banco_;
		_Canal4 = _Canal_;
		_VelocitY4 = _VelocitY_;
	
		delayMicroseconds(800);
	
		_Canal4 --;_Canal4 &= 0b00001111;	_Canal4 |= _modo_BankOn;_Banco4 --;_VelocitY4 --;
	
		noteOn(_Canal4, _Banco4, _VelocitY4);
	
		_switchOn4 = 0;
		_switchOff4 = 1;
		}	
	
	}

}	

void TODO :: NoPulsador4()
{
		
	if(_MidiOn == 1)
	{
		if (_switchOff4 == 1)
		{    
			delayMicroseconds(2000);
			noteOn(_Canal4, _Banco4, 0);  
			_switchOn4 = 1; 
			_switchOff4 = 0;
		}
	}
}

void TODO ::  Pulsador5(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_)
{
	

	
	if(_MidiOn == 1)
	{
	    if(_switchOn5 == 1){  
		
		_Banco5 = _Banco_;
		_Canal5 = _Canal_;
		_VelocitY5 = _VelocitY_;
	
		delayMicroseconds(800);
	
		_Canal5 --;_Canal5 &= 0b00001111;	_Canal5 |= _modo_BankOn;_Banco5 --;_VelocitY5 --;
	
		noteOn(_Canal5, _Banco5, _VelocitY5);
	
		_switchOn5 = 0;
		_switchOff5 = 1;
		}	
	
	}

}	

void TODO :: NoPulsador5()
{
		
	if(_MidiOn == 1)
	{
		if (_switchOff5 == 1)
		{    
			delayMicroseconds(2000);
			noteOn(_Canal5, _Banco5, 0);  
			_switchOn5 = 1; 
			_switchOff5 = 0;
		}
	}
}


void TODO ::  Pulsador6(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_)
{
	

	
	if(_MidiOn == 1)
	{
	    if(_switchOn6 == 1){  
		
		_Banco6 = _Banco_;
		_Canal6 = _Canal_;
		_VelocitY6 = _VelocitY_;
	
		delayMicroseconds(800);
	
		_Canal6 --;_Canal6 &= 0b00001111;	_Canal6 |= _modo_BankOn;_Banco6 --;_VelocitY6 --;
	
		noteOn(_Canal6, _Banco6, _VelocitY6);
	
		_switchOn6 = 0;
		_switchOff6 = 1;
		}	
	
	}

}	

void TODO :: NoPulsador6()
{
		
	if(_MidiOn == 1)
	{
		if (_switchOff6 == 1)
		{    
			delayMicroseconds(2000);
			noteOn(_Canal6, _Banco6, 0);  
			_switchOn6 = 1; 
			_switchOff6 = 0;
		}
	}
}



void TODO :: Potenciometro1 (uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_)
{
	
  
  
  tiempoX1 = millis();
  tiempoX1 = tiempoX1 - tiempoX1_Pa;

 if(tiempoX1 >= tiempo_descanso)
 {
	 
	_VelocitY_ = map(_VelocitY_,0,1024,0,127); 
	_Canal_ --;_Canal_ &= 0b00001111;	_Canal_ |= _modo_BankOn;_Banco_ --;
	noteOn(_Canal_, _Banco_, _VelocitY_);
	tiempoX1 = 0;
	tiempoX1_Pa = millis();
	
 }
	
	
	
}


void TODO :: Potenciometro2(uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_)
{
	
  
  
  tiempoX2 = millis();
  tiempoX2 = tiempoX2 - tiempoX2_Pa;

 if(tiempoX2 >= tiempo_descanso)
 {
	 
	_VelocitY_ = map(_VelocitY_,0,1024,0,127); 
	_Canal_ --;_Canal_ &= 0b00001111;	_Canal_ |= _modo_BankOn;_Banco_ --;
	noteOn(_Canal_, _Banco_, _VelocitY_);
	tiempoX2 = 0;
	tiempoX2_Pa = millis();
	
 }
	
	
	
}

void TODO :: Potenciometro3(uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_)
{
	
  
  
  tiempoX3 = millis();
  tiempoX3 = tiempoX3 - tiempoX3_Pa;

 if(tiempoX3 >= tiempo_descanso)
 {
	 
	_VelocitY_ = map(_VelocitY_,0,1024,0,127); 
	_Canal_ --;_Canal_ &= 0b00001111;	_Canal_ |= _modo_BankOn;_Banco_ --;
	noteOn(_Canal_, _Banco_, _VelocitY_);
	tiempoX3 = 0;
	tiempoX3_Pa = millis();
	
 }
	
	
	
}

void TODO :: Potenciometro4(uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_)
{
	
  
  
  tiempoX4 = millis();
  tiempoX4 = tiempoX4 - tiempoX4_Pa;

 if(tiempoX4 >= tiempo_descanso)
 {
	 
	_VelocitY_ = map(_VelocitY_,0,1024,0,127); 
	_Canal_ --;_Canal_ &= 0b00001111;	_Canal_ |= _modo_BankOn;_Banco_ --;
	noteOn(_Canal_, _Banco_, _VelocitY_);
	tiempoX4 = 0;
	tiempoX4_Pa = millis();
	
 }
	
	
	
}

void TODO :: Potenciometro5(uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_)
{
	
  
  
  tiempoX5 = millis();
  tiempoX5 = tiempoX5 - tiempoX5_Pa;

 if(tiempoX5 >= tiempo_descanso)
 {
	 
	_VelocitY_ = map(_VelocitY_,0,1024,0,127); 
	_Canal_ --;_Canal_ &= 0b00001111;	_Canal_ |= _modo_BankOn;_Banco_ --;
	noteOn(_Canal_, _Banco_, _VelocitY_);
	tiempoX5 = 0;
	tiempoX5_Pa = millis();
	
 }
	
	
	
}

void TODO :: Potenciometro6(uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_)
{
	
  
  
  tiempoX6 = millis();
  tiempoX6 = tiempoX6 - tiempoX6_Pa;

 if(tiempoX6 >= tiempo_descanso)
 {
	 
	_VelocitY_ = map(_VelocitY_,0,1024,0,127); 
	_Canal_ --;_Canal_ &= 0b00001111;	_Canal_ |= _modo_BankOn;_Banco_ --;
	noteOn(_Canal_, _Banco_, _VelocitY_);
	tiempoX6 = 0;
	tiempoX6_Pa = millis();
	
 }
	
	
	
}



void TODO :: LatenciaPotenciometros (int16_t LateQueLate)
{
	
	if( LateQueLate < 0) {tiempo_descanso = 20;}
	else{tiempo_descanso = LateQueLate;}	
	
	
}


void TODO :: ActivarResistencia(uint8_t _PIN_PARA_PULL_UP)
{
  pinMode(_PIN_PARA_PULL_UP,INPUT);
  digitalWrite(_PIN_PARA_PULL_UP,HIGH);
																																							
	
}


		
		
		
		

	
void TODO :: DEBUGIN2 (void){
	
long Cachama;

		if( _receivePin1 != 150  ){Cachama = Prueba(_receivePin1);Serial.print(" | Tecla1: ");Serial.print(Cachama);}
		if( _receivePin2 != 150  ){Cachama = Prueba(_receivePin2);Serial.print(" | Tecla2: ");Serial.print(Cachama);}
		if( _receivePin3 != 150  ){Cachama = Prueba(_receivePin3);Serial.print(" | Tecla3: ");Serial.print(Cachama);}
		if( _receivePin4 != 150  ){Cachama = Prueba(_receivePin4);Serial.print(" | Tecla4: ");Serial.print(Cachama);}
		if( _receivePin5 != 150  ){Cachama = Prueba(_receivePin5);Serial.print(" | Tecla5: ");Serial.print(Cachama);}
		if( _receivePin6 != 150  ){Cachama = Prueba(_receivePin6);Serial.print(" | Tecla6: ");Serial.print(Cachama);}
		if( _receivePin7 != 150  ){Cachama = Prueba(_receivePin7);Serial.print(" | Tecla7: ");Serial.print(Cachama);}
		if( _receivePin8 != 150  ){Cachama = Prueba(_receivePin8);Serial.print(" | Tecla8: ");Serial.print(Cachama);}
		Serial.println(" ");


	
	//delay(100);
}	



void TODO :: DEBUGIN (void)
{
 


		if( _receivePin1 != 150  ){ Nota1(); Serial.print(" | Tecla1: ");Serial.print(_clave1);}
		if( _receivePin2 != 150  ){ Nota2(); Serial.print(" | Tecla2: ");Serial.print(_clave2);}
		if( _receivePin3 != 150  ){ Nota3(); Serial.print(" | Tecla3: ");Serial.print(_clave3);}		
		if( _receivePin4 != 150  ){ Nota4(); Serial.print(" | Tecla4: ");Serial.print(_clave4);}		
		if( _receivePin5 != 150  ){ Nota5(); Serial.print(" | Tecla5: ");Serial.print(_clave5);}		
		if( _receivePin6 != 150  ){ Nota6(); Serial.print(" | Tecla6: ");Serial.print(_clave6);}		
		if( _receivePin7 != 150  ){ Nota7(); Serial.print(" | Tecla7: ");Serial.print(_clave7);}		
		if( _receivePin8 != 150  ){ Nota8(); Serial.print(" | Tecla8: ");Serial.print(_clave8);}		
		
		
		Serial.println(" ");


	
	delay(500);
	
}

  

















