




/*
	Proyect developed by Ing Duvan Camilo Puerto Barajas
	Creatvra SAS. Bogota Colombia 2019
	Please visit us at : https://creaturaestudio.com/
	Github: https://github.com/DuvanP
	
	This project is released over the GNU General Public License, version 2
	
	
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

#ifndef TODO_h
#define TODO_h

#include "Arduino.h"
#include <stdint.h>

#define PIN_TO_BASEREG(pin)             (portInputRegister(digitalPinToPort(pin)))
#define PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))

#define DIRECT_READ(base, mask)         (((*(base)) & (mask)) ? 1 : 0)
#define DIRECT_MODE_INPUT(base, mask)   ((*((base)+1)) &= ~(mask), (*((base)+2)) &= ~(mask))
#define DIRECT_MODE_OUTPUT(base, mask)  ((*((base)+1)) |= (mask))
#define DIRECT_WRITE_LOW(base, mask)    ((*((base)+2)) &= ~(mask))
#define DIRECT_WRITE_HIGH(base, mask)   ((*((base)+2)) |= (mask))

#define verDadero 0

#define Activar_Piano	1
#define Apagar_Piano	0
#define Activar_Sinte	1
#define Apagar_Sinte	0
#define Activar_Midi	1
#define Apagar_Midi	0


#define Activar_Sustain	1
#define Apagar_Sustain	0
#define Activar_Vibrato	1
#define Apagar_Vibrato	0
#define Activar_Delay	1
#define Apagar_Delay	0


#define Nota_Do_1_B	 23	
#define Nota_Do_1    24
#define Nota_Do_1_S  25
#define Nota_Re_1_B  25   
#define Nota_Re_1    26
#define Nota_Re_1_S  27
#define Nota_Mi_1_B  27
#define Nota_Mi_1    28
#define Nota_Mi_1_S  29
#define Nota_Fa_1_B  28
#define Nota_Fa_1    29
#define Nota_Fa_1_S  30
#define Nota_Sol_1_B 30
#define Nota_Sol_1   31
#define Nota_Sol_1_S 32
#define Nota_La_1_B  32
#define Nota_La_1    33
#define Nota_La_1_S  34
#define Nota_Si_1_B  34
#define Nota_Si_1    35
#define Nota_Si_1_S  36
////////////////////////////
#define Nota_Do_2_B  35
#define Nota_Do_2    36
#define Nota_Do_2_S  37
#define Nota_Re_2_B  37   
#define Nota_Re_2    38
#define Nota_Re_2_S  39
#define Nota_Mi_2_B  39
#define Nota_Mi_2    40
#define Nota_Mi_2_S  41
#define Nota_Fa_2_B  40
#define Nota_Fa_2    41
#define Nota_Fa_2_S  42
#define Nota_Sol_2_B 42
#define Nota_Sol_2   43
#define Nota_Sol_2_S 44
#define Nota_La_2_B  44
#define Nota_La_2    45
#define Nota_La_2_S  46
#define Nota_Si_2_B  46
#define Nota_Si_2    47
#define Nota_Si_2_S  48
////////////////////////////
#define Nota_Do_3_B  47
#define Nota_Do_3    48
#define Nota_Do_3_S  49
#define Nota_Re_3_B  49   
#define Nota_Re_3    50
#define Nota_Re_3_S  51
#define Nota_Mi_3_B  51
#define Nota_Mi_3    52
#define Nota_Mi_3_S  53
#define Nota_Fa_3_B  52
#define Nota_Fa_3    53
#define Nota_Fa_3_S  54
#define Nota_Sol_3_B 54
#define Nota_Sol_3   55
#define Nota_Sol_3_S 56
#define Nota_La_3_B  56
#define Nota_La_3    57
#define Nota_La_3_S  58
#define Nota_Si_3_B  58
#define Nota_Si_3    59
#define Nota_Si_3_S  60
//////////////////////////// Bien
#define Nota_Do_4_B  59
#define Nota_Do_4    60
#define Nota_Do_4_S  61
#define Nota_Re_4_B  61 
#define Nota_Re_4    62
#define Nota_Re_4_S  63
#define Nota_Mi_4_B  63
#define Nota_Mi_4    64
#define Nota_Mi_4_S  65
#define Nota_Fa_4_B  64
#define Nota_Fa_4    65
#define Nota_Fa_4_S  66
#define Nota_Sol_4_B 66
#define Nota_Sol_4   67
#define Nota_Sol_4_S 68
#define Nota_La_4_B  68
#define Nota_La_4    69
#define Nota_La_4_S  70
#define Nota_Si_4_B  70
#define Nota_Si_4    71
#define Nota_Si_4_S  72
////////////////////////////
#define Nota_Do_5_B  71
#define Nota_Do_5    72
#define Nota_Do_5_S  73
#define Nota_Re_5_B  73   
#define Nota_Re_5    74
#define Nota_Re_5_S  75
#define Nota_Mi_5_B  75
#define Nota_Mi_5    76
#define Nota_Mi_5_S  77
#define Nota_Fa_5_B  76
#define Nota_Fa_5    77
#define Nota_Fa_5_S  78
#define Nota_Sol_5_B 78
#define Nota_Sol_5   79
#define Nota_Sol_5_S 80
#define Nota_La_5_B  80
#define Nota_La_5    81
#define Nota_La_5_S  82
#define Nota_Si_5_B  82
#define Nota_Si_5    83
#define Nota_Si_5_S  84
////////////////////////////
#define Nota_Do_6_B  83
#define Nota_Do_6    84
#define Nota_Do_6_S  85
#define Nota_Re_6_B  85   
#define Nota_Re_6    86
#define Nota_Re_6_S  87
#define Nota_Mi_6_B  87
#define Nota_Mi_6    88
#define Nota_Mi_6_S  89
#define Nota_Fa_6_B  88
#define Nota_Fa_6    89
#define Nota_Fa_6_S  90
#define Nota_Sol_6_B 90
#define Nota_Sol_6   91
#define Nota_Sol_6_S 92
#define Nota_La_6_B  92
#define Nota_La_6    93
#define Nota_La_6_S  94
#define Nota_Si_6_B  94
#define Nota_Si_6    95
#define Nota_Si_6_S  96
////////////////////////////Bien 
#define Nota_Do_7_B  95
#define Nota_Do_7    96
#define Nota_Do_7_S  97
#define Nota_Re_7_B  97   
#define Nota_Re_7    98
#define Nota_Re_7_S  99
#define Nota_Mi_7_B  99
#define Nota_Mi_7    100
#define Nota_Mi_7_S  101
#define Nota_Fa_7_B  100
#define Nota_Fa_7    101
#define Nota_Fa_7_S  102
#define Nota_Sol_7_B 102
#define Nota_Sol_7   103
#define Nota_Sol_7_S 104
#define Nota_La_7_B  104
#define Nota_La_7    105
#define Nota_La_7_S  106
#define Nota_Si_7_B  106
#define Nota_Si_7    107
#define Nota_Si_7_S  108
////////////////////////////Bien 
#define Nota_Do_8_B  107
#define Nota_Do_8    108
#define Nota_Do_8_S  109
#define Nota_Re_8_B  109  
#define Nota_Re_8    110
#define Nota_Re_8_S  111
#define Nota_Mi_8_B  111
#define Nota_Mi_8    112
#define Nota_Mi_8_S  113
#define Nota_Fa_8_B  112
#define Nota_Fa_8    113
#define Nota_Fa_8_S  114
#define Nota_Sol_8_B 114
#define Nota_Sol_8   115
#define Nota_Sol_8_S 116
#define Nota_La_8_B  116
#define Nota_La_8    117
#define Nota_La_8_S  118
#define Nota_Si_8_B  118
#define Nota_Si_8    119
#define Nota_Si_8_S  120




	








// library interface description
class TODO
{
	
//------------------ P U B L I C ------------------||
	
	
  public:

  
	// La funcion Fiesta hace las configuraciones iniciales que necesita la libreria para iniciar
	void Fiesta(int8_t tonePin1, int8_t tonePin2, int8_t sendPin);

	void Calibracion ( int32_t CALI = 50 );	// se usa para calibrar las teclas segun la persona que toque el piano
	
	// Las funciones Tecla configuran la frecuencia y el pin digital de cada tecla del piano, solo se pueden tener maximo 8
	void Tecla1(int8_t receivePin1, uint16_t frecuencia1=0);
	void Tecla2(int8_t receivePin2, uint16_t frecuencia2);
	void Tecla3(int8_t receivePin3, uint16_t frecuencia3);
	void Tecla4(int8_t receivePin4, uint16_t frecuencia4);
	void Tecla5(int8_t receivePin5, uint16_t frecuencia5);
	void Tecla6(int8_t receivePin6, uint16_t frecuencia6);
	void Tecla7(int8_t receivePin7, uint16_t frecuencia7);
	void Tecla8(int8_t receivePin8, uint16_t frecuencia8);
	

		// Las funciones Nota# determinan si la persona toco o no toco una tecla del piano
	bool Nota1 (void);
	bool Nota2 (void);
	bool Nota3 (void);
	bool Nota4 (void);
	bool Nota5 (void);
	bool Nota6 (void);
	bool Nota7 (void);
	bool Nota8 (void);

		
	long Prueba(int8_t _pin);	// Prueba es la funcion que obtiene el tiempo que se usa para determinar si alguien toco una sola tecla del piano
	void playPiano(void);	// Esta funcion es la encargada de reproducir  el sonido del piano en los Timers.
	void noTono(void);		// noTono se encarga de detener cualquier sonido si nadie esta tocando el piano.
	void ModoPiano ( bool _PianoON_, bool _SynthOn_, bool _MidiOn_); // como una de las funciones principales, activa o desactiva el piano, el sintetizado y el modo MIDI
	
	
	
	void Syntetizador (bool Sustain = 0,bool Vibrate = 0,bool _efecto_delay=0); 	// Funcion que habilita el Sustain, el Vibrato y el Delay del sintetizador
	void TiempoVibrato (uint16_t vibratos);		// funcion que controla el tiempo del vibrato, Esta diseñada para ser usada con un Potenciometro
	void TiempoDelay (uint16_t tiempo_para_delay); // Funcion que controla el tiempo Delay de la funcion delay, esta diseñada para ser usada con un potenciometro
	void Octavas (void);  // La funcion Octavas sube una octaba a cualquier frecuencia que tengan las 8 teclas , cuando llega a su limite, retorna a una frecuencia baja
	void Sustain (bool _sustain);	//La funcion Sutain  activa o desactiva el sustain, osea que el sonido se mantenga cuando uno toca el piano
	void Vibrato (bool _ViBrato);	// la funcion Vibrato activa o desactiva el vibrato, osea que el vibrato se mantenga cuando uno toca el piano
	

	
	void noteOn(int cmd, int pitch, int velocity);	// Funcion encargada de enviar el mensaje MIDI a cualquier dispositivo que quiera recibirlo
	void VolumenMidi ( uint8_t _VolumPianoMidi);	// funcion que configura el volumen de las teclas MIDI en el programa DAW
	void CanalMidiPiano ( uint8_t _CanalPianoMidi); // esta funcion le permite al usuario seleccionar uno de los 16 canales MIDI para usar en el DAW

	
	
	void DEBUGIN (void);	// la funcion DEBUGUIN es la que permite hacer la calibracion, con esta funcion el usuario puede saber que numero escoger para CALI 
	void DEBUGIN2 (void);	// Esta funcion imprime en el puerto serial Los valores reales del tiempo de cada tecla que este configurada

	
	void Pulsador1(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_);	 // las funciones Pulsador#, se usan para poder introducir un pulsador MIDI al programa DAW
	void Pulsador2(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_);
	void Pulsador3(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_);
	void Pulsador4(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_);	 
	void Pulsador5(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_);
	void Pulsador6(uint8_t _Canal_, uint8_t _Banco_, uint8_t _VelocitY_);
	
	void NoPulsador1();		// LAs funciones NoPulsador# se usan para apagar el pulsador midi que este activo en el momento
	void NoPulsador2();
	void NoPulsador3();	
	void NoPulsador4();		
	void NoPulsador5();
	void NoPulsador6();	
	
	void Potenciometro1 (uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_);	// las funciones Potenciometro# se usan para poder manejar un potenciometro en los programas DAW
	void Potenciometro2 (uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_);
	void Potenciometro3 (uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_);	
	void Potenciometro4 (uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_);
	void Potenciometro5 (uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_);	
	void Potenciometro6 (uint8_t _Canal_, uint8_t _Banco_, uint16_t _VelocitY_);

	
	void LatenciaPotenciometros (int16_t LateQueLate);	// Esta funcion permite ajustar cada cuanto se va a leer el puerto analogo por el cual el potenciometro esta conectado
														// este tiempo debe ser prudente para evitar que el Arduino no pierda tiempo leyendo un potenciometro que no va a cambiar en tan poco tiempo	
														
	void ActivarResistencia (uint8_t _PIN_PARA_PULL_UP);		// esta funcion se diseño debido a que en arduino no se puede activar la resistencia de pull up directamente entonces esta lo hace
	
	private:
  
	void apagar_Midi (void); // Esta funcion apaga el sonido de la tecla Midi que no este sonando pero que si estaba sonando antes.

	
	// esta funcion es especial, debido a que las notas musicales que se introducen en las funciones Tecla# son un arreglo de variables previamente
	// establecidas, estas corresponden a las notas musicales en formato MIDI, pero el microcontrolador no las reconoce, por esta razon es necesario
	// convertilas a un formato que los modulos Timer puedan entender. Para esto existe la funcion ConverMidiToFrecu. 
  	float ConverMidiToFrecu ( float MidiFrecu ); 
  
	void noTono_interno(void); // Esta funcion es la que evita que las teclas sigan sonando si la persona ya no las esta tocando. por ende es la que apaga el TIMER
  

	void SenseOneCycle(void);	// Esta es la funcion principal de la capacitancia, Es la base de esta tecnologia.
 	void frecuencia ( uint16_t frequency); // esta funcion transforma una frecuencia en numero a las exigencias del modulo del timer ( osea el Prescaler y el OCRVALOR )
	
	int TIMER_ACTIVO (int VALOR_TECLA);	// Esta funcion controla cual Timer usar, debido a que solo se pueden reproducir 2 sonidos a la vez, es necesario 
										// que una funcion controle el correcto funcionamiento, para evitar que el piano se bloqueé
	
	
	void PlayTimer1 (uint16_t prescalarbits, uint16_t _OCRVALOR, int VALOR_TECLA, uint16_t frecuencia); // Esta funcion reproduce el sonido con el TIMER1
	void PlayTimer2 (uint16_t prescalarbits, uint16_t _OCRVALOR, int VALOR_TECLA, uint16_t frecuencia);	// Esta funcion reproduce el sonido con el TIMER2
	
	void COCONIO (int _VALOR_TECLA,uint8_t _prescalarbits, uint16_t OCRVALOR, uint16_t frecuencia); // esta funcion Controla todas las demas funciones que se encargan de producir los tonos en los TImers


	void Parar(uint8_t timer_desactivado);	// Esta funcion es la que Literalmente Detiene los Timers

	void PARAR_POR_TIMER ( int timer_de_tecla, int timer_a_apagar); // Esta funcion controla cual Timer detener, dependiendo si la persona ya no toca el piano o si ya no toca la misma tecla
	


};

#endif
