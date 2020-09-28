#include "ESP32_AutoConnect_Aux.h"

AutoConnectInput clientIdInput("clientId", "", "MQTT Client ID", "", "");
AutoConnectSubmit saveButton("save", "Save", "/mqtt_settings");
AutoConnectText currentClientIdText("currentId", "", "color:red", "");

AutoConnectAux mqttAux("/mqtt_settings", "MQTT Settings", true, 
                    {clientIdInput, saveButton, currentClientIdText});

AutoConnectAux& Aux_getReference()
{
    return mqttAux;
}
