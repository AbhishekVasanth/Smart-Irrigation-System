# Smart Irrigation System

An Arduino-based irrigation system that checks how dry the soil is and waters the garden automatically. When the soil moisture sensor reads dry, the Arduino switches on a water pump through a relay, and the water flows to the drip lines and sprinkler.

## How it works
1. The soil moisture sensor is placed in the garden soil.
2. The Arduino reads the sensor (average of 10 readings) every 2 seconds.
3. If the reading is above the dry threshold, the pump is switched ON for 10 seconds.
4. The pump switches OFF and the system waits 30 seconds for the water to soak in.
5. The Arduino checks the soil again. When the soil is moist, the pump stays off.

## Components
- Arduino Uno
- Soil moisture sensor (analog)
- Relay module
- Water pump
- Drip irrigation lines and sprinkler
- Power supply for the Arduino and for the pump
- Jumper wires and tubing

## Pin connections
| Part | Connects to |
|---|---|
| Soil sensor VCC | 5V |
| Soil sensor GND | GND |
| Soil sensor AO | A0 |
| Relay VCC | 5V |
| Relay GND | GND |
| Relay IN | D7 |
| Pump | Relay COM and NO terminals, with its own power supply |

Connect all grounds together.

## Calibration
Soil sensors give different readings, so set the values at the top of the code for your own sensor:
- `SENSOR_DRY`: the reading with the sensor in dry air
- `SENSOR_WET`: the reading with the sensor in water
- `DRY_THRESHOLD`: the reading above which the soil counts as dry

Open the Serial Monitor (9600 baud) to see the live readings.

## Run it
1. Open `smart-irrigation-system.ino` in the Arduino IDE.
2. Select your board and upload.
3. If the pump switches the wrong way round, swap `PUMP_ON` and `PUMP_OFF` in the code.

## Possible improvements
- Use more than one sensor and separate valves for different garden areas
- Add a rain sensor and a water tank level sensor
- Send alerts to a phone using Wi-Fi or Bluetooth
- Power the system with a solar panel
