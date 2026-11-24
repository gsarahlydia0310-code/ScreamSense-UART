# ScreamSense — UART Based Output

A sound-activated alert system built on Arduino Uno. It reads a sound sensor, streams the live sound level to the computer over **UART (Serial, 9600 baud)**, and turns on an LED and buzzer when a loud, sustained sound (like a scream) is detected.

## Aim
To study UART-based serial communication using Arduino Uno and demonstrate it by transmitting real-time sound sensor data to a computer, along with a sound-triggered LED/buzzer alert.

## Components

| Component | Quantity |
|---|---|
| Arduino Uno | 1 |
| Sound sensor module (LM393-based, AO/DO/G/+) | 1 |
| LED | 1 |
| Buzzer | 1 |
| Breadboard | 1 |
| Jumper wires (male-to-male) | As required |
| USB cable | 1 |

## Circuit Connections

| From | To |
|---|---|
| Arduino **5V** | Breadboard red (+) rail |
| Arduino **GND** | Breadboard blue (–) rail |
| Sensor **+** (VCC) | Red (+) rail |
| Sensor **G** (GND) | Blue (–) rail |
| Sensor **A0** (analog out) | Arduino **A0** |
| LED anode (+, long leg) | Arduino **pin 2** |
| LED cathode (–, short leg) | Blue (–) rail |
| Buzzer **+** | Arduino **pin 5** |
| Buzzer **–** | Blue (–) rail |

The sensor's **D0** pin is left unconnected. This build uses the analog output only.

> **Note:** The LED is connected without a series resistor in this build. Adding a resistor (about 220Ω–1kΩ) in series with the LED is recommended.

## How It Works

1. `Serial.begin(9600)` starts UART communication with the computer.
2. The sketch reads the sound sensor on `A0` (value 0–1023) every 20 ms and prints it with `Serial.println()`.
3. If the reading stays above `LOUD_THRESHOLD` for 5 consecutive samples (about 100 ms), it is treated as a loud sound.
4. The LED and buzzer turn on for 3 seconds, then turn off.
5. A 5-second cooldown prevents immediate re-triggering.

## Getting Started

1. Wire the circuit as shown above.
2. Open `ScreamSense/ScreamSense.ino` in the Arduino IDE.
3. Select **Tools → Board → Arduino Uno** and choose the correct **Port**.
4. Click **Upload**. Close the Serial Monitor first, otherwise the upload fails with an "Access is denied" error.
5. Open **Serial Monitor** and set the baud rate to **9600**.
6. Make a loud sound near the sensor's microphone and watch the readings and the LED/buzzer.

## Calibration

- Note the baseline reading in silence (about 24–25 in this build).
- Note the peak reading during a loud sound.
- Set `LOUD_THRESHOLD` between the two values. It is currently `150`.
- The blue potentiometer (VR1) on the sensor changes its raw sensitivity.

## Tunable Settings

| Constant | Default | Meaning |
|---|---|---|
| `LOUD_THRESHOLD` | 150 | Reading above which a sample counts as loud |
| `REQUIRED_LOUD_SAMPLES` | 5 | Consecutive loud samples needed to trigger |
| `SAMPLE_INTERVAL_MS` | 20 | Time between sensor readings |
| `ALERT_DURATION_MS` | 3000 | How long the alert stays on |
| `ALERT_COOLDOWN_MS` | 5000 | Minimum time between alerts |

## Troubleshooting

- **"Access is denied" on COM port:** close the Serial Monitor before uploading.
- **Flat or unchanging readings:** plug the sensor's 4 pins directly into the breadboard instead of using loose jumper wires, and check the VCC and GND connections.
- **Garbled Serial Monitor output:** make sure the baud rate is set to 9600.

## Repository Structure

```
.
├── README.md
└── ScreamSense/
    └── ScreamSense.ino
```
