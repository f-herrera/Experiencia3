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
 const int pingPin = 7;
 const int ledPin = 9;
// VARIABLES GLOBALES NO INICIALIZADAS
 int  fadeValue, fadeValue2 ;
 
void setup()

  {
      // se inicializa comunicacion serial:
         Serial.begin(9600);
   }
 
void loop()
 {

// Obtiene distancia 
  /*
   establece variables para duracion del ping 
   y el resultado de la distancia en centimetros
  */
   long duration, inches, cm, cm2;
 
   /*
   El triggered PING))) es un pulso HIGH de 2 microsegundos.
   un pulso LOW posteriormente para asegurarse que limpia el pulso HIGH
   */
     pinMode(pingPin, OUTPUT);
     digitalWrite(pingPin, LOW);
     delayMicroseconds(2);
     digitalWrite(pingPin, HIGH);
     delayMicroseconds(5);
     digitalWrite(pingPin, LOW);
 
  /*
   El mismo pin es usado para leer la señal de PING))) del pulso HIGH
   pulso cuya duración es el tiempo (en microsegundos) desde el envío 
   del ping hasta la recepción de su eco desde un objeto.
  */
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);
 
  /* 
  convierte el tiempo a distancia con la funcion microsecondsToInches y microsecondsToCentimeters
  */
     inches = microsecondsToInches(duration);
     cm = microsecondsToCentimeters(duration);
// Fin Obtiene distancia//


// Fade (o fading) Led
 // Si la distancia es menor a 336 cm
  if (cm<336)  

 {    
  // Brillo de led decae en la medida que se acerca hasta 3 cm
  cm2 = cm - 336  ;  
  //  valor entregado = map(valor que recibo, de Mínimo, de Máximo, a Mínimo, a Máximo)
  fadeValue2 = map(cm2 , 3, 336, 0, 255);
  // Escribe fadeValue2 al pin 9 
  analogWrite(ledPin, fadeValue2);  
 }
 //para cualquier otro caso diferente de cm<336 apaga el pin 
 else
 {
  analogWrite(ledPin, 0);   
 }
// Fin de Fade (o fading) Led

 


// Depurado (o debug/debugging)
// Muestra los valores a traves del monitor serie
    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    Serial.print("Centi 2  :");
    Serial.print(  fadeValue2 );
 
   Serial.println();
// Fin Depurado (o debug/debugging)

// Delay hace gradual el fade (desvanecimiento del led)
  delay(50);
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
   return microseconds / 74 / 2;
 }
 
long microsecondsToCentimeters(long microseconds)
 {
  /*
  La velocidad del sonido es de 340 m / s o 29 microsegundos por centímetro.
  El ping viaja hacia afuera y hacia atrás, por lo que para encontrar 
  la distancia del objeto tomamos la mitad de la distancia recorrida.
  */
   return microseconds / 29 / 2;
 }

// Fin Funciones

/*
#######################
#   Fin de programa   #
#######################
*/
