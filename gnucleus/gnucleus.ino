
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

char color[7]={'RED','GREEN','YELLOW','BLUE','VIOLET','TEAL','WHITE'};
SoftwareSerial GPRS(7, 8);
unsigned char buffer[64]; // buffer array for data recieve over serial port
int count=0;     // counter for buffer array 
String inputString = "";
String PhoneNumber = "";

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

void lcdPrint(String message)
{
  lcd.clear();
  lcd.setCursor(0 ,0);
  lcd.setBacklight(random(1,7));
  lcd.print(message);
}

void incomingAlert()
{
  // Generate random color and ringtone
  int toneCounter = 15;
  for(int i =0;i<toneCounter;i++)
  {
   scanKeys(BUTTON_SELECT,"ATA");
   // needed a delay without causing button lag
   for(int i=50;i>0;i--)
   {
    scanKeys(BUTTON_SELECT,"ATA"); 
   }
   tone(12,random(100,1000),random(50,200));
  }
   
}

void scanKeys(int button, String gsmCommand)
{ 
 uint8_t buttons = lcd.readButtons ();
 if (buttons && button){
   GPRS.println(gsmCommand);
   noTone(12);
 } 
 }

void gprsReadline()
{
  inputString = "";
  while(GPRS.available()){
    char inChar = (char)GPRS.read();
    inputString += inChar;  
    if (inChar == '\n'){
      break;
    }  
  }
} 



void loop()
{ 
   
  gprsReadline();
  Serial.print(inputString);
  
  //Detect incoming Calls
  if(inputString.startsWith("+CLIP") | inputString.startsWith("+CRING")){
    if(inputString.startsWith("+CLIP")){
      PhoneNumber = inputString.substring(9,19);
    }  
    lcd.setBacklight(color[random(1,7)]);
    lcd.setCursor(0,0);
    lcd.print("Incoming Call");
    lcd.setCursor(0,1);
    lcd.print(PhoneNumber);
    incomingAlert();
  }  
  // End Call detection

  // SMS Detection
  if(inputString.startsWith("+CMTI: \"SM\"")){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("New SMS");
    incomingAlert();
    delay(2000);  
  }

  //End SMS Detection 

    lcd.clear();

}

 
void clearBufferArray()              // function to clear buffer array
{
  for (int i=0; i<count;i++)
    { buffer[i]=NULL;}                  // clear all index of array with command NULL
}
