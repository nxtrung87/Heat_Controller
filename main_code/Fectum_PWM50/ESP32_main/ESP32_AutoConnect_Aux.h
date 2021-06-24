#ifndef ESP32_AUTOCONNECT_AUX
#define ESP32_AUTOCONNECT_AUX

#include "AutoConnect.h"

/**
 Return a reference to the MQTT Settings Aux page.
 **/
AutoConnectAux& Aux_getMqttSettingsReference();

/**
 Return a reference to the Software Version Aux page.
 **/
AutoConnectAux& Aux_getVersionReference();

/**
 Update the software version value.
 \param[in] newVersion  String containing the new software version text. 
 **/
void Aux_updateSoftwareVersionText(String newVersion);

#endif /* ESP32_AUTOCONNECT_AUX */
