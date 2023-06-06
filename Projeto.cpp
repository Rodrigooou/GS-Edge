//Programa: Ligando dois displays LCD I2C no Arduino
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Display LCD 1 no endereco 32, 16 linhas e 2 colunas
LiquidCrystal_I2C display1(32, 16, 2);

//Display LCD 2 no endereco 33, 16 linhas e 2 colunas
LiquidCrystal_I2C display2(33, 16, 2);

// Variaveis a serem adicionadas
int SensorUmidPino = 2;
int ldrvariavel = 0;
int porcem = 0;
int operacao;
int solo = 0;

//Declarando entradas, lcd e sensores
void setup()
{
  //Inicializa os displays
  display1.init();
  display2.init();

  //Liga o backlight (luz de fundo)
  display1.backlight();
  display2.backlight();

  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

//Loop
void loop()
{
  //substituto do sensor de umidade
  int SensorUmidTensao = analogRead(SensorUmidPino);
  float porcem = map(SensorUmidTensao, 0, 1023, 0, 100);

  //manter a temperatura em °C
  int tmp = analogRead(A1);
  float voltage = (tmp * 5.0) / 1024;
  float milliVolt = voltage * 1000;
  float tmpCel = (milliVolt - 500) / 10;

  //valores do luminosidade
  ldrvariavel = analogRead(A0);
  Serial.println(ldrvariavel);

  //Condições para os sensores
  operacao = Serial.parseInt();
  solo = analogRead(A3);

  if (solo < 512)
  { // Umidade do solo
    display1.setCursor(0, 0);
    display1.print("Umid solo BOA    ");
  }
  if (solo > 512)
  { // Umidade do solo
    display1.setCursor(0, 0);
    display1.print("Umid solo RUIM    ");
  }
  if (porcem > 50)
  { // Umidade do ar
    display1.setCursor(0, 1);
    display1.print("Umidade do ar OK    ");
    
  }
  else if (porcem < 50)
  { //Umidade do ar
    display1.setCursor(0, 1);
    display1.print("Umidade Baixa        ");
    
  }

  if (16 > tmpCel && tmpCel > 10)
  { //temperatura
    display2.setCursor(0, 0);
    display2.print("Temp Agradavel");
 
  }
  else if (tmpCel > 16)
  { //temperatura
    display2.setCursor(0, 0);
    display2.print("Temp Quente   ");
 
  }
  else if (tmpCel < 10)
  { //temperatura
    display2.setCursor(0, 0);
    display2.print("Temp Frio    ");

  }

  if (ldrvariavel > 1000)
  { //Luminosidade
    display2.setCursor(0, 1);
    display2.print("Luz Estavel");
    
  }
  else
  {
    if (ldrvariavel > 650)
    { //Luminosidade
      display2.setCursor(0, 1);
      display2.print("Luz Estavel");
  
    }
    else
    {
      if (ldrvariavel > 350)
      { //Luminosidade
        display2.setCursor(0, 1);
        display2.print("Luz Mediana");
 
      }
      else
      {
        if (ldrvariavel > 150)
        { // Luminosidade
          display2.setCursor(0, 1);
          display2.print("Luz Instavel");
 
        }
      }
    }
  }
}