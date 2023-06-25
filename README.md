# Maker Faire San José 2023
## Arduino IoT Cloud: Primeros pasos.
Material de apoyo para el laboratorio: Arduino IoT Cloud: Primeros Pasos, para el Maker Faire San José, dado en la Universidad UCenfotec, el 25 de Junio del 2023.


# ESP32
https://espressif.github.io/arduino-esp32/package_esp32_index.json

# Arduino Agent
https://create.arduino.cc/getting-started/plugin/download


    delay(500);
    if (led1) {
      // Turn on LED
      neopixel.setBrightness(200);
      neopixel.setPixelColor(0, 0, 0, 255);
      neopixel.show();
    }
    else 
    {
      // Turn off LED
      neopixel.clear(); 
      neopixel.show();
    }
