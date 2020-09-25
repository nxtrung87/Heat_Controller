#include "ESP32_AutoConnect_Aux.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------
AutoConnectInput clientIdInput("clientId", "", "MQTT Client ID", "", "");
AutoConnectSubmit saveButton("saveButton", "Save", "/mqtt_setting");

AutoConnectAux mqtt_setting("/mqtt_settings", "MQTT Settings", true, {clientIdInput, saveButton});
// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------

AutoConnectAux& Aux_getReference()
{
    return mqtt_setting;
}