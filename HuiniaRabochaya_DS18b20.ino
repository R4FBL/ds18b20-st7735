#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#define ONE_WIRE_BUS 2
//define a object of DS1307 class
// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// https://github.com/milesburton/Arduino-Temperature-Control-Library
//OneWire  ds(10);  // on pin 10 (a 4.7K resistor is necessary)
// TFT lcd(8,9,10,11,12); //Arduino  csk,sda,A0,rst,cs
#define sclk 52
#define mosi 51
#define cs   13
#define rst  11  
#define dc   10
/* На моем дисплее 
 SCK = CLK > D13 = #define sclk 13
 SDA > D11 = #define mosi 11
 A0 = RS > D7 = #define dc   7
 RST > D6 = #define rst  6
 CS > D5= #define cs   5
 GND > GND
 VCC > 5V
*/
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress Thermometer1 = { 
  0x28, 0xFF, 0xAE, 0x28, 0x21, 0x17, 0x04, 0x69 };  // адрес датчика DS18B20
    
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void setup() {  
  //инициализация датчика ds18b20         
  sensors.begin();
  sensors.setResolution(Thermometer1,8);//установка сенсора
  //установка дисплея
  tft.initR(INITR_BLACKTAB);   
  tft.setRotation(tft.getRotation() + 1); // rotate 90degs
  tft.setTextSize(1);    //1-8
  tft.fillScreen(ST7735_BLACK);
  tft.drawLine(0,10,168, 10, ST7735_BLUE);
  tft.drawLine(0,40,168, 40, ST7735_BLUE);
  tft.drawLine(0,70,168, 70, ST7735_BLUE);
  tft.drawLine(0,100,168, 100, ST7735_BLUE);
  //Com-port инициализация
 // Serial.begin(9600);
  //старт времени
  //clock.begin();
  //используется для установки времени
  //для установки раскоментировать
  /*clock.fillByYMD(2018,11,9);//Jan 19,2013
  clock.fillByHMS(13,45,30);//15:28 30"
  clock.fillDayOfWeek(FRI);//Saturday
  clock.setTime();//write time to the RTC chip*/
if (!bmp.begin()) {
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

//  bmp_temp->printSensorDetails();
}

/*void printTime()
{ 
  clock.getTime();  
  tft.setTextSize(2);  
  tft.setCursor(5,65);
  tft.setTextColor(ST7735_YELLOW,ST7735_BLACK);
  tft.print(clock.hour, DEC);
  tft.print(":");
  
  tft.setTextSize(2);  
  tft.setCursor(40,65);
  tft.setTextColor(ST7735_YELLOW,ST7735_BLACK);
  tft.print(clock.minute, DEC);
  tft.print(":");
  
  tft.setTextSize(2);  
  tft.setCursor(75,65);
  tft.setTextColor(ST7735_MAGENTA,ST7735_BLACK);
  tft.print(clock.second);
  
  //Год,месяц,день
  tft.setTextSize(2);  
  tft.setCursor(5,90);
  tft.setTextColor(ST7735_BLUE,ST7735_BLACK);
  tft.print(clock.month, DEC);
  tft.print("/");
  
  tft.setTextSize(2);  
  tft.setCursor(45,90);
  tft.setTextColor(ST7735_BLUE,ST7735_BLACK);
  tft.print(clock.dayOfMonth, DEC);
  tft.print("/");
  
  tft.setTextSize(2);  
  tft.setCursor(75,90);
  tft.setTextColor(ST7735_BLUE,ST7735_BLACK);
  tft.print(clock.year+2000, DEC);  
//неделя
  tft.setTextSize(2);  
  tft.setCursor(105,65);
  tft.setTextColor(ST7735_RED,ST7735_BLACK);
  tft.print(clock.dayOfWeek);
  Serial.print(clock.dayOfWeek);
  switch (clock.dayOfWeek)// Friendly printout the weekday
  {   
    case MON:
      tft.print("MON");
      break;
    case TUE:
      tft.print("TUE");
      break;
    case WED:
      tft.print("WED");
      break;
    case THU:
      tft.print("THU");
      break;
    case FRI:
      tft.print("FRI");
      break;
    case SAT:
      tft.print("SAT");
      break;
    case SUN:
      tft.print("SUN");
      break;
  }
 }
*/


void printTemperature(DeviceAddress deviceAddress) {
  float tempC = sensors.getTempC(deviceAddress);
  //Цельсии
  if(tempC > 24.9){
  tft.setTextSize(3);  
  tft.setCursor(20,15);
  tft.setTextColor(ST7735_BLACK,ST7735_RED);
  tft.print(tempC);
  tft.print("C");
  }
  else
  {
  tft.setTextSize(3);  
  tft.setCursor(20,15);
  tft.setTextColor(ST7735_BLACK,ST7735_CYAN);
  tft.print(tempC);
  tft.print("C"); 
    }
}
void printBmp280(){
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
 if(temp_event.temperature >25.5){
  tft.setTextSize(3);
  tft.setTextColor(ST7735_BLACK,ST7735_RED);  
  tft.setCursor(25,45);
  tft.print(temp_event.temperature);  
  tft.print("C");
}
  else if(temp_event.temperature <= 25.0 ){
  tft.setTextSize(3);
  tft.setTextColor(ST7735_BLACK,ST7735_GREEN);  
  tft.setCursor(25,45);
  tft.print(temp_event.temperature);  
  tft.print("C");
  }
  else if( temp_event.temperature >= 18  ){
  tft.setTextSize(3);
  tft.setTextColor(ST7735_MAGENTA,ST7735_BLACK);  
  tft.setCursor(25,45);
  tft.print(temp_event.temperature);  
  tft.print("C");
  }
  else{
  tft.setTextSize(3);
  tft.setTextColor(ST7735_CYAN,ST7735_BLACK);  
  tft.setCursor(25,45);
  tft.print(temp_event.temperature);  
  tft.print("C");
  }
  
  tft.setTextSize(3);  
  tft.setCursor(25,75);
  tft.setTextColor(ST7735_MAGENTA,ST7735_BLACK);  
  tft.print(pressure_event.pressure/1.333);
}
void loop() {
  sensors.requestTemperatures();
  printTemperature(Thermometer1);
  printBmp280();
  delay(1000);
  //printTime();      
}
