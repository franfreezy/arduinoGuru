//importation of all our libraries 
#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// setting up our display
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
// the values above change from one lcd to another and it is therefore prudent to establish
//those that relate to your lcd.

//declaration of variables
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
int i=0;
#define pass_length  5
char passcode[pass_length] ="1234";
char confirmPasscode[pass_length]="" ;
int statusLed = 13;
int accessLed = 11;
int fan =22;
int bedSide = 23;
int tv = 24;
int officeUp = 25;  //officeDown
int lappy = 26;
int doorUp = 27;   // bedUnder
int irchair=28;
int tvState=0;
int lappystate=0;
bool 
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','4','7','*'},
  {'2','5','8','0'},
  {'3','6','9','#'},
  {'A','B','C','D'}
};

//definition of pins
byte rowPins[ROWS] = {53, 52, 51, 50}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {49, 48, 47, 46}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad, this comes with the library
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("hello world");
  lcd.setCursor(1,1);
  lcd.print("initializing ..");
  lcd.clear();
  pinMode(fan,OUTPUT);
  pinMode(accessLed,OUTPUT);
  pinMode(statusLed,OUTPUT);
  pinMode(bedSide,OUTPUT);
  pinMode(tv,OUTPUT);
  pinMode(lappy,OUTPUT);
  pinMode(doorUp,OUTPUT);
  pinMode(officeUp,OUTPUT);
  digitalWrite(statusLed,HIGH);
  Serial.begin(9600);
}



void reset(){
  while (i !=0){
    i =0;
  }
  return;
}
  
void passwordChecker(){
  lcd.setCursor(0,0);
  lcd.print("Enter passcode :");
  char customKey = customKeypad.getKey();
  
  if (customKey){
    lcd.setCursor(i,1);
    lcd.print("*");
    confirmPasscode[i]=customKey;
    i++; }

  if(i == pass_length-1)
    {
        if(!strcmp(passcode,confirmPasscode))
          {
            lcd.clear();
            lcd.print("correct");
            digitalWrite(accessLed,HIGH);
            delay(2000);
            digitalWrite(accessLed,LOW);
            i=0;
            systemUP();
           }
        else{lcd.clear();
        lcd.print("incorrect");
        reset();
       }
    }
}
void systemUP(){
        digitalWrite(lappy,HIGH);
        digitalWrite(tv,HIGH);
        digitalWrite(officeUp,LOW);
}
void ThinkThru(){
  digitalWrite(officeUp,HIGH);
}
void ChairOccupied()
  {
    tvState= digitalRead(tv);
    lappystate= digitalRead(lappy);

    if(irchair==1 && tvstate=0 && lappystate=0)
    {
        passwordChecker();
    }

    if(irchair==0 && tvstate=0 && lappystate=0)
    {
      digitalWrite(officeUp,LOW);
    }

    if(irchair==0 && tvstate=1 && lappystate=1)
    {
      delay(30000);
      int state=digitalRead(irchair);
        if(state=0)
        {
          digitalWrite(tv,LOW);
          digitalWrite(lappy,LOW);
          digitalWrite(officeUp,HIGH);
          passwordChecker();
        }
    }

}
void loop(){

}
   
  