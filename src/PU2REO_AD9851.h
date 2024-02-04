//////////////////////////////
// Include files
//////////////////////////////
#include "arduino.h"

//////////////////////////////
// general definitions
//////////////////////////////
#define LEVEL_LOW                                0
#define LEVEL_HIGH                               1

// band frequencies
#define MIN_AD9851_FREQ                          1L         // Hz
#define MAX_AD9851_FREQ                          75000000L  // Hz
#define INI_AD9851_FREQ                          1000L      // Hz

// phase definitions
#define MIN_AD9851_PHASE                         0          // * 11.25 degrees
#define MAX_AD9851_PHASE                         31         // * 11.25 degrees
#define INI_AD9851_PHASE                         0          // 0-31 - to multiply 11.25 degrees

//////////////////////////////
// structures
//////////////////////////////
typedef struct
{
    int    			FQ_UD_PIN;
    int     		W_CLK_PIN;
    int     		DATA_PIN; 
    int      		RESET_PIN;
} AD9851_Pins;

typedef struct
{
    uint32_t   		ControlWord;                                              // Current control word
    int8_t      	Phase;                                                    // Current Phase of senoidal wave
} AD9851_st;

//////////////////////////////
// main class
//////////////////////////////
class PU2REO_AD9851
{
//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
public:
	PU2REO_AD9851(int W_CLK, int FQ_UD, int DATA, int RESET);
	void      	Init(void);
	void 		SetFrequency(double freq, uint8_t phase);
private:
	void 		Pulse(int pin);  
//------------------------------------------------------------------------------
// global variables
//------------------------------------------------------------------------------
	AD9851_Pins		AD9851Pins;
	AD9851_st		AD9851Ctr;
};
