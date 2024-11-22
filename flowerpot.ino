#define BLYNK_TEMPLATE_ID "TMPL6fM0eg9Mn"
#define BLYNK_TEMPLATE_NAME "smart flower pot"
#define BLYNK_AUTH_TOKEN "NkhWzzLl1YNStpnsPlmx5QV7pSFc-YRb"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DHTPIN 4
#define DHTTYPE DHT11
#define SOIL_MOISTURE_PIN 34  // Define the analog pin for soil moisture sensor
#define WATER_LEVEL_PIN 35    // Define the analog pin for the water level sensor
#define RELAY_PIN 5           // Define the GPIO pin for the relay module


#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // Address for 128x64 OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Ishini";
const char* password = "12344321";

// Reference state for eyes
int ref_eye_height = 40;
int ref_eye_width = 40;
int ref_space_between_eye = 10;
int ref_corner_radius = 10;

// Current state of the eyes
int left_eye_height = ref_eye_height;
int left_eye_width = ref_eye_width;
int left_eye_x = 32;
int left_eye_y = 32;
int right_eye_x = 32 + ref_eye_width + ref_space_between_eye;
int right_eye_y = 32;
int right_eye_height = ref_eye_height;
int right_eye_width = ref_eye_width;

void draw_eyes(bool update = true) {
    display.clearDisplay();
    // Draw left eye
    int x = int(left_eye_x - left_eye_width / 2);
    int y = int(left_eye_y - left_eye_height / 2);
    display.fillRoundRect(x, y, left_eye_width, left_eye_height, ref_corner_radius, SSD1306_WHITE);
    // Draw right eye
    x = int(right_eye_x - right_eye_width / 2);
    y = int(right_eye_y - right_eye_height / 2);
    display.fillRoundRect(x, y, right_eye_width, right_eye_height, ref_corner_radius, SSD1306_WHITE);
    if (update) {
        display.display();
    }
}

void center_eyes(bool update = true) {
    // Move eyes to the center of the display
    left_eye_x = SCREEN_WIDTH / 2 - ref_eye_width / 2 - ref_space_between_eye / 2;
    left_eye_y = SCREEN_HEIGHT / 2;
    right_eye_x = SCREEN_WIDTH / 2 + ref_eye_width / 2 + ref_space_between_eye / 2;
    right_eye_y = SCREEN_HEIGHT / 2;
    draw_eyes(update);
}

void blink(int speed = 12) {
    draw_eyes();
    for (int i = 0; i < 3; i++) {
        left_eye_height -= speed;
        right_eye_height -= speed;
        draw_eyes();
        delay(1);
    }
    for (int i = 0; i < 3; i++) {
        left_eye_height += speed;
        right_eye_height += speed;
        draw_eyes();
        delay(1);
    }
}



void sleep() {
    left_eye_height = 2;
    right_eye_height = 2;
    draw_eyes(true);
}

void wakeup() {
    sleep();
    for (int h = 0; h <= ref_eye_height; h += 2) {
        left_eye_height = h;
        right_eye_height = h;
        draw_eyes(true);
    }
}

void happy_eye() {
    center_eyes(false);
    // Draw inverted triangle over lower part of eye
    int offset = ref_eye_height / 2;
    for (int i = 0; i < 10; i++) {
        display.fillTriangle(left_eye_x - left_eye_width / 2 - 1, left_eye_y + offset, 
                             left_eye_x + left_eye_width / 2 + 1, left_eye_y + 5 + offset, 
                             left_eye_x - left_eye_width / 2 - 1, left_eye_y + left_eye_height + offset, SSD1306_BLACK);
        display.fillTriangle(right_eye_x + right_eye_width / 2 + 1, right_eye_y + offset, 
                             right_eye_x - left_eye_width / 2 - 1, right_eye_y + 5 + offset, 
                             right_eye_x + right_eye_width / 2 + 1, right_eye_y + right_eye_height + offset, SSD1306_BLACK);
        offset -= 2;
        display.display();
        delay(1);
    }
    display.display();
    delay(1000);
}

void saccade(int direction_x, int direction_y) {
    int direction_x_movement_amplitude = 8;
    int direction_y_movement_amplitude = 6;
    int blink_amplitude = 8;

    for (int i = 0; i < 1; i++) {
        left_eye_x += direction_x_movement_amplitude * direction_x;
        right_eye_x += direction_x_movement_amplitude * direction_x;
        left_eye_y += direction_y_movement_amplitude * direction_y;
        right_eye_y += direction_y_movement_amplitude * direction_y;
        right_eye_height -= blink_amplitude;
        left_eye_height -= blink_amplitude;
        draw_eyes();
        delay(1);
    }
    for (int i = 0; i < 1; i++) {
        left_eye_x += direction_x_movement_amplitude * direction_x;
        right_eye_x += direction_x_movement_amplitude * direction_x;
        left_eye_y += direction_y_movement_amplitude * direction_y;
        right_eye_y += direction_y_movement_amplitude * direction_y;
        right_eye_height += blink_amplitude;
        left_eye_height += blink_amplitude;
        draw_eyes();
        delay(1);
    }
}

void move_big_eye(int direction) {
    int direction_oversize = 1;
    int direction_movement_amplitude = 2;
    int blink_amplitude = 5;

    for (int i = 0; i < 3; i++) {
        left_eye_x += direction_movement_amplitude * direction;
        right_eye_x += direction_movement_amplitude * direction;
        right_eye_height -= blink_amplitude;
        left_eye_height -= blink_amplitude;
        if (direction > 0) {
            right_eye_height += direction_oversize;
            right_eye_width += direction_oversize;
        } else {
            left_eye_height += direction_oversize;
            left_eye_width += direction_oversize;
        }
        draw_eyes();
        delay(1);
    }
    for (int i = 0; i < 3; i++) {
        left_eye_x += direction_movement_amplitude * direction;
        right_eye_x += direction_movement_amplitude * direction;
        right_eye_height += blink_amplitude;
        left_eye_height += blink_amplitude;
        if (direction > 0) {
            right_eye_height += direction_oversize;
            right_eye_width += direction_oversize;
        } else {
            left_eye_height += direction_oversize;
            left_eye_width += direction_oversize;
        }
        draw_eyes();
        delay(1);
    }

    delay(1000);

    for (int i = 0; i < 3; i++) {
        left_eye_x -= direction_movement_amplitude * direction;
        right_eye_x -= direction_movement_amplitude * direction;
        right_eye_height -= blink_amplitude;
        left_eye_height -= blink_amplitude;
        if (direction > 0) {
            right_eye_height -= direction_oversize;
            right_eye_width -= direction_oversize;
        } else {
            left_eye_height -= direction_oversize;
            left_eye_width -= direction_oversize;
        }
        draw_eyes();
        delay(1);
    }
    for (int i = 0; i < 3; i++) {
        left_eye_x -= direction_movement_amplitude * direction;
        right_eye_x -= direction_movement_amplitude * direction;
        right_eye_height += blink_amplitude;
        left_eye_height += blink_amplitude;
        if (direction > 0) {
            right_eye_height -= direction_oversize;
            right_eye_width -= direction_oversize;
        } else {
            left_eye_height -= direction_oversize;
            left_eye_width -= direction_oversize;
        }
        draw_eyes();
        delay(1);
    }

    center_eyes();
}

void setup() {
    // Initialize display
    Serial.begin(115200);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Initialize relay as off (assuming active LOW relay)

  WiFi.begin(ssid, password);

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to Wi-Fi.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to Wi-Fi.");
  }
  
  Serial.println("Connecting to Wi-Fi and Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();
}

void loop() {

    // Animation sequence
    Blynk.run();  // Handle Blynk connection and communication
  
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  int waterLevelValue = analogRead(WATER_LEVEL_PIN);
  int motor;
  // Convert sensor readings to percentages
  soilMoistureValue = map(soilMoistureValue, 0, 4095, 100, 0);
  waterLevelValue = map(waterLevelValue, 0, 4095, 0,100);

  // Print readings to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");
  
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);

  Serial.print("Water Level: ");
  Serial.println(waterLevelValue);
   if (soilMoistureValue < 30) {  // Threshold value for low soil moisture
    digitalWrite(RELAY_PIN, LOW);  // Turn on the water pump (assuming active LOW relay)
    Serial.println("Water pump ON");
    int motor =1;

  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Turn off the water pump
    Serial.println("Water pump OFF");
   int motor = 0;
  }

  // Send readings to Blynk app
  Blynk.virtualWrite(V1, temperature);        // Send temperature to Virtual Pin V1
  Blynk.virtualWrite(V2, humidity);           // Send humidity to Virtual Pin V2
  Blynk.virtualWrite(V3, soilMoistureValue);  // Send soil moisture to Virtual Pin V3
  Blynk.virtualWrite(V4, waterLevelValue);    // Send water level to Virtual Pin V4
  Blynk.virtualWrite(V0, motor);
  if (waterLevelValue < 10) {

    wakeup();
    delay(1000);
    happy_eye();
    delay(1000); 
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(40, 0);
    display.println("I'm ");
    display.setCursor(20, 20);
    display.println("thersty!");
    
    display.display();

  } 
  else {

    wakeup();
    delay(1000);

    blink();
    delay(1000);

    happy_eye();
    delay(1000);

    saccade(1, 0); // Move right
    delay(1000);

    saccade(-1, 0); // Move left
    delay(1000);

    move_big_eye(1); // Move big right eye
    delay(1000);

    move_big_eye(-1); // Move big left eye
    delay(1000);

    sleep();
    delay(1000);
  }
}
