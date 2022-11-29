/*
  Codigo de controle para evitar colisão entre veiculo metro
  viários.
   
*/

// --- Mapeamento de Hardware ---
#define servo1 5 //servo1 ligado no pino digital 5
#define sensor 8 //sensor ligado no pino digital 8
#define tempo  1470



// --- Protótipo das Funções Auxialiares ---
void servo0graus();
void servo90graus();



// --- Configurações Iniciais ---
void setup()
{
   pinMode(servo1, OUTPUT); //saída para o servo1
   pinMode(sensor, INPUT);//entrada para placa 

} //end setup


// --- Loop Infinito ---
void loop()
{
  
  
  for(char i=0;i<100;i++) servo0graus();    //move o servo para a posição 0º por 2 segundos 
  for(char i=0;i<100;i++) servo90graus();    //move o servo para a posição 90º por 2 segundos
    delay(4000);


} //end loop


// --- Desenvolvimento das Funções Auxialiares ---

void servo0graus()              //Posiciona o servo em 0 graus
{
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(00);      //0.4ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<32;i++)delayMicroseconds(800);
 
                               // 20ms = 20000us
                               // 20000us - 600us = 19400us
                               // 19400/600 = ~~32

} //end servo0graus


void servo90graus()             //Posiciona o servo em 90 graus
{
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(tempo);     //1.47ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<12;i++)delayMicroseconds(tempo);
                               // 20ms = 20000us
                               // 20000us - 1500us = 18500us
                               // 18500/1500 = ~~12 

} //end servo0graus