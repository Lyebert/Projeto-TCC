/* Trabalho de Conclusão de Cursos
   * Sistema de Informação
   * Wyden Facimp
   * Autor: Flúvio Lyebert
   * https://github.com/malwarebrz
   * https://hackaday.io/malwarebrz
   * contato@fluvio.com.br
  */

#include <Wire.h> //biblioteca necessária para comunicar via i2c
#include <OneWire.h> //biblioteca necessária para o ds18b20 (sensor temperatura)
#include <LiquidCrystal_I2C.h>//biblioteca necessária para o display lcd
#include <DallasTemperature.h> //biblioteca necessária para o ds18b20

#define DS18B20 13 //define o pino do sensor ds18b20

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//configura uma instância onewire para se comunicar com ds18b20
OneWire ourWire(DS18B20);
//passa a temperatura para o dallastemperature
DallasTemperature sensors(&ourWire);
int PinSenA = 8;
int PinSenB = 9;
int Alto = 0;
int Baixo = 0;

void setup() {

    // inicia o sensor ds18b20
    sensors.begin();
    //iniciando o sistema com mensagem do projeto
    lcd.begin(20, 4);
    lcd.setCursor(0, 0);
    lcd.print("====PROJETO TCC=====");
    lcd.setCursor(0, 1);
    lcd.print("===AUTOMACAO DE=====");
    lcd.setCursor(0, 2);
    lcd.print("======SISTEMA=======");
    lcd.setCursor(0, 3);
    lcd.print("=====AQUAPONICO=====");
    //tempo que a mensagem ficará disponivel
    delay(5000);
    //limpar a tela
    lcd.clear();

    //iniciando o sistema com mensagem do projeto
    lcd.begin(20, 4);
    lcd.setCursor(0, 0);
    lcd.print("====================");
    lcd.setCursor(0, 1);
    lcd.print("=====VERIFICANDO====");
    lcd.setCursor(0, 2);
    lcd.print("======SENSORES======");
    lcd.setCursor(0, 3);
    lcd.print("====================");

//requisita a temperatura do sensor
    sensors.requestTemperatures();

//tempo que a mensagem ficará disponivel
    delay(5000);
//limpar a tela
    lcd.clear();
//Configura o pino 10 como saida para o Relé porta IN1, controle do Sensor ALTO
    pinMode(10, OUTPUT);


}

void loop() {
    Alto = digitalRead(PinSenA);
    Baixo = digitalRead(PinSenB);
    sensors.requestTemperatures();


    if (Baixo == 1 && Alto == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("====Tanque Vazio====");
        lcd.setCursor(0, 1);
        lcd.print("=====Abastecendo====");
        lcd.setCursor(0, 2);
        lcd.print("====================");
        lcd.setCursor(0, 3);
        lcd.print("Temperatura:");
        lcd.setCursor(13, 3);
        lcd.print(sensors.getTempCByIndex(0));//imprime no lcd o valor da temperatura 
        lcd.write(223);//imprime no display lcd o símbolo 'º'
        digitalWrite(10, LOW);
        delay(3000);

    }

    if (Baixo == 0 && Alto == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("====Tanque Cheio====");
        lcd.setCursor(0, 1);
        lcd.print("=====Descarga======");
        lcd.setCursor(0, 2);
        lcd.print("====================");
        lcd.setCursor(0, 3);
        lcd.print("Temperatura:");
        lcd.setCursor(13, 3);
        lcd.print(sensors.getTempCByIndex(0));//imprime no lcd o valor da temperatura 
        lcd.write(223);//imprime no display lcd o símbolo 'º'
        digitalWrite(10, HIGH);
        delay(3000);

    }
    delay(500);
}
