#include <Servo.h>

/*
  Codigo de controle para evitar colisão entre veiculo metro
  viários.
   
*/
// --- Declaração do objeto ---

Servo servo1;


// --- Funções Auxialiares ---
int angulo;
#define sensor 8 
// --- Configurações Iniciais ---
void setup()
{
  servo1.attach(5);
  angulo = 0;
  servo1.write(angulo);

} //end setup


// --- Loop Infinito ---
void loop()
{
  
 if(digitalRead(sensor) == HIGH){
     angulo = 0;
  servo1.write(angulo);
  delay(3000);
  
  angulo = 90;
  servo1.write(angulo);
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
