#include <avr/io.h>
#include <avr/interrupt.h>
#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

int LedPin = 13;
volatile int contadorSegundos = 0;
volatile int contadorSegundosTemperatura = 0; // Se tomará cada 30 segundos o sea 30 veces este evento
volatile int contadorRevoluciones = 0;
volatile float velocidadViento = 0.0;
volatile int direccionViento = 0;
volatile int contadorLluvia = 0;
volatile float mmLluvia = 0.0;
volatile float radiacionSolar = 0.0;
volatile float indiceUV = 0.0;
float temp = 0.0;
float humedad = 0.0;
String resultado = "";
const int tiempoMuestreo = 300; // tiempo en segundos 300 para 5 mins, 60 para 1 minuto
const int tiempoMuestreoTempetatura = 30;

void setup() {
 // analogReference(EXTERNAL);
  Serial.begin(9600);
  dht.begin();
  pinMode(LedPin,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(7,INPUT);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  
  cli();
  TCCR1A = 0;
  TCCR1B = 0;

// configuracion del Timer1 para contar 1 segundos
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TCCR1B |= (0 << CS11);
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
  sei();

// configuracion de las Interrupciones 0 y 1,
//para leer pulsos de velocidad de viento
  EIMSK |= (1<<INT0);
  EIMSK |= (1<<INT1);
  EICRA |= (0<<ISC00);
  EICRA |= (1<<ISC01);
  EICRA |= (0<<ISC10);
  EICRA |= (1<<ISC11);


}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2500);
  humedad = dht.readHumidity();
  temp = dht.readTemperature();
}

ISR(TIMER1_COMPA_vect){
  contadorSegundos++;
  contadorSegundosTemperatura++;
  // para cada 5 minutos tiempoMuestreo = 300, para 1 minuto tiempoMuestreo = 60
  if (contadorSegundos >= tiempoMuestreo){  
    contadorSegundos = 0;
    digitalWrite(LedPin,!digitalRead(LedPin));
    calculaDireccionViento();
    calculaLluvia();
    calculaRadiacion();
    calculaUV();
    // V=P(3.621015/T) km/hr P = pulsos; T=tiempo en seg
    resultado = "{\"dirViento\":" + String(direccionViento) 
              + ",\"velViento\":" + String(contadorRevoluciones*(3.621015)/tiempoMuestreo) 
              + ",\"precipitacion\":" + String(mmLluvia) 
              + ",\"radGlobal\":" + String(radiacionSolar)
              + ",\"indiceUV\":" + String(indiceUV)
              + ",\"temperatura\":" + String(temp)
              + ",\"humedad\":" + String(humedad)
              + "}";
    Serial.println(resultado);          
    contadorRevoluciones = 0;
    mmLluvia = 0;
  }
}

ISR(INT0_vect){
  contadorRevoluciones++;
}

ISR(INT1_vect){
  contadorLluvia++;
}

//calcular la dirección del viento en grados de 0 a 360; 180 = sur; 
void calculaDireccionViento(){
  direccionViento = map(analogRead(A0),0,1023,0,360);
}

//procedimiento para calcular la precipitación
void calculaLluvia(){
  mmLluvia = contadorLluvia * 0.2;
  contadorLluvia = 0;
}

void calculaUV(){
  //indiceUV = analogRead(A2)*(5.0*0.1)/(1024*0.0150);
  indiceUV = analogRead(A2)*(0.032552083);
  //indiceUV = analogRead(A2)*(3.3)/(1023*0.150);
}

//calcula la Radiación Solar
void calculaRadiacion(){
  //radiacionSolar = analogRead(A1)*(5.0)/(1024*0.00167);
  radiacionSolar = analogRead(A1)*(2.923828125)
  //radiacionSolar = analogRead(A1)*(3.3)/(1023*0.00167);
}

 
