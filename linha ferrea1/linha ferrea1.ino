/*
  Codigo de controle para evitar colisão entre veiculo metro
  viários.
   
*/
// --- Declaração do objeto ---
#include <WiFi.h>
#include <Servo.h>
Servo servo1;
// --- Conectando esp32 ao WIFI ---
const char* ssid     = "xxxx";
const char* password = "xxxx";
WiFiServer server(80);//Porta 80 usada no navegador da web
// --- Funções Auxialiares ---
int angulo;
#define sensor 8
// --- Configurações Iniciais ---
void setup()
{
    Serial.begin(115200);//Velocidade de configuração da porta serial
    servo1.attach(5);//Pino número 5 do esp32 para conectar o sinal de controle do servo
    angulo = 0;
    servo1.write(angulo);    
    pinMode(2, OUTPUT);
    delay(10);
    // Começamos conectando-nos a uma rede WiFi
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
    digitalWrite(2, HIGH);//Acende um led quando o modulo esp32 se conecta a rede wi-fi
   
} //end setup

// --- Loop Infinito ---
void loop()
{
 
 if(digitalRead(sensor) == HIGH){
   Serial.println("Trem em rota de colisão");// mensagem no celular
     angulo = 0;
  servo1.write(angulo); //servo em posição de reposo
  delay(3000);
 
  angulo = 90;
  servo1.write(angulo); //servo em posição de 90°
  delay(5000);
 
  angulo = 0;
  servo1.write(angulo);
  delay(3000);
  }else{
        angulo = 0;
  servo1.write(angulo);
  delay(3000);
    }
 


} //end loop

