# Servo-counter
# Harikrishna S B  # Jerald Baiju

Mechanical count down using servo motors based on RTC.


for photos and vedios the link is :


This project uses :
Adafruit PCA9685 16-Channel Servo Driver(x4)
Arduino Nano(x1)
DS1307 RTC(Module)(x1)
MG995 Servo motor with metal gear(x56)
power supply(5v/2A)(x5)

The idea is to build a mechanical counter that counts down,showning the time remaining before approching a particular date..
for example.. you wanna make a count down for newyear before 10 days(suppose),showing number of days,number of hours,number of minutes,number of seconds left...this project is for you.... 

note:you dont have to worry about power cuts(if u are taking power from the mains) since the RTC module keep track of the time even without external power...(not at all important...dont confuse yourelf :)    )....


let's get started.....

so we want the device to show
"00"(days)"00"(hours)"00"(minutes)"00"(seconds) on december 31st {following up with the above example)
so exactly 10 days before it should start with
"09"(days) "23"(hours)"59"(minutes)"59"(seconds) and count backwards
 i.e after next 10 seconds it should show "09"(days) "23"(hours)"59"(minutes)"49"(seconds)...
 I think you got this,now lets see how to show a digit .
 
 (i highly recommend learning a bit about how servo motors function and PCA9685 16-Channel Servo Driver
 https://learn.adafruit.com/16-channel-pwm-servo-driver?view=all)
 
 we are using 7 segments to display numbers.. 
 attach flaps to the servo motor shaft in such a way that its visible when motor rotates shaft through (90 degree) and goes inside when shaft goes back to (0 degree)..
 since every motor is different the pulse width for a 90 degree rotation will be different for different motors..PCA9685 servo driver helps to solve this issue by allowing us to
set the minimum and maximum pulse width for each channel.. (by minimum it is meant the value for which the flap goes inside..and maximum is the value for which flap is visible)
an array is to be created based on minimum and maximum values..(56 elements each) for each motor by trail and error method using the code"".

let visible flap corresponds to "1". and closed one be "0".
so numbers 0 to 9 can be represented as {"0111111"(0),"0000110"(1),"1011011"(2),"1001111"(3),"1100110"(4),"1101101"(5),"1111101"(6), "0000111"(7),"1111111"(8),"1101111"(9)}
note that this is for a single digit(7 flaps)...and we have 7 such other segments..

now lets see how to get the data to be put into each of these segments...
the RTC returns the time and date...
now all you have to do is subtract this from say 31st(in days) 23(in hours) 59(in minutes) 59(in seconds)
and pass it on to a function to set days,hours,minutes,seconds.

ps:the modules communicate using i2c protocol..make sure you solder appropriate pads on the servo driver module to set different slave addressess
