/*
  ScreamSense (Arduino Uno version)
  -----------------------------------
  Detects a loud, sustained sound (like a scream) using a sound sensor's
  analog output, then triggers an LED and buzzer alert. No WiFi.

  WIRING (Arduino Uno pin numbers):
    Sound sensor  AO  -> A0   (analog output pin)
    Sound sensor  VCC -> 5V
    Sound sensor  GND -> GND
    LED (+)       -> pin 2 (direct connection, no resistor)
    LED (-)       -> GND
    Buzzer (+)    -> pin 5
    Buzzer (-)    -> GND
*/

#define SOUND_SENSOR_PIN A0
#define LED_PIN           2
#define BUZZER_PIN        5

// Analog reading (0-1023) above which a sample counts as "loud".
// Tune this after watching real readings in Serial Monitor.
const int LOUD_THRESHOLD = 150; // adjust after testing -- baseline was ~25, this gives good margin

// How many consecutive loud samples (checked every SAMPLE_INTERVAL_MS)
// are needed before triggering the alert.
const int REQUIRED_LOUD_SAMPLES = 5;
const unsigned long SAMPLE_INTERVAL_MS = 20;

// How long (ms) the alert stays on once triggered
const unsigned long ALERT_DURATION_MS = 3000;

// Minimum time (ms) between two separate alerts
const unsigned long ALERT_COOLDOWN_MS = 5000;

unsigned long alertStartTime = 0;
unsigned long lastAlertTime  = 0;
unsigned long lastSampleTime = 0;
int consecutiveLoudSamples   = 0;
bool alertActive = false;

void setup() {
  Serial.begin(9600);
  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("ScreamSense ready. Listening for loud sounds...");
}

void loop() {
  unsigned long now = millis();

  if (!alertActive && now - lastSampleTime >= SAMPLE_INTERVAL_MS) {
    lastSampleTime = now;
    int level = analogRead(SOUND_SENSOR_PIN); // 0-1023

    Serial.println(level); // comment out once calibrated, if you want quieter output

    if (level >= LOUD_THRESHOLD) {
      consecutiveLoudSamples++;
    } else {
      consecutiveLoudSamples = 0;
    }

    if (consecutiveLoudSamples >= REQUIRED_LOUD_SAMPLES) {
      if (now - lastAlertTime > ALERT_COOLDOWN_MS) {
        triggerAlert();
        lastAlertTime = now;
      }
      consecutiveLoudSamples = 0;
    }
  }

  if (alertActive && millis() - alertStartTime >= ALERT_DURATION_MS) {
    stopAlert();
  }
}

void triggerAlert() {
  Serial.println("Loud sound detected! Alert ON.");
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  alertActive = true;
  alertStartTime = millis();
}

void stopAlert() {
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  alertActive = false;
  Serial.println("Alert cleared.");
}
