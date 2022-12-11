/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA2 encryption. For insecure
 WEP or WPA, change the Wifi.begin() call and use Wifi.setMinSecurity() accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>
#include <Servo.h>
const char* ssid     = "yourssid";
const char* password = "yourpasswd";

WiFiServer server(80); //Puerto 80 usado en el navegador web

void setup()
{
    Serial.begin(115200);//Velocidad de configuración del puerto serial
    servoMotor1.attach(5);//Pin número 5 del esp32 para conectar la señal de control del servo
    pinMode(2, OUTPUT);
    delay(10);

     // Comenzamos conectándonos a una red WiFi
    Serial.print("Conectando a ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Conectado a red Wifi.");
    Serial.println("Dirección IP ");
    Serial.println(WiFi.localIP());  
    server.begin();
    digitalWrite(2, HIGH);//Enciende un led cuando el módulo esp32 se conecta a la re wifi
}
int buzi = 33;
int sinal;
int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients
    sinal = pinMode(19);
  if(sinal == LOW){
     pinMode(buzi, OUTPUT);
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/ABRIR\">Abrir</a> Para Abrir la puerta.<br>");
            client.print("Click <a href=\"/CERRAR\">Cerrar</a> Para Cerrar la puerta.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /ABRIR")) {
         servoMotor1.write(110);              // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /CERRAR")) {
          servoMotor1.write(180);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}
