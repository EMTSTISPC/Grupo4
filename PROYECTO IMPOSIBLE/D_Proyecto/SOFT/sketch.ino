#include <analogWrite.h>

//Placa base ESP32

const int ledVerde = 13;
const int ledAmarillo = 12;
const int ledRojo = 14;
const int ledPeaton = 15;
const int buzzer = 32;
const int trigger=33; 
const int echo= 2; 
int LDR= 34; //Pin donde conectaremos el LDR nombre que le das a la fotorresistencia
int lectura; //variable para almacenar el resultado de la fotorresistencia
int salida;
int dely = 4000;
long dist, duracion;



void setup() {
  
  Serial.begin(9600);     //iniciar puerto serial
  pinMode(ledVerde, OUTPUT);   //definir pin como salida
  pinMode(ledAmarillo, OUTPUT);   
  pinMode(ledRojo, OUTPUT);   
  pinMode(ledPeaton, OUTPUT);   
  pinMode(buzzer, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);

 
}

  

void loop() {
  // Codigo que se repite ciclicamente:
  salida = 40;
  
  lectura = analogRead(LDR);  //Conversion Analog-Dig y lo almacena
  Serial.println (lectura);   //Muestra en la terminal el valor
  delay(500);   //Pausa para poder visualizar el resultado
  
  

  if(lectura<300){
    Serial.println("Es de DIA");
    medirTrafico();
    configDia();
  }
  else{
    Serial.println("Es de NOCHE");
    configNoche();
  }
  delay(400);
  
}

void medirTrafico(){
  digitalWrite(trigger,LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigger,HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigger,LOW); 
  duracion=pulseIn(echo,HIGH);
  dist=(duracion/2)/29; //SE HACE LA CONVERSION A CM
  Serial.print("Distancia 1 = ");
  Serial.print(dist); 
  Serial.println(" cm");
}

void configDia(){
  if(dist<100){
    Serial.println("Hay trafico");
  	configDiaTrafico();
  }
  else{
    Serial.println("NO hay trafico");
    configDiaSINTrafico();
  }
  Serial.write(10); //NUEVA LINEA 
  delay(400); //PEQUEÑO DELAY
}

void configDiaSINTrafico() {
  digitalWrite(ledVerde, HIGH);
  delay(dely);
  digitalWrite(ledVerde, LOW);
  delay(300);
  digitalWrite(ledVerde, HIGH);
  delay(300);
  digitalWrite(ledVerde, LOW);
  delay(300);
  digitalWrite(ledVerde, HIGH);
  delay(300);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, HIGH);
  delay(800);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledPeaton, HIGH);
  analogWrite(buzzer,salida);
  delay(dely);
  digitalWrite(ledPeaton, LOW);
  analogWrite(buzzer,0);
  digitalWrite(ledRojo, LOW); 
}

void configDiaTrafico() {
  digitalWrite(ledVerde, HIGH);
  delay(dely+4000);
  digitalWrite(ledVerde, LOW);
  delay(300);
  digitalWrite(ledVerde, HIGH);
  delay(300);
  digitalWrite(ledVerde, LOW);
  delay(300);
  digitalWrite(ledVerde, HIGH);
  delay(300);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, HIGH);
  delay(800);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledPeaton, HIGH);
  analogWrite(buzzer, salida);
  delay(dely-1000);
  digitalWrite(ledPeaton, LOW);
  analogWrite(buzzer, 0);
  digitalWrite(ledRojo, LOW);
}

void configNoche() {
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledAmarillo, HIGH);
  digitalWrite(ledPeaton, HIGH);
  delay(300);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledPeaton, LOW);
  delay(300);
  digitalWrite(ledAmarillo, HIGH);
  digitalWrite(ledPeaton, HIGH);
  delay(300);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledPeaton, LOW);
  delay(300);
  digitalWrite(ledAmarillo, HIGH);
  digitalWrite(ledPeaton, HIGH);
  delay(300);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledPeaton, LOW);
  delay(300);
  digitalWrite(ledRojo, LOW);


}