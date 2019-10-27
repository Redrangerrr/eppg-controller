// Copyright 2019 <Zach Whitehead>
// OpenPPG

#define LAST_PAGE 2  // starts at 0

// Map float values
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// For digital time display - prints leading 0
String convertToDigits(byte digits) {
  String digits_string = "";
  if (digits < 10) digits_string.concat("0");
  digits_string.concat(digits);
  return digits_string;
}

int nextPage() {
  if (page >= LAST_PAGE) {
    return page = 0;
  }
  return ++page;
}

void addVSpace() {
  display.setTextSize(1);
  display.println(" ");
}

void setLEDs(byte state) {
  // digitalWrite(LED_2, state);
  digitalWrite(LED_3, state);
  digitalWrite(LED_SW, state);
}

void blinkLED() {
  byte ledState = !digitalRead(LED_SW);
  setLEDs(ledState);
}

void runVibe(unsigned int sequence[], int siz) {
  vibe.begin();
  for (int thisNote = 0; thisNote < siz; thisNote++) {
    vibe.setWaveform(thisNote, sequence[thisNote]);
  }
  vibe.go();
}

void playMelody(unsigned int melody[], int siz) {
  for (int thisNote = 0; thisNote < siz; thisNote++) {
    // quarter note = 1000 / 4, eigth note = 1000/8, etc.
    int noteDuration = 125;
    tone(BUZZER_PIN, melody[thisNote], noteDuration);
    delay(noteDuration);  // to distinguish the notes, delay between them
  }
  noTone(BUZZER_PIN);
}

void handleArmFail() {
  unsigned int arm_fail_melody[] = { 820, 640 };
  playMelody(arm_fail_melody, 2);
}

// for debugging
void printDeviceData() {
  Serial.print("version major ");
  Serial.println(deviceData.version_major);
  Serial.print("version minor ");
  Serial.println(deviceData.version_minor);
  Serial.print("armed_time ");
  Serial.println(deviceData.armed_time);
  Serial.print("crc ");
  Serial.println(deviceData.crc);
}

void printChipId() {
  volatile uint32_t val1, val2, val3, val4;
  volatile uint32_t *ptr1 = (volatile uint32_t *)0x0080A00C;
  val1 = *ptr1;
  volatile uint32_t *ptr = (volatile uint32_t *)0x0080A040;
  val2 = *ptr;
  ptr++;
  val3 = *ptr;
  ptr++;
  val4 = *ptr;

  Serial.print("chip id: 0x");
  char buf[33];
  sprintf(buf, "%8x%8x%8x%8x", val1, val2, val3, val4);
  Serial.println(buf);
}