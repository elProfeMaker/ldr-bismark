/*
* Autor: Edgar E. Mamani A.
* Proyecto: LDR con Arduino
* Fecha: 7/02/2019
* Comunidad Open Source Hardware
* Cochabamba - Bolivia
*/

#include <Arduino.h>  //Quitar esta libreria en el arduino IDE
#define pot_umbral A0
#define pot_luz A1
#define ldr A2
#define pir 3
#define led 11


int umbral;
int cambiar_luz;
int nivel_luz;
int presencia;
unsigned long tiempo1;
unsigned long tiempo2;
float tiempo;
bool bandera_presencia = false;

void setup() {
  pinMode(pir, INPUT);
  Serial.begin(9600);
}

void loop() {
  presencia = digitalRead(pir);
  
  if(presencia == 1){
    if(!bandera_presencia){
      tiempo1 = millis();
      bandera_presencia = true;
    }
    umbral = analogRead(pot_umbral);
    umbral = map(umbral, 0, 1024, 0, 100);
    nivel_luz = analogRead(nivel_luz);
    nivel_luz = map(nivel_luz, 0, 1024, 0, 100);
    cambiar_luz = analogRead(pot_luz);
    cambiar_luz = map(cambiar_luz, 0, 1024, 0, 255);

    if(nivel_luz < umbral){
      analogWrite(cambiar_luz, led);
    }
    else{
      analogWrite(0, led);
    }
  }
  else{
    if(bandera_presencia){
      tiempo2 = millis();
      tiempo = tiempo2 - tiempo1;
      tiempo = tiempo/60;

      Serial.println(tiempo);
      bandera_presencia = false;
    }
  }
}