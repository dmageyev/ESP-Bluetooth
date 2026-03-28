#include "BluetoothSerial.h"
#include "esp_bt_device.h"

BluetoothSerial SerialBT;

static const char *DEVICE_NAME = "ESP32_Dmytro";
// String value = "";

void printDeviceAddress(){
  const uint8_t* point = esp_bt_dev_get_address();

  for (int i = 0; i < 6; i++){
    char str[3];
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);

    if (i<5) Serial.print(":");
    else Serial.println();
  }
}

void callback (esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if (event == ESP_SPP_SRV_OPEN_EVT){
    Serial.println("У Нас ГОСТИ");  
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!SerialBT.begin(DEVICE_NAME)) {
    Serial.println("Ошибка запуска Bluetooth");
    while (true) delay(1000);
  } else {
    Serial.println("Bluetooth запущен");
    Serial.print("Имя устройства: ");
    Serial.println(DEVICE_NAME);
    printDeviceAddress();
    Serial.println("Подключитесь с телефона/ПК и замучте его.");
  }
  SerialBT.register_callback(callback);
  SerialBT.setTimeout(0);
}

void loop() {
  // Данные из USB Serial в Bluetooth
  if (Serial.available()) {
    String value = Serial.readString();
    Serial.println("ESP32   : " + value);
    SerialBT.println(value);
  }

 // Данные из Bluetooth в USB Serial + эхо обратно
  if (SerialBT.available()) {
    String value = SerialBT.readString();
    Serial.println("Android  : " + value);
  }
}
