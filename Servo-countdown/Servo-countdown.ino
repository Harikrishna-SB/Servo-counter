#include <Wire.h> //for i2c protocol
#include <Adafruit_PWMServoDriver.h>
#include "RTClib.h"
 int seconds,minutes,hours,days;
 int preseconds,preminutes,prehours,predays;

RTC_DS1307 rtc;

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);//setting the address of servo driver modules
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x43);

void setup() {
  Serial.begin(9600);

  pwm1.begin();  //initiating communication with all the servo driver modules
  pwm1.setPWMFreq(50); 

  pwm2.begin();
  pwm2.setPWMFreq(50);

  pwm3.begin();
  pwm3.setPWMFreq(50); 

  pwm4.begin();
  pwm4.setPWMFreq(50);
    while (!Serial);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //uncomment to let compiler set the time.
  //rtc.adjust(DateTime(2019, 10, 16, 00, 00, 00));//uncomment for manually setting the time.
   
  preseconds=0;
  preminutes=0;
  prehours=0;
  predays=0;
}
int mxp[]={ 390,395,380,365,390,370,385, 360,380,360,370,360,380,365 ,370,360,360,360,360,380,360 ,360,360,360,360,360,360,360, 
                  360,360,360,360,360,370,360 ,360,360,360,360,360,400,370 ,360,360,360,360,360,360,380, 360,360,360,360,360,360,360};//maximum values

                 
int mnp[]={220,200,220,220,220,220,220 ,220,210,220,220,220,220,220 ,220,210,220,220,210,220,220 ,220,220,190,220,220,210,210,
                  220,220,220,220,220,220,220 ,220,220,220,220,200,220,220 ,220,220,205,220,220,220,220 ,220,220,220,220,220,220,220};//Minimum values


char data[][7] = {"0111111","0000110","1011011","1001111","1100110","1101101","1111101", "0000111","1111111","1101111"};//(0-9)


//for setting seconds

void setseconds(int sec)
{int a,b;//let the number be "ab"
a=sec/10;
b=sec%10;
Serial.print("a =");Serial.println(a);//Tens place
delay(10);
Serial.print("b =");Serial.println(b);//units place
delay(10);

  for(int j=0;j<7;j++)
{  
  if(data[b][j]=='0')
  pwm1.setPWM(j,0,mnp[j]);
  if(data[b][j]=='1')
  pwm1.setPWM(j,0,mxp[j]);
 
}
delay(10);
 for(int i=8;i<15;i++)
{ Serial.println(data[a][i-8]);
  delay(10);
  if(data[a][i-8]=='0')
  
  {
  pwm1.setPWM(i,0,mnp[i-1]);
  
  }
  
  if(data[a][i-8]=='1')
  pwm1.setPWM(i,0,mxp[i-1]);
}

}



//for setting minutes

void setminutes(int mins)
{int c,d;//let the number be "ab"
c=mins/10;
d=mins%10;
Serial.print("c =");Serial.println(c);
delay(10);
Serial.print("d =");Serial.println(d);
delay(10);

  for(int j=0;j<7;j++)
{  
  if(data[d][j]=='0')
  pwm2.setPWM(j,0,mnp[j+14]);
  if(data[d][j]=='1')
  pwm2.setPWM(j,0,mxp[j+14]);
 
}
delay(10);
 for(int i=8;i<15;i++)
{ Serial.println(data[c][i-8]);
  delay(10);
  if(data[c][i-8]=='0')
  
  {
  pwm2.setPWM(i,0,mnp[i+13]);
  
  }
  
  if(data[c][i-8]=='1')
  pwm2.setPWM(i,0,mxp[i+13]);
}

}




//for setting hours

void sethours(int hrs)
{int e,f;//let the number be "ab"
e=hrs/10;
f=hrs%10;
Serial.print("e =");Serial.println(e);
delay(10);
Serial.print("f =");Serial.println(f);
delay(10);

  for(int j=0;j<7;j++)
{  
  if(data[f][j]=='0')
  pwm3.setPWM(j,0,mnp[j+28]);
  if(data[f][j]=='1')
  pwm3.setPWM(j,0,mxp[j+28]);
 
}
delay(10);
 for(int i=8;i<15;i++)
{ Serial.println(data[e][i-8]);
  delay(10);
  if(data[e][i-8]=='0')
  
  {
  pwm3.setPWM(i,0,mnp[i+27]);
  
  }
  
  if(data[e][i-8]=='1')
  pwm3.setPWM(i,0,mxp[i+27]);
}

}


//for setting days

void setdays(int dys)
{int g,h;//let the number be "ab"
g=dys/10;
h=dys%10;
Serial.print("g =");Serial.println(g);
delay(10);
Serial.print("h =");Serial.println(h);
delay(10);

  for(int j=0;j<7;j++)
{  
  if(data[h][j]=='0')
  pwm4.setPWM(j,0,mnp[j+42]);
  if(data[h][j]=='1')
  pwm4.setPWM(j,0,mxp[j+42]);
 
}
delay(10);
 for(int i=8;i<15;i++)
{ Serial.println(data[g][i-8]);
  delay(10);
  if(data[g][i-8]=='0')
  
  {
  pwm4.setPWM(i,0,mnp[i+41]);
  
  }
  if(data[g][i-8]=='1')
  pwm4.setPWM(i,0,mxp[i+41]);
}

}


  void loop()
{

  DateTime now = rtc.now();
  if(now.day()==1)//new year
  {
   //write a new function which should be executed after all digits turn "0";
    delay(100);
  }
  else  
    { 
      
      hours=(23-now.hour());
      days=(31-now.day());   
      minutes=(59-now.minute());
      seconds=(59-now.second());

      
    
    Serial.print(days);Serial.print("d  ");Serial.print(hours);Serial.print("hrs  ");Serial.print(minutes);Serial.print("mins  ");
    Serial.print(seconds);Serial.println("sec");//for serial monitor

 
  if((seconds-preseconds)!=0)//update only if there is a change in the previous state..
    setseconds(seconds);     //we dont want all the 56 segments updated every second
    if((minutes-preminutes)!=0)//only the digits that change are updated else its gonna loop again
    setminutes(minutes);
    if((hours-prehours)!=0)
    sethours(hours);
   if((days-predays)!=0)
    setdays(days); 
     
  
  preseconds=seconds;
  preminutes=minutes;
  prehours=hours;
  predays=days;

  delay(800);
  
    }
}
  
                  
