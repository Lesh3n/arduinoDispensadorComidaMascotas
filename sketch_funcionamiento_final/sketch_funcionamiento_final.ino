//Agregar dependencias
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Servo.h>
Servo myservo;

//Credenciales WIFI
#define WIFI_SSID "OnePlus Nord CE 2 Lite 5G"
#define WIFI_PASSWORD "d9vkftk3"

//Credenciales firebase
#define FIREBASE_HOST "dispensadoralimento-a39ba-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "8nWkALnFzKqdN8IUcYVlmk2NaP56UOJIOvaQCmYr"

//Firebase Data Object
FirebaseData firebaseData;

//*********** VARIABLES *************

// Rutas FB
String nodo = "/alimento";
String child = "/alimentar";

//Variables simples
bool iterar = true;

void moverServo()
{
  myservo.write(0);
  delay(2000);
  myservo.write(90);
  delay(2000);
  myservo.write(0);
}

void setup() 
{
  //Declarar los baudios en los que correra el serial monitor
  Serial.begin(115200);

  //Declarar pin del servo
  myservo.attach(D7);

  //Conexion WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  //Prints para depurar
  Serial.println();
  Serial.println("Conexion Exitosa!");
  Serial.println("La IP Local es: ");
  Serial.println(WiFi.localIP());

  //Conexion firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() 
{
  
  while(iterar){
    Firebase.getInt(firebaseData, nodo + "/alimentar");
    int estado = firebaseData.intData();
    if (estado == 1){
      moverServo();
      Firebase.setInt(firebaseData, nodo + "/alimentar", 0);
    }
  }

}


