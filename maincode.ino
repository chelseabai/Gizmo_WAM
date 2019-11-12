#include <Servo.h>
#include <Arduino.h>
#include <TM1637Display.h>


// define the time duration here
int count = 120; 
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };

// before the game '----'
const uint8_t NONE[] = {
  SEG_G,           
  SEG_G,   
  SEG_G,               
  SEG_G
  };

// start the game 'go'
const uint8_t START[] = {
  0,           
  0,   
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,                     
  SEG_C | SEG_D | SEG_E | SEG_G             
  };

// end the game 'done'
const uint8_t END[] = {
  0,           
  SEG_A | SEG_E | SEG_D | SEG_F | SEG_G,   
  SEG_C | SEG_E | SEG_G,                    
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G         
  };

// best score 'best'
const uint8_t BEST[] = {
  SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, 
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
  SEG_D | SEG_E | SEG_F | SEG_G               
  };

// define connection pins for timer here
#define CLK A0
#define DIO A1

TM1637Display display(CLK, DIO);

Servo Motor1;
Servo Motor2;
Servo Motor3;
Servo Motor4;
Servo Motor5;

//change the motor pin here
int MotorPin1 = 8;
int MotorPin2 = 9;
int MotorPin3 = 10;
int MotorPin4 = 11;
int MotorPin5 = 12;

//change the angle here
int angleUP = 90;
int angleInitial = 0;

//change the delay time for mole to stay here
int easyUp = 3000;

//change the delay time between moles here
int easyDown = 5000;

//time
unsigned long previousMillisTime = 0;
unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
unsigned long previousMillis5 = 0;

//change the sensor pin here
int mainswitchPin = 7;
int switchPin1 = 2;
int switchPin2 = 3;
int switchPin3 = 4;
int switchPin4 = 5;
int switchPin5 = 6;

int soundPin = 13;


//initialise sensor readings
int mainpress = 0;
int pressSwitch1 = 0;
int pressSwitch2 = 0;
int pressSwitch3 = 0;
int pressSwitch4 = 0;
int pressSwitch5 = 0;


//set the sensor threshold here
int threshold = 100;

int randMotor;
int wins = 0;
int highScore = 0;

//define function for each motors movement

int motorControl1 (int interval) {
  Motor1.write(angleUP);
  while (true) {
    int dif2 = millis() - previousMillis1;
    pressSwitch1 = digitalRead(switchPin1);
    Serial.println("Motor 1: UP");
    Serial.println(dif2);
    countDown(); 

    
    if(pressSwitch1){
      digitalWrite(soundPin,HIGH);
      Serial.println("Motor 1: HIT");
      Motor1.write(angleInitial);
      Serial.println("Motor 1: DOWN");
      wins++;
      return wins;
      break;
    }

    if (dif2 > interval){
      Serial.println("Motor 1: BREAK");
      Motor1.write(angleInitial);
      Serial.println("Motor 1: DOWN");
      return wins;
      break;
    }
  } 
}

int motorControl2 (int interval) {
  Motor2.write(angleUP);
  while (true) {
    int dif2 = millis() - previousMillis2;
    pressSwitch2 = digitalRead(switchPin2);
    Serial.println("Motor 2: UP");
    Serial.println(dif2);
    countDown(); 

        
    if(pressSwitch2){
      digitalWrite(soundPin,HIGH);
      Serial.println("Motor 2: HIT");
      Motor2.write(angleInitial);
      Serial.println("Motor 2: DOWN");
      wins++;
      return wins;
      break;
    }

    if (dif2 > interval){
      Serial.println("Motor 2: BREAK");
      Motor2.write(angleInitial);
      Serial.println("Motor 2: DOWN");
      return wins;
      break;
    }
  }
}

int motorControl3 (int interval) {
  Motor3.write(angleUP);
  while (true) {
    int dif2 = millis() - previousMillis3;
    Serial.println("Motor 3: UP");
    Serial.println(dif2);
    countDown(); 

    if(pressSwitch3){
      digitalWrite(soundPin,HIGH);
      Serial.println("Motor 3: HIT");
      Motor3.write(angleInitial);
      Serial.println("Motor 3: DOWN");
      wins++;
      return wins;
      break;
    }
    
    if (dif2 > interval){
      Serial.println("Motor 3: BREAK");
      Motor3.write(angleInitial);
      Serial.println("Motor 3: DOWN");
      return wins;
      break;
    }
  }
}

int motorControl4 (int interval) {
  Motor4.write(angleUP);
  while (true) {
    int dif2 = millis() - previousMillis4;
    Serial.println("Motor 4: UP");
    Serial.println(dif2);
    countDown(); 
    
    if(pressSwitch4){
      digitalWrite(soundPin,HIGH);
      Serial.println("Motor 4: HIT");
      Motor4.write(angleInitial);
      Serial.println("Motor 4: DOWN");
      wins++;
      return wins;
      break;
    }
    
    if (dif2 > interval){
      Serial.println("Motor 4: BREAK");
      Motor4.write(angleInitial);
      Serial.println("Motor 4: DOWN");
      return wins;
      break;
    }
  }
}

int motorControl5 (int interval) {
  Motor5.write(angleUP);
  while (true) {
    int dif2 = millis() - previousMillis5;
    Serial.println("Motor 5: UP");
    Serial.println(dif2);
    countDown(); 

    if(pressSwitch5){
      digitalWrite(soundPin,HIGH);
      Serial.println("Motor 5: HIT");
      Motor5.write(angleInitial);
      Serial.println("Motor 5: DOWN");
      wins++;
      return wins;
      break;
    }
    
    if (dif2 > interval){
      Serial.println("Motor 5: BREAK");
      Motor5.write(angleInitial);
      Serial.println("Motor 5: DOWN");
      return wins;
      break;
    }
  }
}

int countDown(){
  data[3] = display.encodeDigit((9-(millis()-6000)/1000 % 10));
  data[2] = display.encodeDigit((11-(millis()-6000)/10000 % 10)%10);
  data[1] = display.encodeDigit((120000-millis()+6000)/100000 % 10);
  data[0] = display.encodeDigit(0);
  display.setSegments(data);
}

//main code

void setup() {

  //attach the motor to the pins
  Motor1.attach(MotorPin1);
  Motor2.attach(MotorPin2);
  Motor3.attach(MotorPin3);
  Motor4.attach(MotorPin4);
  Motor5.attach(MotorPin5);

  //initialise the motor to 0 degree
  Motor1.write(angleInitial);
  Motor2.write(angleInitial);
  Motor3.write(angleInitial);
  Motor4.write(angleInitial);
  Motor5.write(angleInitial);

 
  pinMode(switchPin1,INPUT);
  pinMode(switchPin2,INPUT);
  pinMode(switchPin3,INPUT);
  pinMode(switchPin4,INPUT);
  pinMode(switchPin5,INPUT);
  pinMode(mainswitchPin,INPUT);

  digitalWrite(soundPin,LOW);
  pinMode(soundPin,OUTPUT);

  Serial.begin(9600);
  
}

void loop() {
  display.clear();
  display.setBrightness(0x0f);
  display.setSegments(NONE);
  mainpress = digitalRead(mainswitchPin);
  if (mainpress){
    display.setSegments(START);
    Serial.println("Start!");
    delay(6000);
    previousMillis = millis();
    previousMillis1 = millis();
    previousMillis2 = millis();
    previousMillis3 = millis();
    previousMillis4 = millis();
    previousMillis5 = millis();
    previousMillisTime = millis();
    while(true){
      int dif = millis() - previousMillis;
      Serial.print(dif);
      Serial.print(",");
      Serial.print(previousMillis);
      previousMillis1 = millis();
      previousMillis2 = millis();
      previousMillis3 = millis();
      previousMillis4 = millis();
      previousMillis5 = millis();
      Serial.println("."); 
      countDown();       
     
      //total game time
      if (millis()  > 126000) {
        Serial.println("END");
        Serial.print("Score: ");
        Serial.println(wins);
        display.setSegments(END);
        delay(3000);
        if (wins > highScore){
          highScore = wins;
          Serial.println("Highest Score!");
          for (int n=0; n<3; n++){
            display.setSegments(BEST);
            delay(1000);
            display.showNumberDec(wins);
            delay(1000);
          }
        } else{
          for (int n=0; n<3; n++){
            display.setSegments(NONE);
            delay(1000);
            display.showNumberDec(wins);
            delay(1000);
          }
        }
        exit(0);
      }
      
      if (dif >= easyDown) {
        randMotor = random(5);
        if (randMotor == 0) {
          Serial.print("Choose Motor 1");
          motorControl1(easyUp);
          delay(200);
          digitalWrite(soundPin,LOW);  
          Serial.println("low");
          previousMillis = millis();
          Serial.println(previousMillis);
        }
        if (randMotor == 1) {
          Serial.println("Choose Motor 2");
          motorControl2(easyUp);
          delay(200);
          digitalWrite(soundPin,LOW);  
          Serial.println("low");
          previousMillis = millis();
          Serial.println(previousMillis);
        }
        if (randMotor == 2) {
          Serial.println("Choose Motor 3");
          motorControl3(easyUp);
          delay(200);
          digitalWrite(soundPin,LOW);  
          Serial.println("low");
          previousMillis = millis();
          Serial.println(previousMillis);
        }  
        if (randMotor == 3) {
          Serial.println("Choose Motor 4");
          motorControl4(easyUp);
          delay(200);
          digitalWrite(soundPin,LOW);  
          Serial.println("low");
          previousMillis = millis();
          Serial.println(previousMillis);
        }  
        if (randMotor == 4) {
          Serial.println("Choose Motor 5");
          motorControl5(easyUp);
          delay(200);
          digitalWrite(soundPin,LOW);  
          Serial.println("low");
          previousMillis = millis();
          Serial.println(previousMillis);
        }
      easyDown = easyDown - 100;
      easyUp = easyUp - 100;
      }
    }    
  }

}


  





//-----------------------------------------------------------------------------------------
////Original version
//
//int motorControl3 (int interval) {
//  
//  Motor3.write(angleUP);
//  Serial.println("Motor 3: UP");
//  delay(2000);
//  Serial.println("Motor 3: delayed");
//  
//  while (true) {
//    int dif2 = millis() - previousMillis2;
//    
//    while (dif2 <= interval){
//      int sensorReading = analogRead(Sensor3);
//      Serial.println("Motor 3: WAIT");
//      Serial.println(dif2);
//    
//      if (sensorReading >= threshold) {
//        Motor1.write(angleInitial);
//        wins++;
//        break;
//      }
//    }
//    
//    if (dif2 > interval) {
//      previousMillis2 = millis();
//      break;
//    }
//  }
//  
//  Motor3.write(angleInitial);
//  delay(2000);
//  Serial.println("Motor 3: DOWN");
//  return wins;
//}





//
//----------------------------------------------------------------------------------------
//// Whack a LED
//
//// Joystick variables
//int sX = A0;     //joystick x axis, analog input
//int sY = A1;     //joystick y axis, analog input
//int sSX;         //state of x, reading from sX
//int sSY;         //state of y, reading from sY
//int sS;          //converted state (may not be most efficient)
//
//// Game variables
//int rNum;        //random int choosing the random light to turn on
//int wins=0;      //counting consecutive wins
//int highScore=0; //saving the highest score of consecutive wins
//
//// Difficulty constants, time to react
//const int easy=1000;
//const int medium=500;
//const int hard=325;
//const int stupid=250;
//
//
//int ledPins[]={5,2,4,3,6,7,8}; //initializing led's
//int pinCount=7;                //number of led pins
//
//void setup() {
//
//Serial.begin(9600);
//pinMode(sX, INPUT);
//pinMode(sY, INPUT);
//
//for (int thisPin = 0; thisPin < pinCount; thisPin++) { //assigning all the pins as outputs in a for loop
//    pinMode(ledPins[thisPin], OUTPUT);
//  }
//}
//
//void loop() {
//
//  rNum=random(4); //generating random choice
//  delay(1000);
//  digitalWrite(ledPins[rNum], HIGH); //lighting the randomly chosen bulb
//  delay(stupid); //difficulty
//
//  //stick stuff
//  sSX = analogRead(sX); //reading x axis input
//  delay(100);
//  sSY = analogRead(sY); //reading y axis input
//
//  //converting y and x inputs to 4 possibilities. 0 and 1023 are the maximum values on each axis of the joystick, as measured.
//  sS=0;
//  switch (sSX) {
//  case 0:
//  sS=1;      // Left
//  break;
//  case 1023:
//  sS=2;      // Right
//  break;
//}
//switch (sSY) {
//  case 0:
//  sS=3;      // Up
//  break;
//  case 1023:
//  sS=4;      // Down
//  break;
//}
//
//  digitalWrite(ledPins[rNum], LOW); //turning off the randomly selected bulb, after the joystick choice was made
//  if (sS-1==rNum) //checking if the user input the correct direction of the lit bulb
//  {
//    wins++;
//    for (int k=0; k<=3; k++) {     //blinking green light indicating correct choice
//    digitalWrite(ledPins[4], HIGH);
//    delay(50);
//    digitalWrite(ledPins[4], LOW);
//    delay(50);
//    }
//  }
//  else
//  {
//    if (wins>highScore) { //if the consecutive wins are more than the previous highscore, the new highscore is set.
//        highScore=wins;
//        wins=0;
//    }
//    for (int i=0; i<=3; i++) {       //blinking red light indicating incorrect choice
//      digitalWrite(ledPins[5], HIGH);
//      delay(50);
//      digitalWrite(ledPins[5], LOW);
//      delay(50);
//    }
//    for (int w=0; w<highScore; w++) { //displaying via counting and blinking the high score on a yellow bulb.
//        digitalWrite(ledPins[6], HIGH);
//        delay(200);
//        digitalWrite(ledPins[6], LOW);
//        delay(200);
//    }
//  }
//  }
//
//  ---------------------------------------------------------------
//
//  #include <Stepper.h>
//
////motor
//const int stepsPerRev = 100; //depends on motor
//Stepper aStepper(stepsPerRev, 8, 9, 10, 11); // pins depends on circuit
//Stepper bStepper(stepsPerRev, 8, 9, 10, 11);
//Stepper cStepper(stepsPerRev, 8, 9, 10, 11);
//
////delay but not
//unsigned long previousMillis = 0;
//const long interval = 1000; //how long it stays up
//
////sensor
//int fsr_val;
//int fsr_pin = 0; //depends on circuit
//bool unhit = true;
//int threshold = 300; //depends on sensor but minimum reading
//
////LED
//int LEDpin = 11; //depends on circuit
//
//void setup() {
//  Serial.begin(9600);
//  pinMode(LEDpin,OUTPUT);
//}
//
//void loop() {
//
//  fsr_val = analogRead(fsr_pin);
//  unsigned long currentMillis = millis();
//
//  // randomly pop up loop
//  // had to change to while loop because break was not verified
//  while (unhit){
//    aStepper.setSpeed(50); //set constant in rpm
//
//    aStepper.step(25); //quarter movement up
//
//    //during the time target is up
//    if (currentMillis - previousMillis >= interval) {
//      // save the last time motor moved
//      previousMillis = currentMillis;
//
//      if (fsr_val > threshold){
//        unhit = false;
//        break;
//      } else {
//        unhit = true;
//      }
//    }
//
//    aStepper.step(-25); //down
//
//    long x = random(1000,7000);
//    delay(x); //how long it stays down
//    }
//
//  //hit condition
//  if (unhit == false){
//    aStepper.step(-25); //target down
//
//    digitalWrite(LEDpin,HIGH); //LED blinks
//    delay(1000);
//    digitalWrite(LEDpin,LOW);
//
//    unhit = true; //reset to allow loop to continue
//  }
//
//}
