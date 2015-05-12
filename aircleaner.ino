#define IRLEDpin  D2

// IR Codes in (ADDR1 | ADDR2 | COMMAND1 | COMMAND2) format?
unsigned long IRCODE_OFF    = 0b01010101000001000000000000000100;
unsigned long IRCODE_LOW    = 0b01010101000001110000001100000100;
unsigned long IRCODE_MEDIUM = 0b01010101000001100000001100000101;
unsigned long IRCODE_HIGH   = 0b01010101000001010000001100000110;

// This routine runs only once upon reset
void setup() {
  pinMode(IRLEDpin, OUTPUT);
  Spark.function("acfanspeed", setFanSpeed);
}

void IRcarrier(unsigned int IRTime)
{
  for(unsigned int i = 0; i < (IRTime / 26); i++)
  {
    digitalWrite(IRLEDpin, HIGH);
    delayMicroseconds(11);
    digitalWrite(IRLEDpin, LOW);
    delayMicroseconds(11);
  }
}

void IRsendCode(unsigned long code)
{
  for (int i = 0; i < 32; i++)
  {
    if (code & 0x80000000) {
      IRcarrier(1300);
    } else {
      IRcarrier(620);
    }

    code<<=1; 
    delayMicroseconds(1200);
  }
}

int setFanSpeed(String speed)
{
  if (speed == "OFF") {
    IRsendCode(IRCODE_OFF);
  } else if (speed == "LOW") {
    IRsendCode(IRCODE_LOW);
  } else if (speed == "MEDIUM") {
    IRsendCode(IRCODE_MEDIUM);
  } else if (speed == "HIGH") {
    IRsendCode(IRCODE_HIGH);
  } else {
    // ignore
    return -1;
  }
  
  return 0;
}

void loop() {

}
