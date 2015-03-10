// Arduino File for the Gnuclear Hardware backend 
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

SoftwareSerial GPRS(7, 8);
unsigned char buffer[64]; // buffer array for data recieve over serial port
int count=0;     // counter for buffer array 


void setup()
{
  
//pinMode(9,OUTPUT);
//digitalWrite(9,HIGH); // Power on/off modem
//delay(800);
//digitalWrite(9,LOW);
  
  GPRS.begin(19200);               // the GPRS baud rate 
  delay(1000); 
  Serial.begin(19200);             // the Serial port of Arduino baud rate.
  GPRS.println("AT+CFUN=1");
  lcd.begin(16, 2);
  lcd.setBacklight(VIOLET);
  
  
}

void lcdPrint(uint8_t color, String message)
{
  lcd.clear();
  lcd.setCursor(0 ,0);
  lcd.setBacklight(color);
  lcd.print(message);
}

void incomingAlert(String message)
{
  
  
   lcdPrint(RED,message);
   scanKeys(BUTTON_SELECT,"ATA");
   tone(12,2600,200);
   delay(100);
   lcdPrint(GREEN,message);
   scanKeys(BUTTON_SELECT,"ATA");
   tone(12,260,200);
   delay(100);
   lcdPrint(TEAL,message);
   scanKeys(BUTTON_SELECT,"ATA");
   delay(100);
   lcdPrint(YELLOW,message);
   scanKeys(BUTTON_SELECT,"ATA");
   tone(12,2600,200);
   delay(100);
   lcdPrint(BLUE,message);
   scanKeys(BUTTON_SELECT,"ATA");
   tone(12,260,200);
   delay(100);
   lcdPrint(VIOLET,message);
   scanKeys(BUTTON_SELECT,"ATA");
   tone(12,2600,200);
   delay(100);
   lcdPrint(BLUE,message);
   scanKeys(BUTTON_SELECT,"ATA");
   tone(12,260,200);
   delay(100);
   
}

void scanKeys(int button, String gsmCommand)
{
 uint8_t buttons = lcd.readButtons ();
 if (buttons && button){
   GPRS.println(gsmCommand);
 } 
 
}

void loop()
{
 

  
  if (GPRS.available())              // if date is comming from softwareserial port ==> data is comming from gprs shield
  { 
    while(GPRS.available())          // reading data into char array 
    {
      buffer[count++]=GPRS.read();     // writing data into array
      
      // Detect incoming calls and SMS
      if(strstr((const char*)buffer,"+CRING:")){
        incomingAlert("Incoming Call");
        clearBufferArray();
        buffer[count++]=GPRS.read();
        lcd.clear();
        lcd.setBacklight(VIOLET);
      }     
      
      if(strstr((const char*)buffer,"+CMTI: \"SM\"")){
        incomingAlert("New SMS");
        delay(1000);
        clearBufferArray();
      }
     if(buffer[count] == '\n') {
      
       break;
     }
     // menu code here
      
  }
    Serial.write(buffer,count);            // if no data transmission ends, write buffer to hardware serial port
    clearBufferArray();              // call clearBufferArray function to clear the storaged data from the array
    count = 0;                       // set counter of while loop to zero
 
 
  }
  if (Serial.available())            // if data is available on hardwareserial port ==> data is comming from PC or notebook
    GPRS.write(Serial.read());       // write it to the GPRS shield
}
void clearBufferArray()              // function to clear buffer array
{
  for (int i=0; i<count;i++)
    { buffer[i]=NULL;}                  // clear all index of array with command NULL
}
