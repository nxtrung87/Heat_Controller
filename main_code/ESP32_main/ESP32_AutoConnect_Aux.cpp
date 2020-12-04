#include "ESP32_AutoConnect_Aux.h"

AutoConnectInput clientIdInput("clientId", "", "MQTT Client ID", "", "");
AutoConnectSubmit saveButton("save", "Save", "/mqtt_settings");
AutoConnectText currentClientIdText("currentId", "", "color:red", "");
AutoConnectText softwareVersionText("version", "", "color:red", "");

AutoConnectAux versionAux("/version", "Software Version", true, 
                    {softwareVersionText});
AutoConnectAux mqttAux("/mqtt_settings", "MQTT Settings", true, 
                    {clientIdInput, saveButton, currentClientIdText});

AutoConnectAux& Aux_getReference()
{
    return mqttAux;
}
