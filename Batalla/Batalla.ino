// - Pines Controlador - //
  const int pinPWMA = 9;
  const int pinAIN2 = 7;
  const int pinAIN1 = 8;
  
  const int pinBIN1 = 4;
  const int pinBIN2 = 10;
  const int pinPWMB = 11;
  
  const int pinSTBY = 12; // Pin StandBy
 
const int waitTime = 2000;   //espera entre fases
const int speed = 200;      //velocidad de giro
 
const int pinMotorA[3] = { pinPWMA, pinAIN2, pinAIN1 };
const int pinMotorB[3] = { pinPWMB, pinBIN1, pinBIN2 };

// -- Pines Radio -- //
  byte PWM_MOTA = 3;
  byte PWM_MOTB = 5;
  byte PWM_AUX = 6;

  int pwm_valueMOTA = 0 ;
  int pwm_valueMOTB = 0 ;
  int pwm_valueAUX;
 
enum moveDirection {
   forward,
   backward
};
 
enum turnDirection {
   clockwise,
   counterClockwise
};
 
void setup()
{
   pinMode(pinAIN2, OUTPUT);
   pinMode(pinAIN1, OUTPUT);
   pinMode(pinPWMA, OUTPUT);
   pinMode(pinBIN1, OUTPUT);
   pinMode(pinBIN2, OUTPUT);
   pinMode(pinPWMB, OUTPUT);

   Serial.begin(250000);
}
 
void loop()
{
   
   enableMotors();
   
   pwm_valueMOTA = pulseIn(PWM_MOTA, HIGH);
   pwm_valueMOTB = pulseIn(PWM_MOTB, HIGH);
   pwm_valueAUX = pulseIn(PWM_AUX, HIGH);

  
   pwm_valueMOTA = map (pwm_valueMOTA, 1000, 2000, -255 , 255);
   pwm_valueMOTB = map (pwm_valueMOTB, 1000, 2000, -255 , 255);

  if(pwm_valueMOTA > 255)
    {
    pwm_valueMOTA = 255;
    }
  
  if(pwm_valueMOTA < -255)
    {
    pwm_valueMOTA = -255;
    }  
  
  if(pwm_valueMOTB > 255)
    {
    pwm_valueMOTB = 255;
    }
  
  if(pwm_valueMOTB < -255)
    {
    pwm_valueMOTB = -255;
    }  
  
   if(pwm_valueMOTA > 0 )
    { 
    moveMotorForward(pinMotorA, pwm_valueMOTA);
   }else
    {
    moveMotorBackward(pinMotorA, -pwm_valueMOTA);
    }

   if(pwm_valueMOTB > 0 )
    { 
    moveMotorForward(pinMotorB, pwm_valueMOTB);
   }else
    {
    moveMotorBackward(pinMotorB, -pwm_valueMOTB);
    }

   //Serial.print(pwm_valueMOTA);
   //Serial.print(",");
   //Serial.print(pwm_valueMOTB);
   //Serial.println("");
}
 
//Funciones que controlan el vehiculo
void move(int direction, int speed)
{
   if (direction == forward)
   {
      moveMotorForward(pinMotorA, speed);
      moveMotorForward(pinMotorB, speed);
   }
   else
   {
      moveMotorBackward(pinMotorA, speed);
      moveMotorBackward(pinMotorB, speed);
   }
}
 
void turn(int direction, int speed)
{
   if (direction == forward)
   {
      moveMotorForward(pinMotorA, speed);
      moveMotorBackward(pinMotorB, speed);
   }
   else
   {
      moveMotorBackward(pinMotorA, speed);
      moveMotorForward(pinMotorB, speed);
   }
}
 
void fullStop()
{
   disableMotors();
   stopMotor(pinMotorA);
   stopMotor(pinMotorB);
}
 
//Funciones que controlan los motores
void moveMotorForward(const int pinMotor[3], int speed)
{
   digitalWrite(pinMotor[1], HIGH);
   digitalWrite(pinMotor[2], LOW);
 
   analogWrite(pinMotor[0], speed);
}
 
void moveMotorBackward(const int pinMotor[3], int speed)
{
   digitalWrite(pinMotor[1], LOW);
   digitalWrite(pinMotor[2], HIGH);
 
   analogWrite(pinMotor[0], speed);
}
 
void stopMotor(const int pinMotor[3])
{
   digitalWrite(pinMotor[1], LOW);
   digitalWrite(pinMotor[2], LOW);
 
   analogWrite(pinMotor[0], 0);
}
 
void enableMotors()
{
   digitalWrite(pinSTBY, HIGH);
}
 
void disableMotors()
{
   digitalWrite(pinSTBY, LOW);
}
