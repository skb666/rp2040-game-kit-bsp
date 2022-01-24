#include "bsp/ir_bsp.h"

storedIRDataStruct sStoredIRData;

// Stores the code for later playback in sStoredIRData
// Most of this code is just logging
void storeCode(IRData *aIRReceivedData) {
  if (aIRReceivedData->flags & IRDATA_FLAGS_IS_REPEAT) {
    Serial.println(F("Ignore repeat"));
    return;
  }
  if (aIRReceivedData->flags & IRDATA_FLAGS_IS_AUTO_REPEAT) {
    Serial.println(F("Ignore autorepeat"));
    return;
  }
  if (aIRReceivedData->flags & IRDATA_FLAGS_PARITY_FAILED) {
    Serial.println(F("Ignore parity error"));
    return;
  }
  /*
    * Copy decoded data
    */
  sStoredIRData.receivedIRData = *aIRReceivedData;

  if (sStoredIRData.receivedIRData.protocol == UNKNOWN) {
    Serial.print(F("Received unknown code and store "));
    Serial.print(IrReceiver.decodedIRData.rawDataPtr->rawlen - 1);
    Serial.println(F(" timing entries as raw "));
    IrReceiver.printIRResultRawFormatted(&Serial, true); // Output the results in RAW format
    sStoredIRData.rawCodeLength = IrReceiver.decodedIRData.rawDataPtr->rawlen - 1;
    /*
      * Store the current raw data in a dedicated array for later usage
      */
    IrReceiver.compensateAndStoreIRResultInArray(sStoredIRData.rawCode);
  } else {
    IrReceiver.printIRResultShort(&Serial);
    sStoredIRData.receivedIRData.flags = 0; // clear flags -esp. repeat- for later sending
    Serial.println();
  }
}

void sendCode(storedIRDataStruct *aIRDataToSend) {
  if (aIRDataToSend->receivedIRData.protocol == UNKNOWN /* i.e. raw */) {
    // Assume 38 KHz
    IrSender.sendRaw(aIRDataToSend->rawCode, aIRDataToSend->rawCodeLength, 38);

    Serial.print(F("Sent raw "));
    Serial.print(aIRDataToSend->rawCodeLength);
    Serial.println(F(" marks or spaces"));
  } else {
    /*
    * Use the write function, which does the switch for different protocols
    */
    IrSender.write(&aIRDataToSend->receivedIRData, NO_REPEATS);

    Serial.print(F("Sent: "));
    printIRResultShort(&Serial, &aIRDataToSend->receivedIRData);
  }
}


