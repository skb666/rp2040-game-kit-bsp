#ifndef IR_BSP_H
#define IR_BSP_H

#include <Arduino.h>
#if !defined(RAW_BUFFER_LENGTH)
#define RAW_BUFFER_LENGTH  750  // 750 is the value for air condition remotes.
#endif
#if !defined(RECORD_GAP_MICROS)
#define RECORD_GAP_MICROS  20000
#endif
#if !defined(INFO)
#define INFO // To see valuable informations from universal decoder for pulse width or pulse distance protocols
#endif
#include "PinDefinitionsAndMore.h"
#include "IRremoteInt.h"

// Storage for the recorded code
typedef struct {
    IRData receivedIRData;
    // extensions for sendRaw
    uint8_t rawCode[RAW_BUFFER_LENGTH];   // The durations if raw
    uint16_t rawCodeLength; // The length of the code
} storedIRDataStruct;

void storeCode(IRData *aIRReceivedData);
void sendCode(storedIRDataStruct *aIRDataToSend);

extern storedIRDataStruct sStoredIRData;

#endif
