#define DIFF_D 5 // différence de PWM entre droite et gauche
#define DIFF_G -1// différence de PWM entre gauche et droite

// Variables de la carte driver
int PWM_1 = 10;
int SENS_1 = 8;
int PWM_2 = 9;
int SENS_2 = 7;
int LED = 13;
int time = 1000;

// Variables du capteur ultrasonic
const int TrigPin = 3;
const int EchoPin = 4;

// Variables simple choisi par nous.
float duration;
float distance;
int maxSpeed = 90;
int reset = 0;
int temp = 500;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin (9600);
  pinMode (TrigPin, OUTPUT);
  pinMode (EchoPin, INPUT);
  
  pinMode (LED, OUTPUT);
  pinMode(PWM_1, OUTPUT);
  pinMode(SENS_1,OUTPUT);
  
  pinMode(PWM_2, OUTPUT);
  pinMode(SENS_2,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(TrigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  duration = pulseIn(EchoPin, HIGH);
  distance = (duration * 0.0360) / 2;

 // Serial.print(distance);
 // Serial.print(" cm");
 // Serial.print(" \n");
  Com_Mot_Gauche(maxSpeed);
  Com_Mot_Droite(maxSpeed);

  if (distance > 10 && reset > 0 && distance < 20)
  {
  Com_Mot_Gauche(-maxSpeed);
  Com_Mot_Droite(maxSpeed);
  delay(temp);
  }
  
  if (distance < 10 && reset > 0)
  {
  Com_Mot_Gauche(-maxSpeed);
  Com_Mot_Droite(-maxSpeed);
  delay(temp);
  Com_Mot_Gauche(-maxSpeed);
  Com_Mot_Droite(maxSpeed);
  delay(temp);
  }
  

  reset = 1;
}



void Com_Mot_Gauche(int PWM)

{

  if (PWM >= 0)
  {
    digitalWrite(SENS_2, HIGH);
  }

  if (PWM < 0)
  {
    digitalWrite(SENS_2, LOW);
    PWM = -PWM;
  }
  if (PWM != 0)
  {
    PWM = PWM - DIFF_G;
    if (PWM > 255) PWM = 255;
    if (PWM < -255) PWM = -255;
  }
  analogWrite(PWM_2, PWM);
}

void Com_Mot_Droite(int PWM)

{

  if (PWM >= 0)
  {
    digitalWrite(SENS_1, HIGH);
  }

  if (PWM < 0)
  {
    digitalWrite(SENS_1, LOW);
    PWM = -PWM;
  }
  if (PWM != 0)
  {
    PWM = PWM - DIFF_D;
    if (PWM > 255) PWM = 255;
    if (PWM < -255) PWM = -255;
  }
  analogWrite(PWM_1, PWM);
}
