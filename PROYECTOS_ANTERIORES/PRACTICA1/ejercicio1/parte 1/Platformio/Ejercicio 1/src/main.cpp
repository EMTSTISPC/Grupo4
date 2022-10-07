#include <Arduino.h>

/* Definiciones */

/* Variables */

bool flagLectura = false; // Flag para indicar una lectura de datos desde el puerto serial
byte contadorLecturas = 0; // Contador de casos de ingreso de datos

int num1=0,num2=0,suma=0; // Variables para almacenar los datos ingresados por el usuario

/* SETUP */
void setup() {
  Serial.begin(9600); // Inicializacion del puerto serial

}

void loop() {


  if(!flagLectura){
    switch(contadorLecturas){
      case 0: // Ingresa el primer valor
        Serial.print("Ingrese el primer numero: ");
        // contadorLecturas++; No debe ir aca
        break;
      case 1: // Ingresa el segundo valor
        Serial.print("Ingrese el segundo numero: ");
        // contadorLecturas++; No debe ir aca
        break;
      default: // Muestra la suma de los dos valores
        suma = num1 + num2;
        Serial.println("");
        Serial.print("La suma es: ");
        Serial.println(suma); 
        contadorLecturas++;
        //Serial.println(contadorLecturas);
        break;    
    }
    flagLectura = true;                   // Cambio de flag para que no se repita el mensaje
  }

  while(!Serial.available()){
    // Espera a que el usuario ingrese un valor
  }

  if(Serial.available()){
    switch(contadorLecturas){
      case 0: // Ingresa el primer valor
        Serial.println(num1 = Serial.parseInt());
        contadorLecturas++;
        //Serial.println(contadorLecturas);
        break;
      case 1: // Ingresa el segundo valor
        Serial.println(num2 = Serial.parseInt());
        contadorLecturas++;
        //Serial.println(contadorLecturas);
        break;
    }
    if(contadorLecturas < 3) flagLectura = false;                  // Cambio de flag para que se repita el mensaje de ingreso de datos
  }
  
}