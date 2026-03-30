#include <stdio.h>
#include "M5GFX.h"

static M5GFX display;

extern "C" void app_main(void)
{
    display.init();
    display.setRotation(1);
    display.fillScreen(TFT_BLACK);
    display.setTextColor(TFT_WHITE, TFT_BLACK);
    display.setTextDatum(middle_center);
    display.setTextSize(2);
    display.drawString("Hello World!", display.width() / 2, display.height() / 2);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
