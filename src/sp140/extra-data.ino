// Copyright 2020 <Zach Whitehead>
// OpenPPG

// ** Logic for EEPROM **
# define EEPROM_OFFSET 0  // Address of first byte of EEPROM

// read saved data from EEPROM
void refreshDeviceData() {
  uint8_t tempBuf[sizeof(deviceData)];
  uint16_t crc;

  #ifdef M0_PIO
    if (0 != eep.read(EEPROM_OFFSET, tempBuf, sizeof(deviceData))) {
      // Serial.println(F("error reading EEPROM"));
    }
  #elif RP_PIO
    EEPROM.get(EEPROM_OFFSET, tempBuf);
  #endif

  memcpy((uint8_t*)&deviceData, tempBuf, sizeof(deviceData));
  crc = crc16((uint8_t*)&deviceData, sizeof(deviceData) - 2);

  if (crc != deviceData.crc) {
    resetDeviceData();
  }
}

// write to EEPROM
void writeDeviceData() {
  deviceData.crc = crc16((uint8_t*)&deviceData, sizeof(deviceData) - 2);
  #ifdef M0_PIO
    if (0 != eep.write(EEPROM_OFFSET, (uint8_t*)&deviceData, sizeof(deviceData))) {
      //Serial.println(F("error writing EEPROM"));
    }
  #elif RP_PIO
    EEPROM.put(EEPROM_OFFSET, deviceData);
    EEPROM.commit();
  #endif
}

// reset eeprom and deviceData to factory defaults
void resetDeviceData() {
  deviceData = STR_DEVICE_DATA_140_V1();
  deviceData.version_major = VERSION_MAJOR;
  deviceData.version_minor = VERSION_MINOR;
  deviceData.screen_rotation = 3;
  deviceData.sea_pressure = DEFAULT_SEA_PRESSURE;  // 1013.25 mbar
  deviceData.metric_temp = true;
  deviceData.metric_alt = true;
  deviceData.performance_mode = 0;
  deviceData.batt_size = 4000;  // 4kw
  writeDeviceData();
}

// ** Logic for WebUSB **
void line_state_callback(bool connected) {
  digitalWrite(LED_SW, connected);

  if ( connected ) send_usb_serial();
}

// customized for sp140
void parse_usb_serial() {
#ifdef USE_TINYUSB
  const size_t capacity = JSON_OBJECT_SIZE(12) + 90;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, usb_web);

  if (doc["command"] && doc["command"] == "rbl") {
    display.fillScreen(DEFAULT_BG_COLOR);
    displayMessage("BL - UF2");
    rebootBootloader();
    return;  // run only the command
  }

  if (doc["major_v"] < 5) return;

  deviceData.screen_rotation = doc["screen_rot"];  // "3/1"
  deviceData.sea_pressure = doc["sea_pressure"];  // 1013.25 mbar
  deviceData.metric_temp = doc["metric_temp"];  // true/false
  deviceData.metric_alt = doc["metric_alt"];  // true/false
  deviceData.performance_mode = doc["performance_mode"];  // 0,1
  deviceData.batt_size = doc["batt_size"];  // 4000
  writeDeviceData();
  resetDisplay();
  send_usb_serial();
#endif
}

void send_usb_serial() {
#ifdef USE_TINYUSB
#ifdef M0_PIO
  const size_t capacity = JSON_OBJECT_SIZE(11) + 90;
  DynamicJsonDocument doc(capacity);

  doc["major_v"] = VERSION_MAJOR;
  doc["minor_v"] = VERSION_MINOR;
  doc["arch"] = "SAMD21";
  doc["screen_rot"] = deviceData.screen_rotation;
  doc["armed_time"] = deviceData.armed_time;
  doc["metric_temp"] = deviceData.metric_temp;
  doc["metric_alt"] = deviceData.metric_alt;
  doc["performance_mode"] = deviceData.performance_mode;
  doc["sea_pressure"] = deviceData.sea_pressure;
  doc["device_id"] = chipId();

  char output[256];
  serializeJson(doc, output);
  usb_web.println(output);
#elif RP_PIO
  StaticJsonDocument<220> doc; // <- a little more than 220 bytes in the stack
  // const size_t capacity = JSON_OBJECT_SIZE(15) + 90;
  // StaticJsonDocument = doc(capacity);

  doc["mj_v"].set(VERSION_MAJOR);
  doc["mi_v"].set(VERSION_MINOR);
  doc["arch"].set("RP2040");
  doc["scr_rot"].set(deviceData.screen_rotation);
  doc["ar_tme"].set(deviceData.armed_time);
  doc["m_tmp"].set(deviceData.metric_temp);
  doc["m_alt"].set(deviceData.metric_alt);
  doc["prf"].set(deviceData.performance_mode);
  doc["sea_p"].set(deviceData.sea_pressure);
  doc["id"].set(chipId());

  char output[256];
  serializeJson(doc, output, sizeof(output));
  Serial.println(output);
  delay(50);
  usb_web.print(output);
  usb_web.flush();
  Serial.println(chipId());
#endif // M0_PIO/RP_PIO
#endif // USE_TINYUSB
}
