#define LATCH 4
#define CLK 3
#define DATA 2

//This is the hex value of each number stored in an array by index num
//byte digitOne[10]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};   //common anode display
//byte digitTwo[10]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};   //common anode display

byte digitOne[10]= {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};    //common cathode display or VFD tube
byte digitTwo[10]= {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};    //common cathode display or VFD tube

int avg;    //final average number to output to display
int avg1;   //averaging data recived makes the output reading more responsive
int avg2;   //and more like a task manager reading
int avg3;
int avg4;
int avg5;

void setup()
{
  pinMode(LATCH, OUTPUT);   //shift register outputs enable/disable
  pinMode(CLK, OUTPUT);     //shift register clock pulse between data pulses
  pinMode(DATA, OUTPUT);    //shift register data stream
  Serial.begin(19200);      //init serial interface
}

void serial_parse()               //function to sample serial data, then generate an average value
{
  if (Serial.available());
  
      avg1=Serial.parseInt();
      delay(100);                  //delays to take samples over a period of time
      avg2=Serial.parseInt();
      delay(100);
      avg3=Serial.parseInt();
      delay(100);
      avg4=Serial.parseInt();
      delay(100);
      avg5=Serial.parseInt();

      avg=((avg1 + avg2 + avg3 + avg4 + avg5)/5);    //averaging 
}

void send_out()
{                                   //process data to seperate number into two sepereate digits
  unsigned char tens = (avg/10);    //unsigned char drops any remainders - divide vallue by 10 and drop decimal
  unsigned char ones = (avg%10);    //i dont understand the % sign - think it drops the MSD

      // shift out data to shift registers
      digitalWrite(LATCH, LOW);                       // shift reg output lines off
      shiftOut(DATA, CLK, MSBFIRST, ~digitTwo[tens]); // digitTwo - left digit data
      shiftOut(DATA, CLK, MSBFIRST, ~digitOne[ones]); // digitOne - right digit data
      digitalWrite(LATCH, HIGH);                      // shift reg output lines on
}

void loop()
{
  serial_parse();   //fetch variables from serial connection
  send_out();       //send out processed data to the display
  delay(2);         //stability delay
}
