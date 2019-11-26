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

// 'good'
const uint8_t GOOD[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,                     
  SEG_C | SEG_D | SEG_E | SEG_G,
  SEG_C | SEG_D | SEG_E | SEG_G,
  SEG_D | SEG_E | SEG_F | SEG_G | SEG_A               
  };

// 'bad'
const uint8_t BAD[] = {
  0,
  SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,                     
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,     
  SEG_D | SEG_E | SEG_F | SEG_G | SEG_A               
  };

// 'you'
const uint8_t YOU[] = {
  0,
  SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,  
  SEG_C | SEG_D | SEG_E | SEG_G,                   
  SEG_C | SEG_D | SEG_E             
  };

// 'got'
const uint8_t GOT[] = {
  0,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,    
  SEG_C | SEG_D | SEG_E | SEG_G,                   
  SEG_D | SEG_E | SEG_G | SEG_F            
  };

// 'bye'
const uint8_t BYE[] = {
  0,
  SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,    
  SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,                
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G          
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
    pressSwitch3 = digitalRead(switchPin3);
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
    pressSwitch4 = digitalRead(switchPin4);
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
    pressSwitch5 = digitalRead(switchPin5);
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
        display.setSegments(YOU);
        delay(1000);
        display.setSegments(GOT);
        delay(1000);
        if (wins >= 12){
          for (int n=0; n<5; n++){
            display.setSegments(wins);
            delay(1000);
            display.showNumberDec(GOOD);
            delay(1000);
          }
        } else{
          for (int n=0; n<5; n++){
            display.setSegments(wins);
            delay(1000);
            display.showNumberDec(GOOD);
            delay(1000);
          }
        }
        display.setSegments(BYE);
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


  
