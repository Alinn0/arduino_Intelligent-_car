 #include <SoftwareSerial.h> //头文件
 #include "head.h"
 SoftwareSerial myserial (8,9); //定义发送接收引脚
 int five_pin[]={A1,A2,A3,A4,A5};//定义避障数组
 #define IN1 10
 #define IN2 11
 #define IN3 12
 #define IN4 13
 #define ENA 5
 #define ENB 6
 int ch=0;
  int ch1=0;
int destance;
int date;
int i = 0;
int tone_len;
 int mytone[] =
{
    NOTE_D0,NOTE_D0,NOTE_D0,NOTE_D6,NOTE_D7,NOTE_DH1,NOTE_D7,NOTE_DH1,NOTE_DH3,NOTE_D7,NOTE_D7,NOTE_D7,NOTE_D3,NOTE_D3,
    NOTE_D6,NOTE_D5,NOTE_D6,NOTE_DH1,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_D3,NOTE_D4,NOTE_D3,NOTE_D4,NOTE_DH1,
    NOTE_D3,NOTE_D3,NOTE_D0,NOTE_DH1,NOTE_DH1,NOTE_DH1,NOTE_D7,NOTE_D4,NOTE_D4,NOTE_D7,NOTE_D7,NOTE_D7,NOTE_D0,NOTE_D6,NOTE_D7,
    NOTE_DH1,NOTE_D7,NOTE_DH1,NOTE_DH3,NOTE_D7,NOTE_D7,NOTE_D7,NOTE_D3,NOTE_D3,NOTE_D6,NOTE_D5,NOTE_D6,NOTE_DH1,
    NOTE_D5,NOTE_D5,NOTE_D5,NOTE_D2,NOTE_D3,NOTE_D4,NOTE_DH1,NOTE_D7,NOTE_D7,NOTE_DH1,NOTE_DH1,NOTE_DH2,NOTE_DH2,NOTE_DH3,NOTE_DH1,NOTE_DH1,NOTE_DH1,
    NOTE_DH1,NOTE_D7,NOTE_D6,NOTE_D6,NOTE_D7,NOTE_D5,NOTE_D6,NOTE_D6,NOTE_D6,NOTE_DH1,NOTE_DH2,NOTE_DH3,NOTE_DH2,NOTE_DH3,NOTE_DH5,
    NOTE_DH2,NOTE_DH2,NOTE_DH2,NOTE_D5,NOTE_D5,NOTE_DH1,NOTE_D7,NOTE_DH1,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH3,
    NOTE_D6,NOTE_D7,NOTE_DH1,NOTE_D7,NOTE_DH2,NOTE_DH2,NOTE_DH1,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_DH4,NOTE_DH3,NOTE_DH2,NOTE_DH1,
    NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH6,NOTE_DH6,NOTE_DH5,NOTE_DH5,NOTE_DH3,NOTE_DH2,NOTE_DH1,NOTE_DH1,NOTE_D0,NOTE_DH1,
    NOTE_DH2,NOTE_DH1,NOTE_DH2,NOTE_DH2,NOTE_DH5,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH3,NOTE_DH6,NOTE_DH6,NOTE_DH5,NOTE_DH5,
    NOTE_DH3,NOTE_DH2,NOTE_DH1,NOTE_DH1,NOTE_D0,NOTE_DH1,NOTE_DH2,NOTE_DH1,NOTE_DH2,NOTE_DH2,NOTE_D7,NOTE_D6,NOTE_D6,NOTE_D6,NOTE_D6,NOTE_D7
};

double mytime[]=
{
      1,1,1,0.5,0.5, 1+0.5,0.5,1,1, 1,1,1,0.5,0.5,
      1+0.5,0.5,1,1, 1,1,1,1, 1+0.5,0.5,1,1,
      1,1,0.5,0.5,0.5,0.5, 1+0.5,0.5,1,1, 1,1,1,0.5,0.5,
      1+0.5,0.5,1,1, 1,1,1,0.5,0.5, 1+0.5,0.5,1,1,
      1,1,1,0.5,0.5, 1,0.5,0.25,0.25,0.25,0.5, 0.5,0.5,0.5,0.25,0.5,1,
      0.5,0.5,0.5,0.5,1,1, 1,1,1,0.5,0.5, 1+0.5,0.5,1,1,
      1,1,1,0.5,0.5, 1.5,0.5,1,1, 1,1,1,1,
      0.5,0.5,1,1,0.5,0.5, 1.5,0.25,0.5,1, 1,1,1,1,
      1,1,1,1, 1,1,1,1, 0.5,0.5,1,1,0.5,0.5,
      1,0.5,0.5,1,1, 1,1,1,1, 1,1,1,1,
      0.5,0.5,1,1,0.5,0.5, 1,0.5,0.25,0.5,1, 1,1,1,0.5,0.5
};
void speak_play(int pin)     //播放音乐
{
   //tone_len = sizeof(mytone)/sizeof(mytone[0]);
  int i=0;

  for(i=0;i<tone_len;i++)
  {
   if(myserial.available()>0)
   ch=myserial.read();

       tone(pin,mytone[i]);
       delay(400*mytime[i]);
       noTone(pin);
   
   
  }
}
  void car_speed(int left_speed,int right_speed)//小车速度
 {
  analogWrite(ENA,left_speed);
  analogWrite(ENB,right_speed);
 }
 void car_forword()//小车前进
 {    
       car_speed(255,255);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      delay(150);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
 }
  void car_stop()//小车停止
 {    
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
 }
  void car_back()//小车后退
 {
      car_speed(255,255);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      delay(150);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
 }
  void car_left()//小车左转
 {
      car_speed(255,255);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      delay(50);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
 }
  void car_right()//小车右转
 {
      car_speed(255,255);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      delay(50);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
 }


  void led_init(int pin)//设置引脚为高电平
{
   pinMode(pin,OUTPUT);
}

void led_on(int pin)//灯亮
{
  digitalWrite(pin,HIGH);
}

void led_off(int pin)//灯灭

{
  digitalWrite(pin,LOW);
}

void led_flash(int pin) //灯闪
{
  digitalWrite(pin,LOW);
 delay(500);
  digitalWrite(pin,HIGH);
   delay(500);
  digitalWrite(pin,LOW);
   delay(500);
  digitalWrite(pin,HIGH);
   delay(500);
}
void led_breath()//呼吸灯
{
  int i=0;
  for(i=0;i<125;i++)
  {
  analogWrite(2,i);
  }
}


void speak_init(int pin)//数组的个数
{
  pinMode(pin,OUTPUT);
  tone_len = sizeof(mytone)/sizeof(mytone[0]);
}
void speak_on(int pin, int f)//发声
{
  tone(pin,f);
}

void  my_distanc_init(int trig, int echo)//设置距离引脚
{
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void  my_distanc(int trig, int echo)//设置距离
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

 destance = pulseIn(echo,HIGH)*0.017;
 Serial.print(destance);
 Serial.println("cm");
 delay(50);

 } 
 void xunji()
 {
 
    int i=0;
    int level=0;

     for(i=0;i<5;i++)
    {
     level= digitalRead(five_pin[i]);
     
    
     if(level==0)
       {
        ch1 = five_pin[i];
          Serial.println(ch1);
        }
       
         switch(ch1)
          {case 19:
      
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
      delay(1);
     
      
        
          break;
          case 18:
         
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
      delay(1);
      
     
      
          break;
          case 17:
          digitalWrite(IN1,HIGH);
          digitalWrite(IN2,LOW);
          digitalWrite(IN3,HIGH);
          digitalWrite(IN4,LOW); 
          delay(1);
     
          break; 
          case 16:
          
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      delay(1);
 
      
          break;
          case 15:
           
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      delay(1);
 
     
          break;
             
       }
      
    }
  
 }
 



void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  myserial.begin(115200);
  Serial.println("hello");
  led_init(10);
  led_init(11);
  led_init(12);
  led_init(13);
  led_init(5);
  led_init(6);
  
   my_distanc_init(2,3);

  speak_init(7);

  pinMode(A5,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  

 }



void loop() {
  // put your main code here, to run repeatedly:
  
  int ret= myserial.available();
   
  if(ret>0)
  {    
    
    date=myserial.read();
   Serial.println(date);
    switch(date)
    {
      case 10:
        car_forword();      
        break;
      case 11:
        car_back();       
        break;
      case 12:
        car_left();
        break;
      case 13:
        car_right();
        break;      
    }
 }
    if(date==19)
    { 
        my_distanc(2,3);   
         if(destance<20)
         {
          digitalWrite(IN1,HIGH);
          digitalWrite(IN2,LOW);
          digitalWrite(IN3,LOW);
          digitalWrite(IN4,HIGH);
         }
         else if(destance>20&&destance<30)
        {
          car_stop();
        } 
        else if(destance>30)
        {
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        }         
    }
    else if(date == 15)
    {
      if( i == tone_len)
      {
         i=0;
      }
       tone(7,mytone[i]);
       delay(400*mytime[i]);
       noTone(7);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
       i++;
    }
    else if(date == 14)
    {
      xunji();
    }
}

