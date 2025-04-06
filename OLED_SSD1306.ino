#include <Wire.h>                 // Библиотека для работы с интерфейсом I2C
#include <Adafruit_GFX.h>         // Графическая библиотека
#include <Adafruit_SSD1306.h>     // Библиотека для OLED-дисплея

#define SCREEN_WIDTH 128          // Ширина экрана
#define SCREEN_HEIGHT 64          // Высота экрана
#define OLED_RESET     -1         // Рестартовый пин (если он есть)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);             // Иницилизация последовательного порта

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Инициализация дисплея
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                      // Зависание программы, если дисплей не инициализировался
  }

  display.clearDisplay();         // Очищаем буфер дисплея
}

void loop() {
  display.setTextSize(2);         // Размер тектса 
  display.setTextColor(WHITE);    // Цвет текста
  display.setCursor(7, 28);       // Расположение текста на дисплее
  display.print("anachment");     // Выводим информацию

  display.display();              // Обновление дисплея
  delay(2000);                    // Время до следующего повторения
}
