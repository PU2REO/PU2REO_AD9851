#include <PU2REO_AD9851.h>

const int AD9851_PIN_W_CLK = 8;
const int AD9851_PIN_FQ_UD = 9;
const int AD9851_PIN_DATA = 10;
const int AD9851_PIN_RESET = 11;

PU2REO_AD9851   AD9851(AD9851_PIN_W_CLK, AD9851_PIN_FQ_UD, AD9851_PIN_DATA, AD9851_PIN_RESET);  // AD9851 device creation

long value;
int phase = 0; // Remember: each increment means 11.25 degrees. Refer to AD9051 Datasheet for more information

void setup()
{
  // Initializes AD9851
  AD9851.Init();

  // initializes serial
  Serial.begin(115200);
}

void loop(){

  String str;

  // Message:
  Serial.println("Input frequency in [Hz]:");
  while(!Serial.available());

  // read frequency from serial port
  str = Serial.readString();

  // convert
  value = str.toInt(); 
  Serial.print("Frequency set to: ");
  Serial.print(value);
  Serial.println(" [Hz]");
  Serial.println("");
  

  // set frequency
  AD9851.SetFrequency(value, phase);  
}