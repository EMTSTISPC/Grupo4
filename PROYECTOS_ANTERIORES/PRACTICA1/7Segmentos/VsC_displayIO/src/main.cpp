#include <Arduino.h>

#define tiempo 300

void setup() {

//  Serial.begin(9600);

  //DDRX;    Configuara el puerto X == 1 como salida y X == 0 como entrada
  //PINX;    Lee el estado del puerto X
  //PORTX;   Escribe el estado del puerto X

  DDRB = 0xFF; // Configura el puerto B como salida

//  DDRC = 0xFF; // Configura el puerto C como salida

  DDRD = 0xFF; // Configura el puerto D como salida

}

void loop() {


  for(int i=0; i<16; i++){          // i++ = i = i + 1

    switch(i){
      case 0:
        PORTB = i; // PORTB = i;
        PORTD = 0x3f; // PORTD = 0x3f;
        delay(tiempo);
        break;
      case 1:
        PORTB = i; // PORTB = i;
        PORTD = 0x06; // PORTD = 0x06;
        delay(tiempo);
        break;
      case 2:
        PORTB = i; // PORTB = i;
        PORTD = 0x5b; // PORTD = 0x5b;
        delay(tiempo);
        break;
      case 3:
        PORTB = i; // PORTB = i;
        PORTD = 0x4f; // PORTD = 0x4f;
        delay(tiempo);
        break;
      case 4:
        PORTB = i; // PORTB = i;
        PORTD = 0x66; // PORTD = 0x66;
        delay(tiempo);
        break;
      case 5:
        PORTB = i; // PORTB = i;
        PORTD = 0x6d; // PORTD = 0x6d;
        delay(tiempo);
        break;
      case 6:
        PORTB = i; // PORTB = i;
        PORTD = 0x7d; // PORTD = 0x7d;
        delay(tiempo);
        break;
      case 7:
        PORTB = i; // PORTB = i;
        PORTD = 0x07; // PORTD = 0x07;
        delay(tiempo);
        break;
      case 8:
        PORTB = i; // PORTB = i;
        PORTD = 0x7f; // PORTD = 0x7f;
        delay(tiempo);
        break;
      case 9:
        PORTB = i; // PORTB = i;
        PORTD = 0x6f; // PORTD = 0x6f;
        delay(tiempo);
        break;
      case 10:
        PORTB = i; // PORTB = i;
        PORTD = 0x77; // PORTD = 0x77;
        delay(tiempo);
        break;
      case 11:
        PORTB = i; // PORTB = i;
        PORTD = 0x7c; // PORTD = 0x7c;
        delay(tiempo);
        break;
      case 12:
        PORTB = i; // PORTB = i;
        PORTD = 0x39; // PORTD = 0x39;
        delay(tiempo);
        break;
      case 13:
        PORTB = i; // PORTB = i;
        PORTD = 0x5e; // PORTD = 0x5e;
        delay(tiempo);
        break;
      case 14:
        PORTB = i; // PORTB = i;
        PORTD = 0x79; // PORTD = 0x79;
        delay(tiempo);
        break;
      case 15:
        PORTB = i; // PORTB = i;
        PORTD = 0x71; // PORTD = 0x71;
        delay(tiempo);
        break;
    }

  }

  // PORTD = 0x3F; // Escribo el puerto C con el valor 0x3F 
  // delay(tiempo);
  // PORTD = 0x06; // Escribo el puerto C con el valor 0x06
  // delay(tiempo);
  // PORTD = 0x5B; // Escribo el puerto C con el valor 0x5B
  // delay(tiempo);
  // PORTD = 0x4F; // Escribo el puerto C con el valor 0x4F
  // delay(tiempo);
  // PORTD = 0x66; // Escribo el puerto C con el valor 0x66
  // delay(tiempo);
  // PORTD = 0x6D; // Escribo el puerto C con el valor 0x6D
  // delay(tiempo);
  // PORTD = 0x7D; // Escribo el puerto C con el valor 0x7D
  // delay(tiempo);
  // PORTD = 0x07; // Escribo el puerto C con el valor 0x07
  // delay(tiempo);
  // PORTD = 0x7F; // Escribo el puerto C con el valor 0x7F
  // delay(tiempo);
  // PORTD = 0x6F; // Escribo el puerto C con el valor 0x6F
  // delay(tiempo);
  // PORTD = 0x77; // Escribo el puerto C con el valor 0x77
  // delay(tiempo);
  // PORTD = 0x7C; // Escribo el puerto C con el valor 0x7C
  // delay(tiempo);
  // PORTD = 0x39; // Escribo el puerto C con el valor 0x39 
  // delay(tiempo);
  // PORTD = 0x5E; // Escribo el puerto C con el valor 0x5E
  // delay(tiempo);
  // PORTD = 0x79; // Escribo el puerto C con el valor 0x79
  // delay(tiempo);
  // PORTD = 0x71; // Escribo el puerto C con el valor 0x71
  // delay(tiempo);




  // PORTB = B00000000; // Pone el puerto B en 0
  // delay(tiempo);
  // PORTB = B00000001; // Escribe el estado del puerto B
  // delay(tiempo);
  // PORTB = B00000010; // Pone el puerto B en 2
  // delay(tiempo);
  // PORTB = B00000011; // Pone el puerto B en 3
  // delay(tiempo);
  // PORTB = B00000100; // Pone el puerto B en 4
  // delay(tiempo);
  // PORTB = B00000101; // Pone el puerto B en 5
  // delay(tiempo);
  // PORTB = B00000110; // Pone el puerto B en 6
  // delay(tiempo);
  // PORTB = B00000111; // Pone el puerto B en 7
  // delay(tiempo);
  // PORTB = B00001000; // Pone el puerto B en 8
  // delay(tiempo);
  // PORTB = B00001001; // Pone el puerto B en 9
  // delay(tiempo);
  // PORTB = B00001010; // Pone el puerto B en 10
  // delay(tiempo);
  // PORTB = B00001011; // Pone el puerto B en 11
  // delay(tiempo);
  // PORTB = B00001100; // Pone el puerto B en 12
  // delay(tiempo);
  // PORTB = B00001101; // Pone el puerto B en 13
  // delay(tiempo);
  // PORTB = B00001110; // Pone el puerto B en 14
  // delay(tiempo);
  // PORTB = B00001111; // Pone el puerto B en 15
  // delay(tiempo);

}