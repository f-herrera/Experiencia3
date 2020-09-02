/* 

Lab 15125

###################
#   Descripcion   #
###################


  Sensor Ping))) - Fade Led
  
   Este sketch lee el dato obtenido por el sensor ultrasonico PING))) y enciende un led 
   de forma gradual (fade).
   
   los valores aparecen en el monitor serie para poder calibrar.
      
    El circuito:
     * +V conectado a sensor PING))) en +5V
     * GND conectado a sensor PING))) en GND (ground)
     * SIG conectado a sensor PING))) en pin digital 7
     * LED conectado a pin 9 (PWM)

 */

 
// VARIABLES GLOBALES INICIALIZADAS
 const int pingPin = 7;  // se define pingPin como el pin 7 del arduino, que luego sera utilizado como pin de comunicacion con el sensor
 const int ledPin = 9;   // se define ledPin como el pin 9 del arduino, que luego sera utilizado como pin de coneccion un led
// VARIABLES GLOBALES NO INICIALIZADAS
 int  fadeValue, fadeValue2 ;
 
void setup()

  {
      // se inicializa comunicacion serial:
         Serial.begin(9600);   // velocidad de comunicacion del arduino con el computador 
   }
 
void loop()
 {

// Obtiene distancia 
  /*
   establece variables para duracion del ping 
   y el resultado de la distancia en centimetros
  */
   long duration, inches, cm, cm2; // se establece la funciones "duration, inches, cm, cm2" como numeros enteros
 
   /*
   El triggered PING))) es un pulso HIGH de 2 microsegundos.
   un pulso LOW posteriormente para asegurarse que limpia el pulso HIGH
   */
     pinMode(pingPin, OUTPUT);   //se define el pingPin como salida ya que el sensor emite un pulso para poder realizar la medicion 
     digitalWrite(pingPin, LOW);   
     delayMicroseconds(2);
     digitalWrite(pingPin, HIGH);   //aqui la emicion de dicho pulso
     delayMicroseconds(5);
     digitalWrite(pingPin, LOW);   //se limpia el pulso asegurando que se apague
 
  /*
   El mismo pin es usado para leer la señal de PING))) del pulso HIGH
   pulso cuya duración es el tiempo (en microsegundos) desde el envío 
   del ping hasta la recepción de su eco desde un objeto.
  */
    pinMode(pingPin, INPUT);   //aqui se define el pingPin como entrada ya que el sensor recibe el eco del primer pulso y envia lo que demoró en viajar el sonido de ida y de vuelta hasta el sensor
    duration = pulseIn(pingPin, HIGH); // esta funcion define el tiempo en que demoro el sonido en hacer el recorrido
 
  /* 
  convierte el tiempo a distancia con la funcion microsecondsToInches y microsecondsToCentimeters
  */
     inches = microsecondsToInches(duration);   //aqui se define inches como la distancia del objeto al sensor en pulgadas
     cm = microsecondsToCentimeters(duration);   //aqui se define cm como la distancia del objeto al sensor en centimetros
// Fin Obtiene distancia//


// Fade (o fading) Led
 
  if (cm<336)   // solo si la distancia es menor  336 centimetro del objeto al censor correrá esta parte del programa
                // esto sirve para que el led solo encienda si el sensor capta algo en su rango de operacion

 {    
  
  cm2 = cm - 336  ;   // con esta forma de definir cm2 el brillo de led decae en la medida que un objeto se acerca al sensor (dentro del rango)
  
  fadeValue2 = map(cm2 , 3, 336, 0, 255);   //  valor a definir = map(valor que recibo, de Mínimo, de Máximo, a Mínimo, a Máximo)
  
  analogWrite(ledPin, fadeValue2);   // Escribe el valor de fadeValue2 en el pin del led, para asi variar su intensidad
 }
 
 else   //para cualquier otro caso diferente de cm<336 comienza a correr esta parte del codigo 
 {
  analogWrite(ledPin, 0);   //ya que no hay objeto en el rango del sensor se apaga el led
 }
// Fin programa principal

 

// Muestra los valores a traves del monitor serie
    Serial.print(inches);
    Serial.print("in, ");   //Muestra la distancia del objeto al sensor en pulgadas por el monitor
    Serial.print(cm);
    Serial.print("cm");   //Muestra la distancia del objeto al sensor en centimetros por el monitor
    Serial.println();
    Serial.print("Centi 2  :");
    Serial.print(  fadeValue2 );   //muestra el valor de salida del pin conectado al led
 
   Serial.println();



  delay(50);   // Este delay condiciona cada cuento corre el programa, debe ser pequeño para un sense mas rapido en la distacia del objeto al sensor
 }
//Fin de loop

 

// Funciones
long microsecondsToInches(long microseconds)
 {
   /*
   Según la hoja de datos de Parallax para el PING))), 
   hay 73,746 microsegundos por pulgada o 29,034 microsegundos por centimetro 
   (es decir, el sonido viaja a 1130 pies (o 34442.4cm) por segundo). 
   Este da la distancia recorrida por el ping, ida y vuelta, 
   por lo que dividimos por 2 para obtener la distancia del obstáculo.
   ver: 
   https://www.parallax.com/sites/default/files/downloads/28015-PING-Sensor-Product-Guide-v2.0.pdf
        [En el PDF: TO_IN = 73_746' Inches ; TO_CM = 29_034' Centimeters ]
   */
   return microseconds / 74 / 2;   //el tiempo es dividio en dos ya que es el tiempo en que el sonido recorrio la distancia de ida y vuelta desde el sensor hacia el objeto
 }
 
long microsecondsToCentimeters(long microseconds)
 {
  /*
  La velocidad del sonido es de 340 m / s o 29 microsegundos por centímetro.
  El ping viaja hacia afuera y hacia atrás, por lo que para encontrar 
  la distancia del objeto tomamos la mitad de la distancia recorrida.
  */
   return microseconds / 29 / 2;   //el tiempo es dividio en dos ya que es el tiempo en que el sonido recorrio la distancia de ida y vuelta desde el sensor hacia el objeto
 }

// Fin Funciones

/*
#######################
#   Fin de programa   #
#######################
*/
