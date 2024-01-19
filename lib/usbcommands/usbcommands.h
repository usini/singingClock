#include <SerialCommands.h>

void cmd_unrecognized(SerialCommands *sender, const char *cmd);
void cmd_reboot(SerialCommands *sender);
void cmd_status(SerialCommands *sender);
void cmd_ssid(SerialCommands *sender);
void cmd_pass(SerialCommands *sender);
void cmd_wifi(SerialCommands *sender);
void serial_init();
void serial_loop();

char serial_command_buffer_[256];
SerialCommands serial_commands(&Serial, serial_command_buffer_,
                               sizeof(serial_command_buffer_), "\r\n", "§");
SerialCommand serialReboot("reboot", cmd_reboot);
SerialCommand serialStatus("status", cmd_status);
SerialCommand serialSSID("ssid", cmd_ssid);
SerialCommand serialPass("pass", cmd_pass);
SerialCommand serialwifi("wifi", cmd_wifi);

void cmd_unrecognized(SerialCommands *sender, const char *cmd)
{
    sender->GetSerial()->println("Unrecognized command - " + String(cmd));
}

void cmd_status(SerialCommands *sender)
{
    peripherals_statuts();
    Serial.println("[📶 WIFI] 🏷️ SSID - " + wifi_ssid);
    if (connected)
    {
        Serial.println("[📶 WIFI] 🟢");
    }
    else
    {
        Serial.println("[📶 WIFI] ...");
    }
}

void cmd_reboot(SerialCommands *sender)
{
    Serial.println("Rebooting...");
    ESP.restart();
}

void cmd_ssid(SerialCommands *sender)
{
    char *value = sender->Next();
    wifi_ssid = value;
    Serial.println("[📶 WIFI] 🏷️ SSID Changed to - " + wifi_ssid);
}

void cmd_pass(SerialCommands *sender)
{
    char *value = sender->Next();
    wifi_password = value;
    Serial.println("[📶 WIFI] 🏷️ Password Changed");
}

void cmd_wifi(SerialCommands *sender)
{
    char *value = sender->Next();
    String arg = String(value);
    if (arg == "restart")
    {
        wifi_change = true;
        Serial.println("[📶 WIFI] ♾️ Restart");
    } else {
        Serial.println("[🔌USB] - Invalid command: wifi§" + arg);
    }
}

void serial_init()
{
    serial_commands.SetDefaultHandler(cmd_unrecognized);
    serial_commands.AddCommand(&serialReboot);
    serial_commands.AddCommand(&serialStatus);
    serial_commands.AddCommand(&serialSSID);
    serial_commands.AddCommand(&serialPass);
    serial_commands.AddCommand(&serialwifi);
}

void serial_loop()
{
    serial_commands.ReadSerial();
}