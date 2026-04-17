#include "hexpod.h"
#include "Arduino.h"

//add some libraries
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include<Wire.h>
#include <SR04.h>
#include "angle.h"

//define pins
#define TRIG_PIN A2
#define ECHO_PIN A3
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);



//Declaring some global variables
int gyro_x, gyro_y, gyro_z;
long acc_x, acc_y, acc_z, acc_total_vector;
int temperature;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
long loop_timer;
int lcd_loop_counter;
float angle_pitch, angle_roll,angle_yaw;
int angle_pitch_buffer, angle_roll_buffer;
boolean set_gyro_angles;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_output,angle_yaw_output;
float angle_changed;
long a;
bool steaty_on = false;
SoftwareSerial *p_softwareSerial;

// Create servo object
  Servo s0;
  Servo s1;
  Servo s2;
  Servo s3;
  Servo s4;
  Servo s5;
  Servo s6;
  Servo s7;
  Servo s8;
  Servo s9;
  Servo s10;
  Servo s11;
  Servo s12;

int i0H0 = 0;
int i1H0 = 0;
int i2H0 = 0;
int i3H0 = 0;
int i4H0 = 0;
int i5H0 = 0;
int i6H0 = 0;
int i7H0 = 0;
int i8H0 = 0;
int i9H0 = 0;
int i10H0 = 0;
int i11H0 = 0;
int i12H0 = 0;
  
int i0H1 = 0;
int i1H1 = 0;
int i2H1 = 0;
int i3H1 = 0;
int i4H1 = 0;
int i5H1 = 0;
int i6H1 = 0;
int i7H1 = 0;
int i8H1 = 0;
int i9H1 = 0;
int i10H1 = 0;
int i11H1 = 0;
int i12H1 = 0;

int i0H2 = 0;
int i1H2 = 0;
int i2H2 = 0;
int i3H2 = 0;
int i4H2 = 0;
int i5H2 = 0;
int i6H2 = 0;
int i7H2 = 0;
int i8H2 = 0;
int i9H2 = 0;
int i10H2 = 0;
int i11H2 = 0;
int i12H2 = 0;

int i0H3 = 0;
int i1H3 = 0;
int i2H3 = 0;
int i3H3 = 0;
int i4H3 = 0;
int i5H3 = 0;
int i6H3 = 0;
int i7H3 = 0;
int i8H3 = 0;
int i9H3 = 0;
int i10H3 = 0;
int i11H3 = 0;
int i12H3 = 0;

int i0H4 = 0;
int i1H4 = 0;
int i2H4 = 0;
int i3H4 = 0;
int i4H4 = 0;
int i5H4 = 0;
int i6H4 = 0;
int i7H4 = 0;
int i8H4 = 0;
int i9H4 = 0;
int i10H4 = 0;
int i11H4= 0;
int i12H4 = 0;

int i0H5 = 0;
int i1H5 = 0;
int i2H5 = 0;
int i3H5 = 0;
int i4H5 = 0;
int i5H5 = 0;
int i6H5 = 0;
int i7H5 = 0;
int i8H5 = 0;
int i9H5 = 0;
int i10H5 = 0;
int i11H5= 0;
int i12H5 = 0;

int status0 = 0;
int status1 = 0;
int status2 = 0;
int status3 = 0;
int status4 = 0;
int status5 = 0;


int actionspeed=1;
unsigned long showtime = 0;
char serialcom;
int angle=20;
char right=0;
char count = 0;
long counter=0;



QUANRUPED::QUANRUPED()
{
  ;
}

QUANRUPED::QUANRUPED(SoftwareSerial *p_Serial)
{
  p_softwareSerial = p_Serial;
}

QUANRUPED::~QUANRUPED()
{
  ;
}

bool is_steaty_on()
{
  return steaty_on;
}
 

void QUANRUPED::try_steaty()
{
  if (true == is_steaty_on())
  {
    Serial.println("try_steaty: true");
    steaty();
  }
}
 
void steaty_off()
{
  if (true == is_steaty_on())
  {
    steaty_on = false;
  }
}
 
//This is the initialization angle of each leg, you can modify the following values according to your needs.
void original_latest(){
  s0.write(angle0);//D2
  s1.write(angle1);//D3
  s2.write(angle2);//D4
  s3.write(angle3);//D5
  s4.write(angle4);//D6
  s5.write(angle5); //D7
  s6.write(angle6);//D8
  s7.write(angle7); //D9
  s8.write(angle8);//D10
  s9.write(angle9); //D11
  s11.write(angle10);//D12
  s10.write(angle11);//D13
  s12.write(angle12);//D14
}

void QUANRUPED::servo_init()
{
  s0.write(angle0);//D2
  s1.write(angle1);//D3
  s2.write(angle2);//D4
  s3.write(angle3);//D5
  s4.write(angle4);//D6
  s5.write(angle5); //D7
  s6.write(angle6);//D8
  s7.write(angle7); //D9
  s8.write(angle8);//D10
  s9.write(angle9); //D11
  s11.write(angle10);//D12
  s10.write(angle11);//D13
  s12.write(angle12);//D14
}

void QUANRUPED::servo_attach()
{
	s0.attach(2);     s1.attach(3);     s2.attach(4);     s3.attach(5);     s4.attach(6);     s5.attach(7);     s6.attach(8);     s7.attach(9);     s8.attach(10);    s9.attach(11);    s10.attach(12);     s11.attach(13); s12.attach(A0);
  s0.write(angle0); s1.write(angle1); s2.write(angle2); s3.write(angle3); s4.write(angle4); s5.write(angle5); s6.write(angle6); s7.write(angle7); s8.write(angle8); s9.write(angle9); s10.write(angle10); s11.write(angle11); s12.write(angle12); 	
}

void QUANRUPED::moveforward()
{
  if(is_steaty_on()){
    steaty_off();
  }

	/******************step 1 to step 2************************/
  /**********rotate forward and rotate backward to the initial position**********/
  //PROCESS 4:(raise the second leg)
  while(status4<=45){
    status4++;
    s0.write(angle0);

    s2.write(angle2-i2H4);//100-i2H4
    i2H4++;
    if(i2H4==46 ){
      i2H4=0;
    }

    delay(actionspeed);
    s4.write(angle4);

    s6.write(angle6+i6H4);//90+i6H4
    i6H4++;
    if(i6H4==46){
        i6H4=0;
    }

    delay(actionspeed);

    s8.write(angle8);

    s10.write(angle10+i10H4);//90+i10H4
      i10H4++;
      if(i10H4==46){
        i10H4=0;
      }

    delay(actionspeed);

    if(status4>45){
      status4=0;
      break;
    }
  }

  //PROCESS 3:
  /*(rorate second leg forward move second leg back to the ground) and
  (torate first leg backward)*/
  while(status3<=45){
    status3++;
    // Move back to touch the ground1

    s0.write(angle0);//90
    s1.write(angle1-i1H3);
    i1H3++;
    if(i1H3==46){
      i1H3=0;
    }
      
    // delay(1);
    delay(actionspeed);

    // Rise the leg2
    s2.write(angle2-45+i2H3);
    i2H3++;
    if(i2H3==46){
      i2H3=0;
    }
    s3.write(angle3-45+i3H3);//45+i3H3
    i3H3++; 
    if(i3H3==46){
      i3H3=0;
    }
    
    // delay(1);
    delay(actionspeed);
    // Move back to touch the ground3
    s4.write(angle4);  //90
    s5.write(angle5+30-i5H3);                              //165-i5H3
    i5H3++;
    if(i5H3==46){
      i5H3=0;
    }
    
    //delay(1);
    delay(actionspeed);
    // Rise the leg4
    s6.write(angle6+45-i6H3);
    i6H3++;
    if(i6H3==46){
        i6H3=0;
    }
    s7.write(angle7+45-i7H3);
    i7H3++;
    if(i7H3==46){
      i7H3=0;
    }
    
    delay(actionspeed);
    // Move back to touch the ground5
    s8.write(angle8);  //90
    s9.write(angle9-17.5+i9H3);//50+i9H3
    i9H3++;
    if(i9H3==46){
      i9H3=0;
    }
    
    delay(actionspeed);  

    // Rise the leg6
    s10.write(angle10+45-i10H3);
    i10H3++;
    if(i10H3==46){
      i10H3=0;
    }
    s11.write(angle11-i11H3);                                          //45-i11H3
    i11H3++;
    if(i11H3==46){
      i11H3=0;
    }
    
    delay(actionspeed);
  
    if(status3>45){
      status3 = 0;
      break;
    }
  }

  /*********rotate backward to the initial position and rotate forward**********/
  //PROCESS 5:(raise the first leg)
  while(status5<=45){
    status5++;
    s0.write(angle0-i0H5);//90-i0H5
    i0H5++;
    if(i0H5==46){
      i0H5=0;
    }

    s2.write(angle2);
    delay(actionspeed);
    s4.write(angle4-i4H5);//90-i4H5
    i4H5++;
    if(i4H5==46){
      i4H5=0;
    }

    s6.write(angle6);
    
    delay(actionspeed);
    s8.write(angle8+i8H5);//90+i8H5
      i8H5++;
      if(i8H5==46){
        i8H5=0;
      }

    s10.write(angle10);
    delay(actionspeed);

    if(status5>45){
      status5=0;
      break;
    }
  }


  //PROCESS 1:
  /*(rorate first leg forward move first leg back to the ground) and
  (rorate second leg backward)*/
  while(status1<=45){
    status1++;
    // Rise the leg1
    s0.write(angle0-45+i0H1);
    i0H1++;
    if(i0H1==46){
      i0H1=0;
    }
    s1.write(angle1-45+i1H1); 
    i1H1++;
    if(i1H1==46){
      i1H1=0;
    }
  
    delay(actionspeed);
    // Move back to touch the ground2       
    s2.write(angle2); 
    s3.write(angle3-i3H1);//90-i3H1
    i3H1++;
    if(i3H1==46){
      i3H1=0;                       
    }
                        
    delay(actionspeed);
    // Rise the leg3
    s4.write(angle4-45+i4H1);
    i4H1++;
    if(i4H1==46){
      i4H1=0;
    }

    s5.write(angle5-15+i5H1);//120+i5H1
    i5H1++;
    if(i5H1==46){
      i5H1=0;
    }
    
    delay(actionspeed);
    // Move back to touch the ground4
    s6.write(angle6); 
    s7.write(angle7+i7H1);
    i7H1++;
    if(i7H1==46){
      i7H1=0;
    }
    
    delay(actionspeed);
    // Rise the leg5
    s8.write(angle8+45-i8H1);
    i8H1++;
    if(i8H1==46){
      i8H1=0;
    }

    s9.write(angle9+27.5-i9H1);//95-i9H1
    i9H1++;
    if(i9H1==46){
      i9H1=0;
    }
    
    delay(actionspeed);
    
    // Move back to touch the ground6
    s10.write(angle10);
    s11.write(angle11-45+i11H1);//0+i11H1
    i11H1++;
    if(i11H1==46){
      i11H1=0;
    }
  
    delay(actionspeed);
    if(status1>45){
      status1 = 0;
      break;
    }
  }
}

void QUANRUPED::movebackward()
{
  if(is_steaty_on()){
    steaty_off();
  }
  
  /******************step 1 to step 2************************/
  // Rotate the leg1
 //PROCESS 5:
  
  while(status5<=45){
    status5++;
    s0.write(angle0-i0H5);
    i0H5++;
    if(i0H5==46){
      i0H5=0;
    }

    s2.write(angle2);
    delay(actionspeed);
    s4.write(angle4-i4H5);
      i4H5++;
      if(i4H5==46){
        i4H5=0;
      }
  
    s6.write(angle6);

    delay(actionspeed);
    s8.write(angle8+i8H5);
      i8H5++;
      if(i8H5==46){
        i8H5=0;
      }
      
    s10.write(angle10);
    delay(actionspeed);
    if(status5>45){
      status5=0;
      break;
    }
  }

  //PROCESS 3:
  while(status3<=45){
    status3++;
    // Move back to touch the ground1
    s0.write(angle0-45+i0H3);
    i0H3++;
    if(i0H3==46){
        i0H3=0;
    }
    s1.write(angle1-i1H3);
    i1H3++;
    if(i1H3==46){
      i1H3=0;
    }
    
    delay(actionspeed);
    
    // Rise the leg2
    s2.write(angle2);
    s3.write(angle3-45+i3H3);//45+i3H3
    i3H3++; 
    if(i3H3==46){
      i3H3=0;
    }

    delay(actionspeed);
    
    // Move back to touch the ground3
    s4.write(angle4-45+i4H3); 
    i4H3++;
    if(i4H3==46){
      i4H3=0;
    }

    s5.write(angle5+30-i5H3);//165-i5H3
    i5H3++;
    if(i5H3==46){
      i5H3=0;
    }
    
   delay(actionspeed);
  
    // Rise the leg4
    s6.write(angle6);
    s7.write(angle7+45-i7H3);
    i7H3++;
    if(i7H3==46){
      i7H3=0;
    }
    
    delay(actionspeed);

    // Move back to touch the ground5
    s8.write(angle8+45-i8H3);
    i8H3++;
    if(i8H3==46){
        i8H3=0;
    }

    s9.write(angle9-17.5+i9H3);//50+i9H3
    i9H3++;
    if(i9H3==46){
      i9H3=0;
    }

    delay(actionspeed);

    // Rise the leg6
    s10.write(angle10);
    s11.write(angle11-i11H3);//45-i11H3
    i11H3++;
    if(i11H3==46){
      i11H3=0;
    }
    
    delay(actionspeed);

    if(status3>45){
      status3 = 0;
      break;
    }
  }

  /*********rotate backward to the initial position and rotate forward**********/

  //PROCESS 4:
  while(status4<=45){
    status4++;
    s0.write(angle0);
    
    s2.write(angle2-i2H4);
    i2H4++;
    if(i2H4==46){
      i2H4=0;
    }

    delay(actionspeed);
    s4.write(angle4);
    
    s6.write(angle6+i6H4);
      i6H4++;
    if(i6H4==46){
        i6H4=0;
    }
    
    delay(actionspeed);

    s8.write(angle8);
    
    s10.write(angle10+i10H4);
      i10H4++;
      if(i10H4==46){
        i10H4=0;
    }
    
    delay(actionspeed);

    if(status4>45){
      status4=0;
      break;
    }
  }

  //PROCESS 1:
  while(status1<=45){
    status1++;
    
    // Rise the leg1
    s0.write(angle0);
    s1.write(angle1-45+i1H1); 
    i1H1++;
    if(i1H1==46){
      i1H1=0;
    }
    
    //  delay(1); 
    delay(actionspeed);
    
    // Move back to touch the ground2       
    s2.write(angle2-45+i2H1);
    i2H1++;
    if(i2H1==46){
      i2H1=0;                           
    }

    s3.write(angle3-i3H1);//90-i3H1
    i3H1++;
    if(i3H1==46){
      i3H1=0;                       
    }
    
    delay(actionspeed);
    
    // Rise the leg3
    s4.write(angle4);
    s5.write(angle5-15+i5H1);//120+i5H1
    i5H1++;
    if(i5H1==46){
      i5H1=0;
    }
    
    delay(actionspeed);
    
    // Move back to touch the ground4
    s6.write(angle6+45-i6H1);
    i6H1++;
    if(i6H1==46){
        i6H1=0;
    }

    s7.write(angle7+i7H1);
    i7H1++;
    if(i7H1==46){
      i7H1=0;
    }

    delay(actionspeed);
    // Rise the leg5
    s8.write(angle8);
    s9.write(angle9+27.5-i9H1);//95-i9H1
    i9H1++;
    if(i9H1==46){
      i9H1=0;
    }
    
    delay(actionspeed);
    
    // Move back to touch the ground6
    s10.write(angle10+45-i10H1);
    i10H1++;
    if(i10H1==46){
        i10H1=0;
    }
    s11.write(angle11-45+i11H1);//0+i11H1
    i11H1++;
    if(i11H1==46){
      i11H1=0;
    }
    
    //  delay(1);  
    delay(actionspeed);

    if(status1>45){
      status1 = 0;
      break;
    }
  }

  /**********rotate forward and rotate backward to the initial position**********/
}

void QUANRUPED::turnright()
{
  if(is_steaty_on()){
    steaty_off();
  }
  
  /********************step 1  first******************************/  
  //PROCESS 4:(raise the second leg)
  while(status4<=45){
    status4++;
    s0.write(angle0);
    
    s2.write(angle2-i2H4);
    i2H4++;
    if(i2H4==46){
      i2H4=0;
    }
    
    delay(actionspeed);
    s4.write(angle4);

    s6.write(angle6+i6H4);
    i6H4++;
    if(i6H4==46){
        i6H4=0;
    }
    
    delay(actionspeed);

    s8.write(angle8);

    s10.write(angle10+i10H4);
      i10H4++;
      if(i10H4==46){
        i10H4=0;
    }
    
    delay(actionspeed);
    
    if(status4>45){
      status4=0;
      break;
    }
  }

  //PROCESS 3:
  /*(rorate second leg forward move second leg back to the ground) and
  (torate first leg backward)*/
  while(status3<=45){
    status3++;
    // Move back to touch the ground1
    s0.write(angle0);

    s1.write(angle1-i1H3);
    i1H3++;
    if(i1H3==46){
      i1H3=0;
    }
       
    delay(actionspeed);
    // Rise the leg2
    s2.write(angle2-45+i2H3);
    i2H3++;
    if(i2H3==46){
      i2H3=0;
    }

    s3.write(angle3-45+i3H3);//45+i3H3
    i3H3++; 
    if(i3H3==46){
      i3H3=0;
    }
    delay(actionspeed);
    
    // Move back to touch the ground3
    s4.write(angle4);
    s5.write(angle5+30-i5H3);//165-i5H3
    i5H3++;
    if(i5H3==46){
      i5H3=0;
    }
      
    delay(actionspeed);
    // Rise the leg4

    s6.write(angle6+45-i6H3);
    i6H3++;
    if(i6H3==46){
      i6H3=0;
    }  

    s7.write(angle7+i7H3);
    i7H3++;
    if(i7H3==46){
      i7H3=0;
    }
    delay(actionspeed);
    
    // Move back to touch the ground5
    s8.write(angle8);
    s9.write(angle9+27.5-i9H3);//95-i9H3
    i9H3++;
    if(i9H3==46){
      i9H3=0;
    }
      
    delay(actionspeed);

    // Rise the leg6
    s10.write(angle10+45-i10H3);
    i10H3++;
    if(i10H3==46){
      i10H3=0;
    }

    s11.write(angle11-45+i11H3);//0+i11H3
    i11H3++;
    if(i11H3==46){
      i11H3=0;
    }

    delay(actionspeed);

    if(status3>45){
      status3 = 0;
      break;
    }  
  }

  /*********rotate backward to the initial position and rotate forward**********/

  //PROCESS 5:(raise the first leg)
  while(status5<=45){
    status5++;
    s0.write(angle0-i0H5);
    
    i0H5++;
    if(i0H5==46){
      i0H5=0;
    }
    
    s2.write(angle2);
    delay(actionspeed);
    s4.write(angle4-i4H5);
    i4H5++;
    if(i4H5==46){
      i4H5=0;
    }
    
    s6.write(angle6);
  
    delay(actionspeed);
    s8.write(angle8+i8H5);
    i8H5++;
    if(i8H5==46){
      i8H5=0;
    }
    
    s10.write(angle10);
    delay(actionspeed);

    if(status5>45){
      status5=0;
      break;
    }
  }

  //PROCESS 1:
  /*(rorate first leg forward move first leg back to the ground) and
  (torate second leg backward)*/
  while(status1<=45){
    status1++;
    // Rise the leg1
    s0.write(angle0-45+i0H1);
    i0H1++;
    if(i0H1==46){
      i0H1=0;
    }

    s1.write(angle1-45+i1H1); 
    i1H1++;
    if(i1H1==46){
      i1H1=0;
    }

    delay(actionspeed);
  
    // Move back to touch the ground2       
    s2.write(angle2); 
    s3.write(angle3-i3H1);//90-i3H1
    i3H1++;
    if(i3H1==46){
      i3H1=0;                       
    }
    delay(actionspeed);    
    
    // Rise the leg3
    s4.write(angle4-45+i4H1);
    i4H1++;
    if(i4H1==46){
      i4H1=0;
    }

    s5.write(angle5-15+i5H1);//120+i5H1
    i5H1++;
    if(i5H1==46){
      i5H1=0;
    }
    delay(actionspeed);
    
    // Move back to touch the ground4
    s6.write(angle6);
    s7.write(angle7+45-i7H1);
    i7H1++;
    if(i7H1==46){
      i7H1=0;
    }
    delay(actionspeed);
    
    // Rise the leg5 
    s9.write(angle9-17.5+i9H1);//50+i9H1
    i9H1++;
    if(i9H1==46){
      i9H1=0;
    }

    s8.write(angle8+45-i8H1);
    i8H1++;
    if(i8H1==46){
      i8H1=0;
    }

    delay(actionspeed);
    
    // Move back to touch the ground6
    s10.write(angle10);
    s11.write(angle11-i11H1);//45-i11H1
    i11H1++;
    if(i11H1==46){
      i11H1=0;
    }

    delay(actionspeed);
    
    if(status1>45){
      status1 = 0;
      break;
    }
  }

  /**********rotate forward and rotate backward to the initial position**********/    
}

void QUANRUPED::turnleft()
{
  if(is_steaty_on()){
    steaty_off();
  }
  
  /********************step 1  third******************************/  
  //PROCESS 4:(raise the second leg)
  while(status4<=45){
    status4++;
    s0.write(angle0);
    
    s2.write(angle2-i2H4);
    i2H4++;
    if(i2H4==46){
      i2H4=0;
    }
    
    delay(actionspeed);
    s4.write(angle4);
    
    s6.write(angle6+i6H4);
    i6H4++;
    if(i6H4==46){
        i6H4=0;
    }
      
    delay(actionspeed);
    s8.write(angle8);
    
    s10.write(angle10+i10H4);
    i10H4++;
    if(i10H4==46){
      i10H4=0;
    }
    
    delay(actionspeed);
    
    if(status4>45){
      status4=0;
      break;
    }
  }

  //PROCESS 3:
  /*(rorate second leg forward move second leg back to the ground) and
  (torate first leg backward)*/
  while(status3<=45){
    status3++;
    // Move back to touch the ground1
    s0.write(angle0);
    s1.write(angle1-45+i1H3);
    i1H3++;
    if(i1H3==46){
      i1H3=0;
    }
       
    delay(actionspeed);
    // Rise the leg2
    s2.write(angle2-45+i2H3);
    i2H3++;
    if(i2H3==46){
      i2H3=0;
    }

    s3.write(angle3-i3H3);//90-i3H3
    i3H3++; 
    if(i3H3==46){
      i3H3=0;
    }

    delay(actionspeed);
    
    // Move back to touch the ground3
    s4.write(angle4);
    s5.write(angle5-15+i5H3);//120+i5H3
    i5H3++;
    if(i5H3==46){
      i5H3=0;
    }
      
    delay(actionspeed);
    // Rise the leg4

    s6.write(angle6+45-i6H3);
    i6H3++;
    if(i6H3==46){
      i6H3=0;
    }  
    s7.write(angle7+45-i7H3);
    i7H3++;
    if(i7H3==46){
      i7H3=0;
    }
    
    delay(actionspeed); 

    // Move back to touch the ground5
    s8.write(angle8);
    s9.write(angle9-17.5+i9H3);//50+i9H3
    i9H3++;
    if(i9H3==46){
      i9H3=0;
    }
      
    delay(actionspeed);

    // Rise the leg6
    s10.write(angle10+45-i10H3);
    i10H3++;
    if(i10H3==46){
      i10H3=0;
    }

    s11.write(angle11-i11H3);//45-i11H3
    i11H3++;
    if(i11H3==46){
      i11H3=0;
    }

    delay(actionspeed);
 
    if(status3>45){
      status3 = 0;
      break;
    }

  }

  /*********rotate backward to the initial position and rotate forward**********/

  //PROCESS 5:(raise the first leg)
  while(status5<=45){
    status5++;
    s0.write(angle0-i0H5);
    i0H5++;
    if(i0H5==46){
      i0H5=0;
    }
    
    s2.write(angle2);
    
    delay(actionspeed);
    s4.write(angle4-i4H5);
    i4H5++;
    if(i4H5==46){
      i4H5=0;
    }
    
    s6.write(angle6);
    
    delay(actionspeed);
    s8.write(angle8+i8H5);
    i8H5++;
    if(i8H5==46){
      i8H5=0;
    }
    
    s10.write(angle10);
    delay(actionspeed);

    if(status5>45){
      status5=0;
      break;
    }
  }

  //PROCESS 1:
  /*(rorate first leg forward move first leg back to the ground) and
  (torate second leg backward)*/
  while(status1<=45){
    status1++;
    // Rise the leg1
    s0.write(angle0-45+i0H1);
    i0H1++;
    if(i0H1==46){
      i0H1=0;
    }
    s1.write(angle1-i1H1); 
    i1H1++;
    if(i1H1==46){
      i1H1=0;
    }
    delay(actionspeed);
    
    // Move back to touch the ground2       
    s2.write(angle2); 
    s3.write(angle3-45+i3H1);//45+i3H1
    i3H1++;
    if(i3H1==46){
      i3H1=0;                       
    }
    delay(actionspeed);      
    
  // Rise the leg3
    s4.write(angle4-45+i4H1);
    i4H1++;
    if(i4H1==46){
      i4H1=0;
    }

    s5.write(angle5+30-i5H1);//165-i5H1
    i5H1++;
    if(i5H1==46){
      i5H1=0;
    }
    delay(actionspeed);
    
    // Move back to touch the ground4
    s6.write(angle6);
    s7.write(angle7+i7H1);
    i7H1++;
    if(i7H1==46){
      i7H1=0;
    }
    delay(actionspeed);
    
    // Rise the leg5
    s8.write(angle8+45-i8H1);
    i8H1++;
    if(i8H1==46){
      i8H1=0;
    }
    s9.write(angle9+27.5-i9H1);//95-i9H1
    i9H1++;
    if(i9H1==46){
      i9H1=0;
    }
    
    delay(actionspeed);
    
    // Move back to touch the ground6
    s10.write(angle10);
    s11.write(angle11-45+i11H1);//0+i11H1
    i11H1++;
    if(i11H1==46){
      i11H1=0;
    }
    delay(actionspeed);  
    
    if(status1>45){
      status1 = 0;
      break;
    }
  }
  /**********rotate forward and rotate backward to the initial position**********/
}

void QUANRUPED::advoid()
{  
  if(is_steaty_on()){
    steaty_off();
  }
  
  /**********rotate forward and rotate backward to the initial position**********/
  //PROCESS 4:(raise the second leg)
  while(status4<=45){
    status4++;
    s0.write(angle0);
    s2.write(angle2+10-i2H4);//100-i2H4
    i2H4++;
    if(i2H4==46 ){
      i2H4=0;
    }
      
    delay(actionspeed);
    s4.write(angle4);
    
    s6.write(angle6+i6H4);//90+i6H4
    i6H4++;
    if(i6H4==46){
        i6H4=0;
    }
    
    delay(actionspeed);

    s8.write(angle8);
  
    s10.write(angle10+i10H4);//90+i10H4
    i10H4++;
    if(i10H4==46){
      i10H4=0;
    }
    
    delay(actionspeed);
    s12.write(angle12+i12H4);
      
    if(i12H4<=20){
      i12H4++;
    }

    else{
      i12H4=20;
    }

    if(status4>45){
      status4=0;
      i12H4=0;
      break;
    }
    if(Serial.available()>0){
      break;
    }
  }
    
  //PROCESS 3:
  /*(rorate second leg forward move second leg back to the ground) and
  (torate first leg backward)*/
  while(status3<=45){
    status3++;

    // Move back to touch the ground1
    s0.write(angle0);//90
    s1.write(angle1-i1H3);
    i1H3++;
    if(i1H3==46){
      i1H3=0;
    }
      
    delay(actionspeed);

    // Rise the leg2
    s2.write(angle2-45+i2H3);
    i2H3++;
    if(i2H3==46){
      i2H3=0;
    }

    s3.write(angle3-67.5+i3H3);//45+i3H3
    i3H3++; 
    if(i3H3==46){
      i3H3=0;
    }
    
    delay(actionspeed);

    // Move back to touch the ground3
    s4.write(angle4);  //90
    s5.write(angle5+30-i5H3);                              //165-i5H3
    i5H3++;
    if(i5H3==46){
      i5H3=0;
    }
    
    delay(actionspeed);

    // Rise the leg4
    s6.write(angle6+45-i6H3);
    i6H3++;
    if(i6H3==46){
        i6H3=0;
    }

    s7.write(angle7+45-i7H3);
    i7H3++;
    if(i7H3==46){
      i7H3=0;
    }
    
    delay(actionspeed);

    // Move back to touch the ground5
    s8.write(angle8);  //90
    s9.write(angle9-17.5+i9H3);//50+i9H3
    i9H3++;
    if(i9H3==46){
      i9H3=0;
    }
    
    delay(actionspeed);  

    // Rise the leg6
    s10.write(angle10+45-i10H3);
    i10H3++;
    if(i10H3==46){
      i10H3=0;
    }

    s11.write(angle11-i11H3);                                          //45-i11H3
    i11H3++;
    if(i11H3==46){
      i11H3=0;
    }
    
    delay(actionspeed);
    s12.write(angle12+20-i12H3);
    
    if(i12H3<=20){
      i12H3++;
    }
    else{
      i12H3=20;
    }
    
    if(status3>45){
      status3 = 0;
      i12H3=0;
      break;
    }
    if(Serial.available()>0){
      break;
    }
  }
  /*********rotate backward to the initial position and rotate forward**********/

  //PROCESS 5:(raise the first leg)
  while(status5<=45){
    status5++;
    s0.write(angle0-i0H5);//90-i0H5
    i0H5++;
    if(i0H5==46){
      i0H5=0;
    }
    
    s2.write(angle2);
  
    delay(actionspeed);
    s4.write(angle4-i4H5);//90-i4H5
      i4H5++;
      if(i4H5==46){
        i4H5=0;
      }
  
    s6.write(angle6);
    
    delay(actionspeed);
    s8.write(angle8+i8H5);//90+i8H5
    i8H5++;
    if(i8H5==46){
      i8H5=0;
    }

    s10.write(angle10);

    delay(actionspeed);
    s12.write(angle12-i12H5);

    if(i12H5<=20){
      i12H5++;
    }
    else{
      i12H5=20;
    }

    if(status5>45){
      status5=0;
      i12H5=0;
      break;
    }
    if(Serial.available()>0){
      break;
    }
  }

  //PROCESS 1:
  /*(rorate first leg forward move first leg back to the ground) and
  (rorate second leg backward)*/
  while(status1<=45){
    status1++;
    // Rise the leg1
    s0.write(angle0-45+i0H1);
    i0H1++;
    if(i0H1==46){
      i0H1=0;
    }
    s1.write(angle1-45+i1H1); 
    i1H1++;
    if(i1H1==46){
      i1H1=0;
    }
    
    delay(actionspeed);
    // Move back to touch the ground2       
    s2.write(angle2); 
    s3.write(angle3-22.5-i3H1);//90-i3H1
    i3H1++;
    if(i3H1==46){
      i3H1=0;                       
    }
                
    delay(actionspeed);
  
    // Rise the leg3
    s4.write(angle4-45+i4H1);
    i4H1++;
    if(i4H1==46){
      i4H1=0;
    }

    s5.write(angle5-25+i5H1);//120+i5H1
    i5H1++;
    if(i5H1==46){
      i5H1=0;
    }
    
    delay(actionspeed);
    // Move back to touch the ground4
    s6.write(angle6); 
    s7.write(angle7+i7H1);
    i7H1++;
    if(i7H1==46){
      i7H1=0;
    }
    
    delay(actionspeed);

    // Rise the leg5
    s8.write(angle8+45-i8H1);
    i8H1++;
    if(i8H1==46){
      i8H1=0;
    }

    s9.write(angle9+27.5-i9H1);//95-i9H1
    i9H1++;
    if(i9H1==46){
      i9H1=0;
    }
    
    delay(actionspeed);
    
    // Move back to touch the ground6
    s10.write(angle10);
    s11.write(angle11-45+i11H1);//0+i11H1
    i11H1++;
    if(i11H1==46){
      i11H1=0;
    }
      
    delay(actionspeed);
    s12.write(angle12-20+i12H1);

    if(i12H1<=20){
      i12H1++;
    }
    else{
      i12H1=20;
    }
  
    if(status1>45){
      status1 = 0;
      i12H1=0;
      break;
      }
      if(Serial.available()>0){
        break;
      }
    }

    ultrasonic();
    if(a<=20 && a>0){
      while(right<6){
        right++;
        turnright();
        if(Serial.available()>0){
        break;
        }
      }
      right=0;
    }

}

void QUANRUPED::ultrasonic()
{
	a=sr04.Distance();
  if(a>100){
    a=0;
  }
  
  Serial.print(a);
  Serial.println("cm");
}

void step_by_step(){
  while(status2<=45){
    status2++;
    s0.write(angle0+45-i0H0);
    i0H0++;
    if(i0H0==46){
      i0H0=0;
    }
    delay(actionspeed);
    s2.write(angle2+45-i2H0);
    i2H0++;
    if(i2H0==46){
      i2H0=0;
    }
    delay(actionspeed);
    s4.write(angle4+45-i4H0);
    i4H0++;
    if(i4H0==46){
      i4H0=0;
    }
    delay(actionspeed);
    s6.write(angle6+45-i6H0);
    i6H0++;
    if(i6H0==46){
      i6H0=0;
    }
    delay(actionspeed);
    s8.write(angle8+45-i8H0);
    i8H0++;
    if(i8H0==46){
      i8H0=0;
    }
    delay(actionspeed);
    s10.write(angle10+45-i10H0);
    i10H0++;
    if(i10H0==46){
      i10H0=0;
    }
    delay(actionspeed);
    s1.write(angle1-45-i1H0);
    i1H0++;
    if(i1H0==46){
      i1H0=0;
    }
    delay(actionspeed);
    s3.write(angle3-45-i3H0);
    i3H0++;
    if(i3H0==46){
      i3H0=0;
    }
    delay(actionspeed);
    s5.write(angle5+30-i5H0);
    i5H0++;
    if(i5H0==46){
      i5H0=0;
    }
    delay(actionspeed);
    s7.write(angle7+45+i7H0);
    i7H0++;
    if(i7H0==46){
      i7H0=0;
    }
    delay(actionspeed);
    s9.write(angle9+5+i9H0);
    i9H0++;
    if(i9H0==46){
      i9H0=0;
    }
    delay(actionspeed);
    s11.write(angle11-45+i11H0);
    i11H0++;
    if(i11H0==46){
      i11H0=0;
    }
    delay(actionspeed);
    if(status2>45){
      status2=0;
      break;
    }
    if(softwareSerial1.available()>0){
      break;
    }
    delay(actionspeed);
  }


  while(status3<=45){
    status3++;
    s0.write(angle0-i0H0);
    i0H0++;
    if(i0H0==46){
      i0H0=0;
    }
    delay(actionspeed);
    s2.write(angle2-i2H0);
    i2H0++;
    if(i2H0==46){
      i2H0=0;
    }
    delay(actionspeed);
    s4.write(angle4-i4H0);
    i4H0++;
    if(i4H0==46){
      i4H0=0;
    }
    delay(actionspeed);
    s6.write(angle6-i6H0);
    i6H0++;
    if(i6H0==46){
      i6H0=0;
    }
    delay(actionspeed);
    s8.write(angle8-i8H0);
    i8H0++;
    if(i8H0==46){
      i8H0=0;
    }
    delay(actionspeed);
    s10.write(angle10-i10H0);
    i10H0++;
    if(i10H0==46){
      i10H0=0;
    }
    delay(actionspeed);
    s1.write(0+i1H0);
    i1H0++;
    if(i1H0==46){
      i1H0=0;
    }
    delay(actionspeed);
    s3.write(0+i3H0);
    i3H0++;
    if(i3H0==46){
      i3H0=0;
    }
    delay(actionspeed);
    s5.write(angle5-15+i5H0);
    i5H0++;
    if(i5H0==46){
      i5H0=0;
    }
    delay(actionspeed);
    s7.write(180-i7H0);
    i7H0++;
    if(i7H0==46){
      i7H0=0;
    }
    delay(actionspeed);
    s9.write(angle9+45-i9H0);
    i9H0++;
    if(i9H0==46){
      i9H0=0;
    }
    delay(actionspeed);
    s11.write(angle11-i11H0);
    i11H0++;
    if(i11H0==46){
      i11H0=0;
    }
    delay(actionspeed);
    if(status3>45){
      status3=0;
      break;
    }
    if(Serial.available()>0){
      break;
    }
    delay(actionspeed);
  }

  while(status4<=45){
    status4++;
    s0.write(angle0-45+i0H0);
    i0H0++;
    if(i0H0==46){
      i0H0=0;
    }
    delay(actionspeed);
    s2.write(angle2-45+i2H0);
    i2H0++;
    if(i2H0==46){
      i2H0=0;
    }
    delay(actionspeed);
    s4.write(angle4-45+i4H0);
    i4H0++;
    if(i4H0==46){
      i4H0=0;
    }
    delay(actionspeed);
    s6.write(angle6-45+i6H0);
    i6H0++;
    if(i6H0==46){
      i6H0=0;
    }
    delay(actionspeed);
    s8.write(angle8-45+i8H0);
    i8H0++;
    if(i8H0==46){
      i8H0=0;
    }
    delay(actionspeed);
    s10.write(angle10-45+i10H0);
    i10H0++;
    if(i10H0==46){
      i10H0=0;
    }
    delay(actionspeed);
    s1.write(angle1-45+i1H0);
    i1H0++;
    if(i1H0==46){
      i1H0=0;
    }
    delay(actionspeed);
    s3.write(angle3-45+i3H0);
    i3H0++;
    if(i3H0==46){
      i3H0=0;
    }
    delay(actionspeed);
    s5.write(angle5+30+i5H0);
    i5H0++;
    if(i5H0==46){
      i5H0=0;
    }
    delay(actionspeed);
    s7.write(angle7+45-i7H0);
    i7H0++;
    if(i7H0==46){
      i7H0=0;
    }
    delay(actionspeed);
    s9.write(angle9+5-i9H0);
    i9H0++;
    if(i9H0==46){
      i9H0=0;
    }
    delay(actionspeed);
    s11.write(angle11-45-i11H0);
    i11H0++;
    if(i11H0==46){
      i11H0=0;
    }
    delay(actionspeed);
    if(status4>45){
      status4=0;
      break;
    }
    if(Serial.available()>0){
      break;
    }
    delay(actionspeed);
  }

  while(status5<=45){
    status5++;
    s0.write(angle0+i0H0);
    i0H0++;
    if(i0H0==46){
      i0H0=0;
    }
    delay(actionspeed);
    s2.write(angle2+i2H0);
    i2H0++;
    if(i2H0==46){
      i2H0=0;
    }
    delay(actionspeed);
    s4.write(angle4+i4H0);
    i4H0++;
    if(i4H0==46){
      i4H0=0;
    }
    delay(actionspeed);
    s6.write(angle6+i6H0);
    i6H0++;
    if(i6H0==46){
      i6H0=0;
    }
    delay(actionspeed);
    s8.write(angle8+i8H0);
    i8H0++;
    if(i8H0==46){
      i8H0=0;
    }
    delay(actionspeed);
    s10.write(angle10+i10H0);
    i10H0++;
    if(i10H0==46){
      i10H0=0;
    }
    delay(actionspeed);
    s1.write(angle1-i1H0);
    i1H0++;
    if(i1H0==46){
      i1H0=0;
    }
    delay(actionspeed);
    s3.write(angle3-i3H0);
    i3H0++;
    if(i3H0==46){
      i3H0=0;
    }
    delay(actionspeed);
    s5.write(angle5+75-i5H0);
    i5H0++;
    if(i5H0==46){
      i5H0=0;
    }
    delay(actionspeed);
    s7.write(angle7+i7H0);
    i7H0++;
    if(i7H0==46){
      i7H0=0;
    }
    delay(actionspeed);
    s9.write(angle9-40+i9H0);
    i9H0++;
    if(i9H0==46){
      i9H0=0;
    }
    delay(actionspeed);
    s11.write(0+i11H0);
    i11H0++;
    if(i11H0==46){
      i11H0=0;
    }
    delay(actionspeed);
    if(status5>45){
      status5=0;
      break;
    }
    if(Serial.available()>0){
      break;
    }
    delay(actionspeed);
  }
}




void QUANRUPED::read_mpu_6050_data()
{
	Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
  //  while(Wire.available() < 14);                                        //Wait until all the bytes are received
  delay(1);
  acc_x = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_x variable
  acc_y = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_y variable
  acc_z = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_z variable
  temperature = Wire.read()<<8|Wire.read();                            //Add the low and high byte to the temperature variable
  gyro_x = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_x variable
  gyro_y = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_y variable
  gyro_z = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_z variable
	
}

void QUANRUPED::setup_mpu_6050_registers()
{
	 //Activate the MPU-6050
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x6B);                                                    //Send the requested starting register
  Wire.write(0x00);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1C);                                                    //Send the requested starting register
  Wire.write(0x10);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1B);                                                    //Send the requested starting register
  Wire.write(0x08);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
	
}

void QUANRUPED::self_balanced_setup()
{
	Wire.begin();                                                        //Start I2C as master
  setup_mpu_6050_registers();                                          //Setup the registers of the MPU-6050 (500dfs / +/-8g) and start the gyro
  for (int cal_int = 0; cal_int < 1000 ; cal_int ++){                  //Run this code 2000 times                            
    read_mpu_6050_data();                                              //Read the raw acc and gyro data from the MPU-6050
    gyro_x_cal += gyro_x;                                              //Add the gyro x-axis offset to the gyro_x_cal variable
    gyro_y_cal += gyro_y;                                              //Add the gyro y-axis offset to the gyro_y_cal variable
    gyro_z_cal += gyro_z;                                              //Add the gyro z-axis offset to the gyro_z_cal variable
    delay(3);                                                          //Delay 3us to simulate the 250Hz program loop
  }
  gyro_x_cal /= 1000;                                                  //Divide the gyro_x_cal variable by 2000 to get the avarage offset
  gyro_y_cal /= 1000;                                                  //Divide the gyro_y_cal variable by 2000 to get the avarage offset
  gyro_z_cal /= 1000;                                                  //Divide the gyro_z_cal variable by 2000 to get the avarage offset
  loop_timer = micros();                                               //Reset the loop timer  
}

void QUANRUPED::self_balanced()
{
  read_mpu_6050_data();

  gyro_x -= gyro_x_cal;
  gyro_y -= gyro_y_cal;
  gyro_z -= gyro_z_cal;

  float dt = (micros() - loop_timer) / 1000000.0;
  loop_timer = micros();

  // ===== 陀螺仪积分 =====
  angle_pitch += gyro_x * dt * 0.0611;
  angle_roll  += gyro_y * dt * 0.0611;

  // ===== 加速度 =====
  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));

  if(abs(acc_y) < acc_total_vector){
    angle_pitch_acc = asin((float)acc_y/acc_total_vector)*57.296;
  }
  if(abs(acc_x) < acc_total_vector){
    angle_roll_acc  = asin((float)acc_x/acc_total_vector)*-57.296;
  }

  // ===== 互补滤波 =====
  angle_pitch = angle_pitch * 0.98 + angle_pitch_acc * 0.02;
  angle_roll  = angle_roll  * 0.98 + angle_roll_acc  * 0.02;

  // ===== 输出平滑 =====
  angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1;
  angle_roll_output  = angle_roll_output  * 0.9 + angle_roll  * 0.1;
}

void QUANRUPED::self_balanced_test()
{
  // ===== 参数（可以调）=====
  const float KP_PITCH = 2.2;
  const float KI_PITCH = 0.02;
  const float KD_PITCH = 0.6;

  const float KP_ROLL  = 2.0;
  const float KI_ROLL  = 0.02;
  const float KD_ROLL  = 0.6;

  const float DEADZONE = 1.0;
  const float MAX_COMP = 20.0;

  // ===== PID状态（必须static）=====
  static float pitchIntegral = 0;
  static float rollIntegral  = 0;

  static float lastPitch = 0;
  static float lastRoll  = 0;

  static float dPitchFiltered = 0;
  static float dRollFiltered  = 0;

  // ===== 当前误差 =====
  float pitch = angle_pitch_output;
  float roll  = angle_roll_output;

  // ===== 死区（防抖）=====
  if (abs(pitch) < DEADZONE) pitch = 0;
  if (abs(roll)  < DEADZONE) roll  = 0;

  // ===== 积分（防风up）=====
  if (abs(pitch) < 20) pitchIntegral += pitch;
  if (abs(roll)  < 20) rollIntegral  += roll;

  pitchIntegral = constrain(pitchIntegral, -100, 100);
  rollIntegral  = constrain(rollIntegral,  -100, 100);

  // ===== 微分（带低通滤波，防抖关键）=====
  float dPitch = pitch - lastPitch;
  float dRoll  = roll  - lastRoll;

  // 一阶低通滤波（非常关键！）
  dPitchFiltered = dPitchFiltered * 0.7 + dPitch * 0.3;
  dRollFiltered  = dRollFiltered  * 0.7 + dRoll  * 0.3;

  lastPitch = pitch;
  lastRoll  = roll;

  // ===== PID输出 =====
  float pitchComp =
      KP_PITCH * pitch +
      KI_PITCH * pitchIntegral +
      KD_PITCH * dPitchFiltered;

  float rollComp =
      KP_ROLL * roll +
      KI_ROLL * rollIntegral +
      KD_ROLL * dRollFiltered;

  // ===== 限幅 =====
  pitchComp = constrain(pitchComp, -MAX_COMP, MAX_COMP);
  rollComp  = constrain(rollComp,  -MAX_COMP, MAX_COMP);

  // ===== 六足姿态补偿 =====
  // 左右分组（pitch）
  // 前中后（roll权重不同）

  // 左侧
  s0.write(angle0 - pitchComp - rollComp * 0.3);   // 左前
  s2.write(angle2 - pitchComp - rollComp * 1.0);   // 左中
  s4.write(angle4 - pitchComp - rollComp * 0.7);   // 左后

  // 右侧
  s6.write(angle6 + pitchComp - rollComp * 0.3);   // 右前
  s8.write(angle8 + pitchComp - rollComp * 1.0);   // 右中
  s10.write(angle10 + pitchComp - rollComp * 0.7); // 右后
}

void QUANRUPED::attack(){
  Serial.println("attack");

  if(is_steaty_on()){
    steaty_off();
  }
  
  ultrasonic();
  if(a<=15 && a>0){
    s0.write(10);
    s1.write(90); //45
    s3.write(135);//90
    s2.write(90); //10
    s4.write(170);
    s5.write(45); //120
    s6.write(170);//180
    s7.write(90); //90
    s8.write(90);
    s9.write(45); //95
    s11.write(135);//0 
    s10.write(10);   //180

    while(status4<=30){
      delay(10);
      status4++;
      s12.write(angle12+i2H4);
      i2H4++;
      if(i2H4==31){
        i2H4=0;
      }
      if(status4>30){
        status4=0;
        break;
      }
      if(Serial.available()>0){
        break;
      }
    }

    while(status4<=30){
      delay(10);
      status4++;
      s12.write(angle12+30-i2H4);
      i2H4++;
      if(i2H4==31){
        i2H4=0;
      }
      if(status4>30){
        status4=0;
        break;
      }
      if(Serial.available()>0){
        break;
      }
    }

    while(status4<=30){
      delay(10);
      status4++;
      s12.write(angle12-i2H4);
      i2H4++;
      if(i2H4==31){
        i2H4=0;
      }
      if(status4>30){
        status4=0;
        break;
      }
      if(Serial.available()>0){
        break;
      }
    }

    while(status4<=30){
      delay(10);
      status4++;
      s12.write(angle12-30+i2H4);
      i2H4++;
      if(i2H4==31){
        i2H4=0;
      }
      if(status4>30){
        status4=0;
        break;
      }
      if(Serial.available()>0){
        break;
      }
    }
  }
  else if(a>15){
    while(a>15){
      ultrasonic();
      original_latest();
      if(Serial.available()>0){
        break;
      }
    }
  }
  
}



void QUANRUPED::steaty()
{
  steaty_on = true;
  
  Serial.println("steaty()");

  self_balanced();

  s1.write(angle1);
  s3.write(angle3);
  s5.write(angle5);
  s7.write(angle7);
  s9.write(angle9);
  s11.write(angle11);

  self_balanced_test();
}


void QUANRUPED::automatic()
{
  if(is_steaty_on()){
    steaty_off();
  }
  
  Serial.println("automatic()");

  self_balanced();

  s1.write(angle1);
  s3.write(angle3);
  s5.write(angle5);
  s7.write(angle7);
  s9.write(angle9);
  s11.write(angle11);

  self_balanced_test();
}

void QUANRUPED::sendultrasonic(){
  s12.write(angle);
  angle++;
  if(angle%3 == 0){
    ultrasonic();
    Serial.print("AT+CIPSEND=0,3\r\n");
    delay(20);
    Serial.println(a);
    delay(250);
  }
  if(angle==124){
    angle=20;
  }
}



void QUANRUPED::pushup(){
  Serial.println("pushup");

  if(is_steaty_on()){
    steaty_off();
  }

}
