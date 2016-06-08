#include <Wire.h>
#include "SHT1x.h"

typedef struct
{
    SHT1x cRH;
    int iValvePin;
} Bed;

#define MSECS_PER_MINUTE 60ul * 1000ul
#define MSECS_PER_HOUR 60ul * MSECS_PER_MINUTE

#define NUM_BEDS 3
#define RH_CLK_PIN 6

const unsigned long lWaterIntervalMsecs = 12ul * MSECS_PER_HOUR;
const unsigned long lValveOpenIntervalMsecs = 10ul * MSECS_PER_MINUTE;
const float fRHThreshold = 60.0f;

Bed pBeds[NUM_BEDS];

/* Prototypes */
float get_humidity( Bed* );
int operate_valve( Bed* );
void transmit_data();
void initialize_beds();

void setup()
{
    initialize_beds();
}


void loop()
{
    int iBed = 0;
    for( ; iBed < NUM_BEDS; ++iBed )
    {
        Bed* pCurBed = pBeds + iBed;
        if( get_humidity( pCurBed ) < fRHThreshold )
        {
            operate_valve( pCurBed );
        }
    }
    transmit_data();

    delay( lWaterIntervalMsecs );
}


/* Gets the current soil moisture in a garden "Bed" */
float get_humidity( Bed* pBed )
{
    return pBed->cRH.readHumidity();
}


/* Opens the soaker hose valve for a garden "Bed" */
int operate_valve( Bed* pBed )
{
    digitalWrite( pBed->iValvePin, HIGH );
    delay( lValveOpenIntervalMsecs );
    digitalWrite( pBed->iValvePin, LOW );

    return 0;
}


/* Transmits data back to VS */
void transmit_data()
{
}


/* Sets up our awkward array of garden "Beds" */
void initialize_beds()
{
    const int piRHDataPins[NUM_BEDS] = { 8, 9, 10 };
    const int piValvePins[NUM_BEDS]  = { 3, 4,  5 };

    int i = 0;
    for( ; i < NUM_BEDS; ++i )
    {
        pBeds[i].cRH.setPins( piRHDataPins[i],
                              RH_CLK_PIN );

        pinMode( piValvePins[i], OUTPUT );
        pBeds[i].iValvePin = piValvePins[i];
    }
}

