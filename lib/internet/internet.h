String wifi_ssid = "";
String wifi_password = "";
Timezone myTz;
bool connected = false;
bool redraw_clock_needed = true;
#include "wifi_icon.h"

TFT_eSprite wiFiSprite = TFT_eSprite(&tft);

void WiFiTask(void *parameter)
{
    WiFi.begin(wifi_ssid, wifi_password);
    Serial.println("[📶 WIFI] 👋 Init");
    Serial.println("[📶 WIFI] 🏷️ SSID - " + wifi_ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        Serial.println("[📶 WIFI] ...");
    }
    Serial.println("[📶 WIFI] 🟢 OK");
    //while (!screen_available)
    //{
    //    vTaskDelay(pdMS_TO_TICKS(10));
    //}
    //drawJPGpos(256, 0, "/wifi.jpg");
    Serial.println("[📶⏲️ NTP CLOCK] 👋 Init");
    myTz.setLocation("Europe/Paris");
    waitForSync();
    connected = true;
    redraw_clock_needed = true;
    Serial.println("[📶⏲️ NTP CLOCK] 🟢 OK");
    while (1)
    {
        events();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
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
    //File LittleFS_file = LittleFS.open("/wifi.txt", FILE_WRITE);
    wifi_ssid = file.readStringUntil('\n');
    wifi_ssid.trim();
    // LittleFS_file.println(wifi_ssid);

    wifi_password = file.readStringUntil('\n');
    wifi_password.trim();
    //LittleFS_file.println(wifi_password);
    Serial.println("[💾 SD] 🟢 /sd/wifi.txt OK");
    file.close();
    // LittleFS_file.close();
    return true;
}

bool wifi_start()
{
    wiFiSprite.createSprite(16, 16);
    wiFiSprite.setSwapBytes(true);
    if (read_wifi_credentials())
    {
        xTaskCreate(
            WiFiTask,   // Fonction pour la tâche
            "WiFiTask", // Nom de la tâche
            3000,       // Taille de la pile pour la tâche
            NULL,       // Paramètre pour la tâche
            0,          // Priorité de la tâche
            NULL        // Handle de la tâche
        );
        return true;
    }
    else
    {
        return false;
    }
}