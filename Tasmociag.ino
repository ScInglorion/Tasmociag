#include <Servo.h>

#define S0 7
#define S1 8
#define S2 9
#define S3 10
#define sensorOut 11
#define LED 12
#define Servo1Pin 6
#define Servo2Pin 5
#define Servo3Pin 3

Servo servo1;
Servo servo2;
Servo servo3;
int pos1 = 180;
int pos2 = 180;
int pos3 = 180;

int colourReading();
void servo_Move_to_position(int);
void servo_Move_from_position(int);

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(LED, OUTPUT);  
  pinMode(sensorOut, INPUT);  
// Setting frequency scaling to 100%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);
  digitalWrite(LED, HIGH);
  Serial.begin(115200);
  servo1.attach(Servo1Pin);
  servo2.attach(Servo2Pin);
  servo3.attach(Servo3Pin);
  servo1.write(180); // Starting position at 180 is caused due to the fact that servos can turn in range (0;180), and due to our negligance it was inproperly screwed and we just did not want to unscrew the whole staff.
  servo2.write(180); 
  servo3.write(180); 
}


void loop() {
  int colour;
  colour = colourReading();
  Serial.println(colour);
  servo_Move_from_position(colour);  
  servo_Move_to_position(colour);
}


// Function responsible for differencing between colours of packages. It has to be stated that range of frequences could be different based on lighting, needed colours and lastly on sensor's scaling. 
int colourReading(){
  int redFrequency = 0;
  int greenFrequency = 0;
  int blueFrequency = 0;
  // seting red photodiodesto be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  // seting green photodiodesto be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  // seting blue photodiodesto be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // choosing the proper colour
  if(blueFrequency > 13 && blueFrequency < 20 && redFrequency > 5 && redFrequency < 9 && greenFrequency > 20 && greenFrequency <30){
    Serial.println("RED");
    Serial.print(" R = ");
    Serial.println(redFrequency);
    Serial.print(" G = ");
    Serial.println(greenFrequency);
     Serial.print(" B = ");
    Serial.println(blueFrequency);
    return 1;
  }
  else if(blueFrequency > 14 && blueFrequency < 24   && redFrequency > 11 && redFrequency < 21 && greenFrequency > 7 && greenFrequency <18){
    Serial.println("Green");
    Serial.print(" R = ");
    Serial.println(redFrequency);
    Serial.print(" G = ");
    Serial.println(greenFrequency);
    Serial.print(" B = ");
    Serial.println(blueFrequency);
    return 2;
  }
  else if(blueFrequency > 8 && blueFrequency < 17 && redFrequency > 30 && redFrequency < 40 && greenFrequency > 24 && greenFrequency <34) {
    Serial.println("Blue");
    Serial.print(" R = ");
    Serial.println(redFrequency);
    Serial.print(" G = ");
    Serial.println(greenFrequency);
    Serial.print(" B = ");
    Serial.println(blueFrequency);
    return 3;
  }
  else{
    Serial.println("Else");
    Serial.print(" R = ");
    Serial.println(redFrequency);
    Serial.print(" G = ");
    Serial.println(greenFrequency);
    Serial.print(" B = ");
    Serial.println(blueFrequency);
    delay(100);
    return 4;    
  }

} 


// Function moving servo position from positon 0 to needed position (in this case position zero means 180 degree)
/*The difference in desired position was caused by differences in amounting servomotors at each support*/
void servo_Move_to_position(int properServo){
if(properServo == 1){
  for (pos1 = 141; pos1 <=180; pos1 ++) {
    servo1.write(pos1);              
    delay(20);                       
  }
  }
  else if(properServo == 2){
  for (pos2 = 136; pos2 <= 185; pos2 ++) {
    servo2.write(pos2);              
    delay(20);                       
  }                           
  }
  else if(properServo == 3){
  for (pos3 = 130; pos3 <= 180; pos3 ++) {
    servo3.write(pos3);              
    delay(20);                       
  }    
  }
  else{

  }
}


// Function returning servo position to positon 0 (in this case position zero means 180 degree)
void servo_Move_from_position(int properServo){
  if(properServo == 1){
    for (int pos1 = 180; pos1 >= 143; pos1 --) {
      servo1.write(pos1);              
      delay(20);                       
    }
    delay(8000);
  }
  else if(properServo == 2){
    for (int pos2 = 180; pos2 >= 136; pos2 --) {
      servo2.write(pos2);              
      delay(20);                       
    }
    delay(6000);                      
  }
  else if(properServo == 3){
    for (int pos3 = 180; pos3 >= 130; pos3 --) {
      servo3.write(pos3);              
      delay(20);                       
    }
    delay(3000);  
  }
  else{
  }
}
