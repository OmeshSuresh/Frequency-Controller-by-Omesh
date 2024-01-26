#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

int fre = 0;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the used OLED display

void setup(void) {
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  u8g2.begin(); 
}

void loop(void) {
  if (digitalRead(5) == LOW) {
    if (fre <= 50000) { // Check if frequency is within bounds
      fre += 5000;
    }
    delay(200); // Debouncing delay
  }

  if (digitalRead(6) == LOW) {
    if (fre <= 50000) { // Check if frequency is within bounds
      fre -= 5000;
    }
    delay(200); // Debouncing delay
  }

  char buffer[10];
  sprintf(buffer, "%d", fre); // Convert integer to string

  tone(3,fre);

  u8g2.clearBuffer(); // Clear the display buffer
  u8g2.setFont(u8g2_font_profont22_tr);
  u8g2.drawStr(40, 38, buffer);
  u8g2.drawStr(54, 57, "Hz");
  u8g2.sendBuffer();
}
