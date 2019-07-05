#define MRAr 3 // first pin of the right motor
#define MRB 5 // second pin of the right motor
#define MLA 6 // first pin of the left motor
#define MLB 9 //second pin of the left motor
//#define MRS 6 // the speed controller pin (enable) of the right motor
//#define MLS 3 // the speed controller pin (enable) of the right motor
#define trig 12 // the trig pin (sends ultra sonic waves ) of the ultrasonic
#define echo 13 // the echo pin (recieve ultra sonic waves ) of the ultrasonic
#define RM1 3
#define RM2 5
#define LM1 6
#define LM2 9
#define maxx 255
#define minn 50
#define myspeed 125
#define speed1 110
#define linespeed 200
#define irl 2 
#define irr 8
char state; // to check what we do in the switch case (recieved from the bluetooth module)
float Mspeed=255; // to control the speed can change it from bluetooth module (float so that no data lost when we devide it
float distance; // to see what is the curent distance from the nearest obstacle
void FW(){
  analogWrite(RM1,maxx);
  analogWrite(LM1,maxx);
  analogWrite(RM2,linespeed);
  analogWrite(LM2,linespeed);
  }
 
void BW(){
  analogWrite(RM2,maxx);
  analogWrite(LM2,maxx);
  analogWrite(RM1,minn);
  analogWrite(LM1,minn);
  }
void RT(){
  analogWrite(RM1,maxx);
  analogWrite(RM2,myspeed);
  analogWrite(LM1,myspeed);
  analogWrite(LM2,maxx);
  }  
void LT(){
  analogWrite(RM2,maxx);
  analogWrite(RM1,myspeed);
  analogWrite(LM2,myspeed);
  analogWrite(LM1,maxx);
  }  
  void FL(){
    analogWrite(RM1,speed1);
    analogWrite(RM2,minn);
     analogWrite(LM2,minn);
   analogWrite(LM1,maxx);
    
  }
   void FR(){
    analogWrite(RM1,maxx);
    analogWrite(RM2,minn);
    analogWrite(LM1,speed1);
    analogWrite(LM2,minn);
    
   }
   void BL(){
    analogWrite(RM2,maxx);
    analogWrite(RM1,speed1);
    analogWrite(LM2,minn);
    analogWrite(LM1,minn);
    
   }
    void BR(){
    analogWrite(RM2,maxx);
    analogWrite(RM1,myspeed);
    analogWrite(LM2,myspeed);
    analogWrite(LM1,maxx);
      
    }
    void mystop (){
      analogWrite(RM2,0);
    analogWrite(RM1,0);
    analogWrite(LM2,0);
    analogWrite(LM1,0);
      
      }
void FWD(){
digitalWrite(MRA,HIGH);
digitalWrite(MRB,LOW);
digitalWrite(MLA,HIGH);
digitalWrite(MLB,LOW);
//analogWrite(MRS,Mspeed);
//analogWrite(MLS,Mspeed); // same speed so that it doesn't turn
}
void BWD(){
digitalWrite(MRA,LOW);
digitalWrite(MRB,HIGH);
digitalWrite(MLA,LOW);
digitalWrite(MLB,HIGH);
//analogWrite(MRS,Mspeed);
//analogWrite(MLS,Mspeed); // same speed so that it doesn't turn (it's the oppsite of BW)
}
void Left(){
digitalWrite(MRA,LOW);
digitalWrite(MRB,HIGH);
digitalWrite(MLA,HIGH);
digitalWrite(MLB,LOW);
//analogWrite(MRS,Mspeed);
//analogWrite(MLS,Mspeed); // same speed so that there is no angle (first part(MR) of FW ,second part of (ML)of BW so it turns left)
}
void Right(){
digitalWrite(MRA,HIGH);
digitalWrite(MRB,LOW);
digitalWrite(MLA,LOW);
digitalWrite(MLB,HIGH);
//analogWrite(MRS,Mspeed);
//analogWrite(MLS,Mspeed); // same speed so that there is no angle (first part(MR) of BW ,second part of (ML)of FW so it turns right)
}
void BWR(){
digitalWrite(MRA,HIGH);
digitalWrite(MRB,LOW);
digitalWrite(MLA,HIGH);
digitalWrite(MLB,LOW);
//analogWrite(MRS,50);
//analogWrite(MLS,Mspeed); // same as BW but (MR) is slower than (ML) so it turns backward & right as well
}
void BWL(){
digitalWrite(MRA,HIGH);
digitalWrite(MRB,LOW);
digitalWrite(MLA,HIGH);
digitalWrite(MLB,LOW);
//analogWrite(MRS,Mspeed);
//analogWrite(MLS,50); // same as BW but (ML) is slower than (MR) so it turnsbackward & left as well
}
void FWR(){
digitalWrite(MRA,HIGH);
digitalWrite(MRB,LOW);
digitalWrite(MLA,HIGH);
digitalWrite(MLB,LOW);
//analogWrite(MRS,Mspeed);
//analogWrite(MLS,50); // same as FW but (MR) is slower than (ML) so it turns forward & right as well
}
void FWL(){
digitalWrite(MRA,LOW);
digitalWrite(MRB,HIGH);
digitalWrite(MLA,LOW);
digitalWrite(MLB,HIGH);
//analogWrite(MRS,50);
//analogWrite(MLS,255); // same as FW but (ML) is slower than (MR) so it turns forward & right as well
}
void STOP(){
digitalWrite(MRA,LOW);
digitalWrite(MRB,LOW);
digitalWrite(MLA,LOW);
digitalWrite(MLB,LOW); // if the to wires of the mator have same voltage it won't move
}
float ultra_sonic(){
    delayMicroseconds(500);
  digitalWrite(trig,LOW);
  delayMicroseconds(500);
digitalWrite(trig,HIGH); // send ultrasonic waves
delayMicroseconds(500); // wait some time for it so it can return
digitalWrite(trig,LOW); // stop sending ultrasonic waves
float duration = pulseIn(echo,HIGH); // calculate time it needed to be recieved (in us)
float distance = (duration * 0.0343)/2.0; // [0.0343 = 343 (sound speed in air )* 100 (to be in cm)/ 10^6 (to be in us)] [2 the time was for it to go then returns so we need half of it] [ float so that no data is lost from the calculations]
return distance;
}
void setup() {
Serial.begin(9600); // begin communication with bluetooth module 9600 bit/sec
pinMode(MRA,OUTPUT); // arduino sends voltage so it's an output
pinMode(MRB,OUTPUT); // arduino sends voltage so it's an output
pinMode(MLA,OUTPUT); // arduino sends voltage so it's an output
pinMode(MLB,OUTPUT); // arduino sends voltage so it's an output
//pinMode(MRS,OUTPUT); // arduino sends voltage so it's an output
//pinMode(MLS,OUTPUT); // arduino sends voltage so it's an output
pinMode(trig,OUTPUT);// arduino sends voltage so it's an output
pinMode(echo,INPUT); // arduino recieves so it's an input
pinMode(irr,INPUT);
pinMode(irl,INPUT);
digitalWrite(trig,LOW); // to ensure that it starts as low
}
void wall(){
distance = ultra_sonic(); // read the distance from the ultrasonic
if(distance< 50) {
Right();}
//else{
//STOP();
//}
}
void linefollwer(){
  while(1){
    int irr1=digitalRead(irr);
int irl1=digitalRead(irl);
  if(irr1==1 && irl1==1 ){
    FW();
    
  }
  
  if(irr1==0 && irl1==1 ){
   
   RT();
   delay(22);
  }
  
  if(irr1==1 && irl1==0 ){
     LT();
     delay(22);
  }
  
  if(irr1==0 && irl1==0 ){
    FW();
   
  }
  distance =  ultra_sonic();

    
  

 if(distance <25){
Right();
delay(200);
while(irr1==1 && irl1==1){
  FW();
  int irr2 = digitalRead(irr);
  if(irr2 == 0){
    Right();
    delay(50);
    break;
  }
  
}
}
  if (Serial.available()){char b =Serial.read();
  if(b!='W') break;}

  
  }}
  void linefollwerr(){
  while(1){
    int irr1=digitalRead(irr);
int irl1=digitalRead(irl);
  if(irr1==1 && irl1==1 ){
    FW();
    
  }
  
  if(irr1==0 && irl1==1 ){
   
   RT();
   delay(22);
  }
  
  if(irr1==1 && irl1==0 ){
     LT();
     delay(22);
  }
  
  if(irr1==0 && irl1==0 ){
    FW();
   
  }
  distance =  ultra_sonic();

    
  

 if(distance <25){
Left();
delay(200);
while(irr1==1 && irl1==1){
  FW();
  int irr2 = digitalRead(irl);
  if(irr2 == 0){
    Left();
    delay(50);
    break;
  }
  
}
}
  if (Serial.available()){char b =Serial.read();
  if(b!='w') break;}

  
  }}
void loop() {
 if (Serial.available()){ // see if communication is available
state= Serial.read(); // read the character sent
switch(state){ // see what is it and choose what to do depending on what is it
case 'F':FWD();break;
case 'B':BWD();break;
case 'L':Left();break;
case 'R':Right();break;
case 'G':FWL();break;
case 'I':FWR();break;
case 'H':BWL();break;
case 'J':BWR();break;
case 'S':STOP();break;
case 'W':linefollwer();break;
case 'w':linefollwerr();break;
// case '' :wall();break;0
default: STOP();}}
else{
wall();
}

}
