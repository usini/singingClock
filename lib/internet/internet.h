
// WiFi
#include <WiFi.h>
extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

// MQTT
#include <AsyncMqttClient.h>

// NTP Management
#include <Preferences.h>
#include <ezTime.h>

// WiFi Settings
String wifiSSID = "";
String wifiPassword = "";

// NTP Settings
Timezone myTz;

bool connected = false;
bool wifiChange = false;
bool redrawInProgress = false;
bool mqttConnected = false;
bool wifiCredentialsNeededSave = false;

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

IPAddress mqtt_host = IPAddress(0, 0, 0, 0);
int mqtt_port = 1883;
const char *mqttUsername = "";
const char *mqttPassword = "";

bool buttonState[3] = {false, false, false};
bool buttonRedrawNeeded[3] = {false, false, false};

void connectToMqtt();

void WiFiTask(void *pvParameters)
{
    while (true)
    {
        if (connected)
        {
            events();
        }
        if (wifiChange)
        {
            connected = false;
            wifiChange = false;
            Serial.println("[📶 WIFI] 👋🏷️ SSID changed");
            wifiCredentialsNeededSave = true;
            WiFi.disconnect();
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void saveWifiCredentialsToFlash()
{
    File LittleFS_File = LittleFS.open("/wifi.txt", FILE_WRITE);
    LittleFS_File.println(wifiSSID);
    LittleFS_File.println(wifiPassword);
    LittleFS_File.close();
    Serial.println("[💾 FLASH] 📶 WiFi Credentials saved to flash");
}

void WiFiEvent(WiFiEvent_t event)
{
    Serial.printf("[📶 WIFI] event: %d\n", event);
    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("[📶 WIFI] 🟢 OK");
        Serial.print("[📶 WIFI] IP: ");
        Serial.println(WiFi.localIP());
        connected = true;
        myTz.setLocation("Europe/Paris");
        Serial.println("[📶⏲️ NTP CLOCK] 👋 Init");
        if (wifiCredentialsNeededSave)
        {
            saveWifiCredentialsToFlash();
        }
        connectToMqtt();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        connected = false;
        Serial.println("[📶 WIFI] 🔴 FAILED");
        xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
        xTimerStart(wifiReconnectTimer, 0);
        break;
    }
}

void connectToWifi()
{
    WiFi.begin(wifiSSID, wifiPassword);
    Serial.println("[📶 WIFI] 👋 Init");
}

void connectToMqtt()
{
    while (redrawInProgress)
    {
        Serial.println("Waiting for redraw");
        delay(100);
    }
    Serial.println("📨MQTT] 👋 Init");
    mqttClient.setServer(mqtt_host, mqtt_port);
    mqttClient.setCredentials(mqttUsername, mqttPassword);
    mqttClient.connect();
}

void onMqttConnect(bool sessionPresent)
{
    Serial.println("📨MQTT] 🟢 OK");
    mqttClient.subscribe("lampe/salon/status", 2);
    mqttConnected = true;
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    Serial.println("📨MQTT] 🔴 FAILED");
    mqttConnected = false;
    if (WiFi.isConnected())
    {
        xTimerStart(mqttReconnectTimer, 0);
    }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
    Serial.println("[📨MQTT] Subcribded");
}

void onMqttUnsubscribe(uint16_t packetId)
{
    Serial.println("Unsubscribe acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
}

void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    Serial.print("[📨MQTT] Received - ");
    Serial.print(topic);
    Serial.print(" ");
    Serial.println(payload);
    if (String(topic) == "lampe/salon/status")
    {
        buttonRedrawNeeded[0] = true;
        if (String(payload) == "on")
        {
            buttonState[0] = true;
        }
        if (String(payload) == "off")
            buttonState[0] = false;
    }
}

void onMqttPublish(uint16_t packetId)
{
    Serial.println("[📨MQTT] Sended");
}

bool readWifiCredentialsFlash()
{
    if (LittleFS.exists("/wifi.txt"))
    {
        File LittleFS_File = LittleFS.open("/wifi.txt", FILE_READ);
        wifiSSID = LittleFS_File.readStringUntil('\n');
        wifiSSID.trim();
        wifiPassword = LittleFS_File.readStringUntil('\n');
        wifiPassword.trim();
        LittleFS_File.close();
        Serial.println("[💾 FLASH] 🟢 /flash/wifi.txt founded");
        return true;
    }
    wifiCredentialsNeededSave = true;
    Serial.println("[💾 FLASH] 🔴 /flash/wifi.txt not founded");
    return false;
}

bool readWifiCredentialsSD()
{
    if (SD.exists("/wifi.txt"))
    {
        File SD_File = SD.open("/wifi.txt", "r");
        String newWifiSSID = SD_File.readStringUntil('\n');
        newWifiSSID.trim();
        String newWifiPassword = SD_File.readStringUntil('\n');
        newWifiPassword.trim();
        if(newWifiSSID == wifiSSID && newWifiPassword == wifiPassword){
            Serial.println("[💾 SD] 🟢 /sd/wifi.txt Same Credentials");
        } else {
            Serial.println("[💾 SD] 🟢 /sd/wifi.txt New Credentials");
            wifiSSID = newWifiSSID;
            wifiPassword = newWifiPassword;
            wifiCredentialsNeededSave = true;
        }
        SD_File.close();
        return true;
    }
    Serial.println("[💾 SD] ❔ /sd/wifi.txt not founded");
    return false;
}

void wifiStart()
{
    readWifiCredentialsFlash();
    readWifiCredentialsSD();
    mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
    wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

    WiFi.onEvent(WiFiEvent);

    mqttClient.onConnect(onMqttConnect);
    mqttClient.onDisconnect(onMqttDisconnect);
    mqttClient.onSubscribe(onMqttSubscribe);
    mqttClient.onUnsubscribe(onMqttUnsubscribe);
    mqttClient.onMessage(onMqttMessage);
    mqttClient.onPublish(onMqttPublish);

    xTimerStart(wifiReconnectTimer, 0);

    while (redrawInProgress)
    {
        Serial.println("Redraw in progress");
        delay(100);
    }
    xTaskCreate(
        WiFiTask,   // Fonction pour la tâche
        "WiFiTask", // Nom de la tâche
        6000,       // Taille de la pile pour la tâche
        NULL,       // Paramètre pour la tâche
        0,          // Priorité de la tâche
        NULL        // Handle de la tâche
    );
}