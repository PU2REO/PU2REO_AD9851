//------------------------------------------------------------------------------
// Programmer...: PU2REO
//
// Description..: Arduino Library for AD9851 DDS module
//
// History......: v1.0.0 - 10/01/2024: Initial version
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files
//------------------------------------------------------------------------------
#include "arduino.h"
#include "PU2REO_AD9851.h"
// #include "debug.h"

//------------------------------------------------------------------------------
// Procedure:    PU2REO_AD9851::PU2REO_AD9851
// Description:  Adjust initial parameters for AD9851
// Paramaters:   None
// Output:       None
//------------------------------------------------------------------------------
PU2REO_AD9851::PU2REO_AD9851(int W_CLK, int FQ_UD, int DATA, int RESET)
{
	// assing pins
	AD9851Pins.FQ_UD_PIN = FQ_UD;
	AD9851Pins.W_CLK_PIN = W_CLK;
	AD9851Pins.DATA_PIN	 = DATA; 
	AD9851Pins.RESET_PIN = RESET;
	
	// set pins mode
    pinMode(AD9851Pins.FQ_UD_PIN, OUTPUT);                         
    pinMode(AD9851Pins.W_CLK_PIN, OUTPUT);                         
    pinMode(AD9851Pins.DATA_PIN,  OUTPUT);                         
    pinMode(AD9851Pins.RESET_PIN, OUTPUT);                         	
}

//------------------------------------------------------------------------------
// Procedure:    PU2REO_AD9851::Init
// Description:  Resets and adjusts AD9851 for serial loading
// Paramaters:   None
// Output:       None
//------------------------------------------------------------------------------
void PU2REO_AD9851::Init(void)
{ 
    // reset DDS logic
	this->Pulse(AD9851Pins.RESET_PIN);
  
    // serial load enable sequence
    // note: for device start-up in serial mode, hardwire pin 2 at 0, pin 3 at 1, and pin 4 at 1
    this->Pulse(AD9851Pins.W_CLK_PIN);
    this->Pulse(AD9851Pins.FQ_UD_PIN);

    // set initial frequency
    this->SetFrequency(INI_AD9851_FREQ, INI_AD9851_PHASE);
}

//------------------------------------------------------------------------------
// Procedure:    PU2REO_AD9851::SetFrequency
// Description:  Calculates control word and send it to the AD9851 unit
// Paramaters:   Frequency in Hertz (long), phase(uint8_t)
// Output:       None
//------------------------------------------------------------------------------
void PU2REO_AD9851::SetFrequency(double freq, uint8_t phase)
{
    // -----------------------------------------------------------------------------------------------------------------------------
    // Word | Data[7]        | Data[6]  | Data[5]  | Data[4]  | Data[3]        | Data[2]    | Data[1]   | Data[0]
    // -----------------------------------------------------------------------------------------------------------------------------
    // W0   | Phase–b4 (MSB) | Phase–b3 | Phase–b2 | Phase–b1 | Phase–b0 (LSB) | Power-Down | Log ic 0* | 6xREFCLK Multiplier Enable
    // W1   | Freq–b31 (MSB) | Freq–b30 | Freq–b29 | Freq–b28 | Freq–b27       | Freq–b26   | Freq–b25  | Freq–b24
    // W2   | Freq–b23       | Freq–b22 | Freq–b21 | Freq–b20 | Freq–b19       | Freq–b18   | Freq–b17  | Freq–b16
    // W3   | Freq–b15       | Freq–b14 | Freq–b13 | Freq–b12 | Freq–b11       | Freq–b10   | Freq–b9   | Freq–b8
    // W4   | Freq–b7        | Freq–b6  | Freq–b5  | Freq–b4  | Freq–b3        | Freq–b2    | Freq–b1   | Freq–b0 (LSB)

    uint8_t Word_W0;             // store contents of W0;

    // calculate control word
	AD9851Ctr.ControlWord = (uint32_t)(freq * (pow(2,32) / 180e+6));

    // calculate first word - Phase + control bits
    Word_W0 = (phase << 3) | 0b001;

	// now we itterate through the first 32 bits, 8 at a time, streaming to the DataPin.
    for (int i=0; i<4; i++, AD9851Ctr.ControlWord>>=8) 
	{
		// stream out bits to DataPin, pulsing clock pin
		shiftOut(AD9851Pins.DATA_PIN, AD9851Pins.W_CLK_PIN, LSBFIRST, (AD9851Ctr.ControlWord & 0xFF));
    }
	
	// now send the final 8 bits to complete the 40 bit instruction
    shiftOut(AD9851Pins.DATA_PIN, AD9851Pins.W_CLK_PIN, LSBFIRST, Word_W0 & 0xFF);

    // and once all 40 bits have been sent
    // finally we toggle the load bit to say we are done
    // and let the AD9851 do its stuff
    this->Pulse(AD9851Pins.FQ_UD_PIN);
    return;
}

//------------------------------------------------------------------------------
// Procedure:    PU2REO_AD9851::Pulse
// Description:  Pulse High/Low a given pin
// Paramaters:   Pin Number (int)
// Output:       None
//------------------------------------------------------------------------------
void PU2REO_AD9851::Pulse(int pin) 
{
	// put pin High
	digitalWrite(pin, LEVEL_HIGH);
	digitalWrite(pin, LEVEL_LOW);
}
