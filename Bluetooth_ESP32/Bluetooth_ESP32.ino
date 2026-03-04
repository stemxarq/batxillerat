/*
Dóna errors al compilar però carrega
S'ha de reiniciar l'ESP32 per què connecte el BT
Funciona rebent dades des del terminal
*/

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void setup()
   {   Serial.begin(115200);
       Serial.println("Si no pots emparellar-lo fes un reset a l'ESP32 (amb EN)");
       SerialBT.begin("ESP32Massa"); //Inicia Bluetooth i li posa l'ID
       Serial.println("El BT està actiu, pots emparellar-lo per Bluetooth!");
   }

void loop()
   {   if (Serial.available()) {        // Si la consola té dades
           int cadena = Serial.read();  // Llegeix caràcters ASCII (int) 10 = '\n'
           SerialBT.write(cadena); // Escriu al BT el contingut de la consola
           Serial.println("<--- " + (String) cadena); //Mostra el que ha rebut al monitor sèrie del PC
          }
       if (SerialBT.available())  // Llegeix el que arriba pel Bluetooth
          {  String S = GetLine(); // Funció que llegeix cadenes ASCII acabades en "\n"
             SerialBT.print(S);
             Serial.println("---> " + S); //Mostra el que ha rebut al monitor sèrie del PC
          }
    }

String GetLine()  // Lee una cadena desde el puerto BT
   {   String S = "" ;
       if (SerialBT.available())
          {    char c = SerialBT.read(); ;
               while ( c != '\n')            //Hasta que el caracter sea intro
                {     S = S + c ;
                      delay(25) ;
                      c = SerialBT.read();
                }
                return( S + '\n') ;
          }
   }