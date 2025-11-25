int time = 10;    //delay time 
int cpu;

int avg;
int avg1;
int avg2;
int avg3;
int avg4;
int avg5;

int pinA  = 2;
int pinB  = 3;
int pinC  = 4;
int pinD  = 5;
int pinE  = 6;
int pinF  = 7;
int pinG  = 8;
//int pinDP = 13;

int DIG1  = 11;
int DIG2  = 12;

void choose_digit(char num){
  switch(num) {
    default:
       //set segments to 0
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
//      digitalWrite(pinDP,HIGH);
      break;

    case 1:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
//      digitalWrite(pinDP,HIGH);
      break;
      
    case 2:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
//      digitalWrite(pinDP,HIGH);
      break;
    
    case 3:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
//      digitalWrite(pinDP,HIGH);
      break;

    case 4:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
//      digitalWrite(pinDP,HIGH);
      break;

    case 5:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
//      digitalWrite(pinDP,HIGH);
      break;

    case 6:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
//      digitalWrite(pinDP,HIGH);
      break;

    case 7:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
//      digitalWrite(pinDP,HIGH);
      break;

    case 8:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
 //     digitalWrite(pinDP,HIGH);
      break;

    case 9:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
 //     digitalWrite(pinDP,HIGH);
      break;
  }
}

void setup() {
  // put your setup code here, to run once:

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(DIG1, OUTPUT);
  pinMode(DIG2, OUTPUT);

  Serial.begin(19200);

}

void pick_digit(int digit)
{
  digitalWrite(DIG1, LOW);
  digitalWrite(DIG2, LOW);

  switch(digit)
  {
    case 1: digitalWrite(DIG1, HIGH);
    break;
    case 2: digitalWrite(DIG2, HIGH);
    break;
    default:digitalWrite(DIG2, LOW);
  }
  
}

void seven_segment(int number)
{ 
  unsigned char tens = int (number/10);
  unsigned char ones = int (number%10);
  int i = 1;

  while (i < 20)
       
  {
      
  choose_digit(tens);
  pick_digit(1);
  delay(time);

  choose_digit(ones);
  pick_digit(2);
  delay(time);  

  i++;
  }
      average(avg);
  
}
void average(int number)
{

if (Serial.available()) cpu=avg;
  
      avg1=Serial.parseInt();
      delay(10);
      avg2=Serial.parseInt();
      delay(10);
      avg3=Serial.parseInt();
      delay(10);
      avg4=Serial.parseInt();
      delay(10);
      avg5=Serial.parseInt();

      avg=((avg1 + avg2 + avg3 + avg4 + avg5)/5);
      
}

void loop() {
  // put your main code here, to run repeatedly:

  seven_segment(cpu);
  delay(2);

}
