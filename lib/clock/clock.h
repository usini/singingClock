
void clock_init()
{
  txtSprite.createSprite(240, 96);
  txtSprite.setTextColor(TFT_WHITE, TFT_BLACK);
  txtSprite.setSwapBytes(true);
  txtSprite.loadFont("/Calibri-96", LittleFS);
}

void clock_display(void *parameter)
{
  while (true)
  {
    while (!connected)
    {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }

    TJpgDec.drawFsJpg(0, 0, "/bg.jpg", LittleFS);
    txtSprite.setCursor(0, 0);
    txtSprite.fillScreen(TFT_BLACK);
    String time = myTz.dateTime("H:i");
    txtSprite.print(time);
    txtSprite.pushSprite(55, 52, TFT_BLACK);
    vTaskDelay(pdMS_TO_TICKS(60000));
  }
}

bool clock_start()
{
  clock_init();
  xTaskCreate(
      clock_display, // Fonction pour la tâche
      "ClockTask",   // Nom de la tâche
      10000,         // Taille de la pile pour la tâche
      NULL,          // Paramètre pour la tâche
      4,             // Priorité de la tâche
      NULL           // Handle de la tâche
  );
  return true;
}