int n;
int prom=0;
void setup() {
  Serial.begin(9600);
}
void loop() {
 
  Serial.println("Escriba la cantidad de números que va a ingresar");
  while (!Serial.available()); // Espera datos
  n = (Serial.readString()).toInt();
  int numeros [n]; //arreglo para guardar datos
 
  for (int i = 0; i <= n - 1; i++) {
     Serial.print("Numero ");
     Serial.print(i+1);
     Serial.print(" = ");
    while (!Serial.available()); // Esperamos a que ingrese num
    
    numeros [i] = (Serial.readString()).toInt();
    Serial.println(numeros[i]);
  }
  for (int i = 0; i <= n - 1; i++) { //suma todos los datos
    prom = prom + numeros [i];
  }
  Serial.print("La media es = ");
  prom = prom / n; 
  Serial.println (prom);
  
}
