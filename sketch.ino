const int SevenLed_Layout[7]={2,3,4,5,6,7,8};
const int SevenSegment_Layout[4]={9,10,11,12};
const int Potent = A0;
const int Buzzer = 13;
long val;
unsigned long timer=0;
const byte Segment[10][7]{
      {1,1,1,1,1,1,0}, //0
      {0,1,1,0,0,0,0}, //1
      {1,1,0,1,1,0,1}, //2
      {1,1,1,1,0,0,1}, //3
      {0,1,1,0,0,1,1}, //4
      {1,0,1,1,0,1,1}, //5
      {1,0,1,1,1,1,1}, //6
      {1,1,1,0,0,0,0}, //7
      {1,1,1,1,1,1,1}, //8
      {1,1,1,1,0,1,1} //9
};

enum StateMachine{
    STATE_SET_TIME,
    STATE_COUNTDOWN,
    STATE_ALARM
};
StateMachine StartState = STATE_SET_TIME;


long Timer(){
  long valoare;
  valoare = map(analogRead(Potent),0,1023,0,3600);
  return valoare;
}

int Clock[4]={0,0,0,0};

void DisplayRefresh(){
  for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
          digitalWrite(SevenSegment_Layout[j],HIGH);
        }
          
        for(int c=0;c<7;c++){
          digitalWrite(SevenLed_Layout[c],Segment[Clock[i]][c]);
        }
      digitalWrite(SevenSegment_Layout[i],LOW);
      delay(4);
  }
}


void setup() {
  for(int i=0;i<7;i++)
    pinMode(SevenLed_Layout[i],OUTPUT);
  for(int i=0;i<4;i++)
    pinMode(SevenSegment_Layout[i],OUTPUT);
    pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    DisplayRefresh();
    switch(StartState){
      case STATE_SET_TIME:
          val=Timer();
          Clock[1]=(val/60)%10;
          Clock[0]=(val/60)/10;
          Clock[3]=(val%60)%10;
          Clock[2]=(val%60)/10;
           if(millis()-timer>=3000){
          Serial.print(val/60);
          Serial.print(":");
          Serial.println(val%60);
          timer=millis();                
          StartState=STATE_COUNTDOWN;
          }
      break;
      case STATE_COUNTDOWN:
            if(millis()-timer>=1000){
              timer=millis();
              if(val>0)
                val-=1;
            }
            Clock[1]=(val/60)%10;
            Clock[0]=(val/60)/10;
            Clock[3]=(val%60)%10;
            Clock[2]=(val%60)/10;
            if(val<=0){
              timer = millis();
                StartState=STATE_ALARM;
            }
          

      break;
      case STATE_ALARM:
              tone(13,262,250);
              if(millis()-timer>=1000)
                {
                  timer=millis();
                  StartState=STATE_SET_TIME;
                }
             
      break;
    }

}