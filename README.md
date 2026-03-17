# ESP-Bluetooth

Пример для **ESP32 DevKit v1** (Arduino IDE, core **2.0.17**) с классическим Bluetooth (SPP).

## Что в репозитории
- `examples/BluetoothSerialEcho/BluetoothSerialEcho.ino` — двусторонний мост:
  - USB Serial -> Bluetooth
  - Bluetooth -> USB Serial
  - Эхо-ответ в Bluetooth с префиксом `Echo ->`

## Как запустить
1. В Arduino IDE установите **ESP32 by Espressif Systems** версии **2.0.17**.
2. Откройте скетч `examples/BluetoothSerialEcho/BluetoothSerialEcho.ino`.
3. Выберите плату **ESP32 Dev Module** (подходит для ESP32 DevKit v1).
4. Загрузите скетч на плату.
5. Откройте Serial Monitor на **115200 baud**.
6. На телефоне/ПК найдите Bluetooth-устройство `ESP32_DevKit_BT` и подключитесь.
7. Отправьте строку с `\n` в конце — получите ответ `Echo -> <ваш текст>`.

## Важно
- Это **Classic Bluetooth SPP**, не BLE.
- На некоторых Android-устройствах может потребоваться разрешение на доступ к Nearby devices/Location.
