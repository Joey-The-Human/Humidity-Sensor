#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#define DHTPIN 2          // Pin where the DHT sensor is connected
#define DHTTYPE DHT11     // DHT 11

BME280 bme; // Create an instance of the BME280 sensor
DHT dht(DHTPIN, DHTTYPE); // Create an instance of the DHT sensor   
Adafruit_SSD1306 display(128, 64, &Wire, -1); // Create an instance of the OLED display
void setup() {
  Serial.begin(9600);
  dht.begin(); // Initialize the DHT sensor
  if (!bme.begin(0x76)) { // Initialize the BME280 sensor
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Initialize the OLED display
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay(); // Clear the display buffer
}
void loop(){
    // Read temperature, humidity, and pressure from the sensors
    float temperature = bme.readTemperature();
    float humidity = dht.readHumidity();
    float pressure = bme.readPressure() / 100.0F; // Convert to hPa
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(temperature) || isnan(humidity) || isnan(pressure)) {
        Serial.println("Failed to read from sensors!");
        return;
    }
    
    // Print the values to the Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Pressure: ");
    Serial.print(pressure);
    Serial.println(" hPa");
    
    // Display the values on the OLED display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    display.setCursor(0,0);
    display.print("Temp: ");
    display.print(temperature);
    display.println(" C");
    
    display.setCursor(0,16);
    display.print("Humidity: ");
    display.print(humidity);
    display.println(" %");
    
    display.setCursor(0,32);
    display.print("Pressure: ");
    display.print(pressure);
    display.println(" hPa");
    
    display.display(); // Update the OLED display with the new values
    
    delay(2000); // Wait for a few seconds before the next reading
}