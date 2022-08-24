#include <Arduino.h>

/* Definiciones */

/* Variables */

bool flagLectura = false; // Flag para indicar una lectura de datos desde el puerto serial
byte contadorLecturas = 0; // Contador de casos de ingreso de datos

String nombre = "";
String apellido = "";
String direccion = "";
int celular = 0;

/* SETUP */
void setup() {
  Serial.begin(9600); // Inicializacion del puerto serial
}

void loop() {

  if(!flagLectura){
    switch(contadorLecturas){
      case 0: 
        Serial.print("Ingrese el Nombre ........: ");
        break;
      case 1: 
        Serial.print("Ingrese el Apellido ......: ");
        break;
       case 2: 
        Serial.print("Ingrese la Direccion .....: ");
        break;
      case 3: 
        Serial.print("Ingrese el nro de Celular : ");
        break;
      default: // Muestra Resultados
        Serial.println("");
        Serial.print("El Nombre es          : ");
        Serial.println(nombre); 
        Serial.print("El Apellido es        : ");
        Serial.println(apellido); 
        Serial.print("La Direccion es       : ");
        Serial.println(direccion); 
        Serial.print("El nro de Celular es  : ");
        Serial.println(celular); 
        contadorLecturas++;
        break;    
    }
    flagLectura = true;                   // Cambio de flag para que no se repita el mensaje
  }

  while(!Serial.available()){
    // Espera a que el usuario ingrese un valor
  }

  if(Serial.available()){
    switch(contadorLecturas){
      case 0:  
        Serial.println(nombre = Serial.readString());
        contadorLecturas++;
        break;
      case 1:  
        Serial.println(apellido = Serial.readString());
        contadorLecturas++;
        break;
      case 2:  
        Serial.println(direccion = Serial.readString());
        contadorLecturas++;
        break;
      case 3:  
        Serial.println(celular = Serial.parseInt());
        contadorLecturas++;
         
        break;
    }
    if(contadorLecturas < 5) flagLectura = false; // Cambio de flag para que se repita el mensaje de ingreso de datos
  }
  
}