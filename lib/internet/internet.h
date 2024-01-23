
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
String wifi_ssid = "";
String wifi_password = "";

// NTP Settings
Timezone myTz;

bool connected = false;
bool wifi_change = false;
bool redraw_in_progress = false;
bool mqtt_connected = false;

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

IPAddress mqtt_host = IPAddress(192, 168, 0, 191);
int mqtt_port = 1883;
const char *mqtt_username = "";
const char *mqtt_password = "";

bool button_state[3] = {false, false, false};
bool button_redraw_needed[3] = {false, false, false};

void connectToMqtt();

void WiFiTask(void *pvParameters)
{
    while (true)
    {
        if (connected)
        {
            events();
        }
        if (wifi_change)
        {
            connected = false;
            wifi_change = false;
            Serial.println("[📶 WIFI] 👋🏷️ SSID changed");
            WiFi.disconnect();
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
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
    WiFi.begin(wifi_ssid, wifi_password);
    Serial.println("[📶 WIFI] 👋 Init");
}

void connectToMqtt()
{
    while (redraw_in_progress)
    {
        Serial.println("Waiting for redraw");
        delay(100);
    }
    Serial.println("📨MQTT] 👋 Init");
    mqttClient.setServer(mqtt_host, mqtt_port);
    mqttClient.setCredentials(mqtt_username, mqtt_password);
    mqttClient.connect();
}

void onMqttConnect(bool sessionPresent)
{
    Serial.println("📨MQTT] 🟢 OK");
    mqttClient.subscribe("lampe/salon/status", 2);
    mqtt_connected = true;
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    Serial.println("📨MQTT] 🔴 FAILED");
    mqtt_connected = false;
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
    if(String(topic) == "lampe/salon/status"){
        button_redraw_needed[0] = true;
        if(String(payload) == "on"){
            button_state[0] = true;
        }
        if(String(payload) == "off")
            button_state[0] = false;
    }
}

void onMqttPublish(uint16_t packetId)
{
    Serial.println("[📨MQTT] Sended");
}

bool read_wifi_credentials()
{
    File file = SD.open("/wifi.txt", "r");
    if (!file)
    {
        Serial.println("[💾 SD] 🔴 /sd/wifi.txt not founded");

        /*
        if (LittleFS.exists("/wifi.txt"))
        {
            File LittleFS_file = LittleFS.open("/wifi.txt", FILE_READ);
            Serial.println("Check FS wifi.txt");
            wifi_ssid = LittleFS_file.readStringUntil('\n');
            Serial.println(wifi_ssid);
            wifi_ssid.trim();

            wifi_password = LittleFS_file.readStringUntil('\n');
            Serial.println(wifi_password);
            wifi_password.trim();
            return true;
        }
        LittleFS_file.close();
        */
        file.close();
        return false;
    }
    // File LittleFS_file = LittleFS.open("/wifi.txt", FILE_WRITE);
    wifi_ssid = file.readStringUntil('\n');
    wifi_ssid.trim();
    // LittleFS_file.println(wifi_ssid);

    wifi_password = file.readStringUntil('\n');
    wifi_password.trim();
    // LittleFS_file.println(wifi_password);
    Serial.println("[💾 SD] 🟢 /sd/wifi.txt OK");
    file.close();
    // LittleFS_file.close();
    return true;
}

void wifiStart()
{
    read_wifi_credentials();
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

    while (redraw_in_progress)
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