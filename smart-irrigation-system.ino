/*
  Smart Irrigation System

  Reads a soil moisture sensor and switches a water pump (through a relay
  module) when the soil is dry. The pump feeds the drip lines and sprinkler.

  Adjust the pins and the DRY_THRESHOLD value to match your wiring,
  your sensor and your soil.
*/

// ---- Pins ----
#define SOIL_PIN  A0   // soil moisture sensor analog output (AO)
#define RELAY_PIN 7    // relay module input (IN)

// Most relay modules switch ON with a LOW signal.
// If yours works the other way round, swap these two lines.
#define PUMP_ON  LOW
#define PUMP_OFF HIGH

// ---- Settings (calibrate for your sensor and soil) ----
const int DRY_THRESHOLD = 600;                 // reading above this = soil is dry
const int SENSOR_DRY    = 1023;                // reading with the sensor in dry air
const int SENSOR_WET    = 300;                 // reading with the sensor in water

const unsigned long WATERING_TIME  = 10000UL;  // pump runs for 10 seconds
const unsigned long SOAK_TIME      = 30000UL;  // wait 30 seconds for water to soak in
const unsigned long CHECK_INTERVAL = 2000UL;   // check the soil every 2 seconds

int readSoilMoisture();

void setup() {
  Serial.begin(9600);
  digitalWrite(RELAY_PIN, PUMP_OFF);   // make sure the pump starts OFF
  pinMode(RELAY_PIN, OUTPUT);
  Serial.println("Smart Irrigation System started");
}

void loop() {
  int raw = readSoilMoisture();
  int percent = map(raw, SENSOR_DRY, SENSOR_WET, 0, 100);
  percent = constrain(percent, 0, 100);

  Serial.print("Soil moisture: ");
  Serial.print(percent);
  Serial.print(" % (raw ");
  Serial.print(raw);
  Serial.print(") - ");

  if (raw > DRY_THRESHOLD) {
    Serial.println("DRY, watering");
    digitalWrite(RELAY_PIN, PUMP_ON);
    delay(WATERING_TIME);
    digitalWrite(RELAY_PIN, PUMP_OFF);
    Serial.println("Watering done, waiting for water to soak in");
    delay(SOAK_TIME);
  } else {
    Serial.println("OK, pump off");
    digitalWrite(RELAY_PIN, PUMP_OFF);
  }

  delay(CHECK_INTERVAL);
}

// Average of 10 readings to reduce noise
int readSoilMoisture() {
  long total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(SOIL_PIN);
    delay(10);
  }
  return total / 10;
}
