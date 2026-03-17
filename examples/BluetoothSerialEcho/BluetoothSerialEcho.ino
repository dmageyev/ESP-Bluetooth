#include "BluetoothSerial.h"

// Для ESP32 классический Bluetooth SPP.
// В Arduino IDE выберите плату: ESP32 Dev Module (ESP32 DevKit v1).

BluetoothSerial SerialBT;

static const char *DEVICE_NAME = "ESP32_DevKit_BT";

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!SerialBT.begin(DEVICE_NAME)) {
    Serial.println("Ошибка запуска Bluetooth");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("Bluetooth запущен");
  Serial.print("Имя устройства: ");
  Serial.println(DEVICE_NAME);
  Serial.println("Подключитесь с телефона/ПК и отправьте текст.");
  Serial.println("ESP32 вернет сообщение с префиксом: Echo -> ");
}

void loop() {
  // Данные из USB Serial в Bluetooth
  if (Serial.available()) {
    String fromUsb = Serial.readStringUntil('\n');
    fromUsb.trim();

    if (fromUsb.length() > 0) {
      SerialBT.print("USB -> ");
      SerialBT.println(fromUsb);
      Serial.println("Отправлено в BT: " + fromUsb);
    }
  }

  // Данные из Bluetooth в USB Serial + эхо обратно
  if (SerialBT.available()) {
    String fromBt = SerialBT.readStringUntil('\n');
    fromBt.trim();

    if (fromBt.length() > 0) {
      Serial.println("Получено по BT: " + fromBt);
      SerialBT.print("Echo -> ");
      SerialBT.println(fromBt);
    }
  }

  delay(10);
}
