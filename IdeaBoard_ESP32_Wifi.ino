// https://learn.sparkfun.com/tutorials/esp32-thing-plus-usb-c-hookup-guide/arduino-example-wifi
// En el Arduino IDE escoger la placa: ESP32 Dev Module

#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

// WiFi network name and password:
const char * networkName = "Maker FAIRE";
const char * networkPswd = "MAKERFAIRE2023";

// Internet domain to request from:
constexpr char * hostDomain = "example.com";
constexpr int hostPort = 80;

constexpr int BUTTON_PIN = 27;

constexpr int PIXEL_PIN = 2;

Adafruit_NeoPixel neopixel(1, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  // Initilize hardware:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  neopixel.begin();
  neopixel.show(); // Initialize all pixels to 'off'

  // Connect to the WiFi network (see function below loop)
  connectToWiFi(networkName, networkPswd);

  neopixel.clear();

  Serial.print("Press button 0 to connect to ");
  Serial.println(hostDomain);
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == LOW)
  { // Check if button has been pressed
    while (digitalRead(BUTTON_PIN) == LOW)
      ; // Wait for button to be released

    // Turn on LED
    neopixel.setBrightness(200);
    neopixel.setPixelColor(0, 0, 0, 255);
    neopixel.show();

    requestURL(hostDomain, hostPort); // Connect to server

    delay(2000);

    // Turn off LED
    neopixel.clear(); 
    neopixel.show();
  }
}

void connectToWiFi(const char * ssid, const char * pwd)
{
  boolean ledState = 0;

  printLine();
  Serial.println("Connecting to WiFi network: " + String(ssid));

  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) 
  {
    // Blink LED while we're connecting:
    if (ledState) {
      neopixel.setBrightness(200);
      neopixel.show(); // Turn on LED
    }
    else
    {
      neopixel.clear(); // Turn off LED
    }

    ledState = !ledState; // Flip ledState

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void requestURL(const char * host, uint8_t port)
{
  printLine();
  Serial.println("Connecting to domain: " + String(host));

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.println("Connected!");
  printLine();

  // This will send the request to the server
  client.print((String)"GET / HTTP/1.1\r\n" +
               "Host: " + String(host) + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) 
  {
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
  client.stop();
}

void printLine()
{
  Serial.println();
  for (int i=0; i<30; i++)
    Serial.print("-");
  Serial.println();
}
