//Librerias para el uso del proyecto
#include <WiFi.h>

#include <Servo.h>
Servo servoMotor1; 
const char* ssid     = "xxxx";
const char* password = "xxxx";
WiFiServer server(80);//Puerto 80 usado en el navegador web

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
int  = 33;
int sinal;
int value = 0;
void loop(){
   
 WiFiClient client = server.available();   // Escuchando a los clientes entrantes
  sinal = pinMode(19);
  if(sinal == LOW){
     pinMode(buzi, OUTPUT);

  }
  if (client) {                             // Si hay un cliente,
    Serial.println("Nuevo cliente");        // Imprime un mensaje en el puerto serie
    String currentLine = "";                // String para contener datos entrantes del cliente
    while (client.connected()) {            // Bucle mientras el cliente está conectado
      if (client.available()) {             // Si hay bytes para leer del cliente,
        char c = client.read();             // Lee un caracter
        Serial.write(c);                    // Lo imprimimos en el monitor serial
        if (c == '\n') {                    // Si el byte es un carácter de nueva línea        
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Contenido HTML si lo vemos en el navegador
//-------------------------------------------------------------------------------------------
            client.print("Click <a href=\"/ABRIR\">Abrir</a> Para Abrir la puerta.<br>");
            client.print("Click <a href=\"/CERRAR\">Cerrar</a> Para Cerrar la puerta.<br>");
//-------------------------------------------------------------------------------------------
             client.println();
            // Salir del ciclo while:
            break;
          } else {    // si tienes una nueva línea, borra currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
        //-----------------------
        if (currentLine.endsWith("GET /ABRIR")) {//Posición del servo para abrir la puerta
          servoMotor1.write(110);            
        }
        if (currentLine.endsWith("GET /CERRAR")) {//Posición del servo para abrir la puerta
          servoMotor1.write(180);           
        }
        //-----------------------
      }
    }
    // Cierra la conexión
    client.stop();
    Serial.println("Cliente desconectado");
  }
}