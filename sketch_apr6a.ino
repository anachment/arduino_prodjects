#include <Wire.h>                                         // Библиотека для работы с I2C
#include <Adafruit_GFX.h>                                 // Базовая библиотека для графики
#include <Adafruit_SSD1306.h>                             // Библиотека для управления OLED-дисплеем
#include "DHT.h"                                          // Исправленное название библиотеки для датчиков DHT

// Определение типов и пинов
#define SCREEN_WIDTH 128                                  // Ширина экрана
#define SCREEN_HEIGHT 64                                  // Высота экрана
#define OLED_RESET     -1                                 // Пин сброса дисплея (-1, если не используется)
#define DHTPIN         7                                  // Пин подключения датчика DHT
#define DHTTYPE        DHT11                              // Тип используемого датчика

                                                          // Создание объектов
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);                                 // Создаем объект класса DHT

void setup() {
  Serial.begin(9600);                                     // Инициализация последовательного порта
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {       // Адрес дисплея может различаться
    Serial.println(F("SSD1306 allocation failed"));       // Сообщаем об ошибке
    while (true);                                         // Зависаем, если дисплей не инициализировался
  }

  display.clearDisplay();                                 // Очищаем буфер дисплея
  display.setTextSize(1);                                 // Устанавливаем размер текста
  display.setTextColor(WHITE);                            // Устанавливаем цвет текста

  dht.begin();                                            // Инициализируем датчик DHT
}

void loop() {
                                                          // Считываем данные с датчика
  float temperature = dht.readTemperature();              // Температура в градусах Цельсия
  float humidity = dht.readHumidity();                    // Относительная влажность (%)

                                                          // Проверяем наличие ошибок считывания
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

                                                          // Очищаем дисплей перед обновлением данных
  display.clearDisplay();

                                                          // Выводим значения на дисплей
  display.setCursor(0, 10);                               // Устанавливаем позицию курсора
  display.print("Temp: ");                                // Выводим заголовок
  display.print(temperature);                             // Выводим значение температуры
  display.print(" C");                                    // Добавляем символ градусов Цельсия
  display.setCursor(0, 30);                               // Переходим на следующую строку
  display.print("Humidity: ");                            // Выводим заголовок
  display.print(humidity);                                // Выводим значение влажности
  display.print("%");                                     // Добавляем символ процента
  display.setCursor(30, 50);
  display.print("anachment");                              // Выводим "лого"

  display.display();                                      // Обновляем дисплей
  delay(2000);                                            // Пауза между обновлениями
}