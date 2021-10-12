#include <Arduino.h>
#include <ModbusSolarEdge.h>

// SSID of the Wi-Fi to connect to
const char *ssid = "your-ssid"; 

// Wi-Fi password
const char *password = "your-password";  // The password of the Wi-Fi network

// IP of the SolarEdge inverter
IPAddress remote(192, 168, 0, 1);

// Modbus port of the SolarEdge inverter
const int port = 1502;

// ModbusIP object
ModbusIP mb;

// Modbus SolarEdge helper
ModbusSolarEdge mbse;

void printChar(const char *name, const char *value) {
    char log[160];
    sprintf(log, "%s: %s", name, value);
    Serial.println(log);
}

void printChar(const char *name, uint32_t value) {
    char log[160];
    sprintf(log, "%s: %d", name, value);
    Serial.println(log);
}

void printString(ModbusIP &mb, IPAddress &remote, const char *name, uint16_t reg, uint16_t size) {
    char value[size * 2];
    mbse.readHregString(mb, remote, reg, size, value);
    printChar(name, value);
}

void printAcc32(ModbusIP &mb, IPAddress &remote, const char *name, uint16_t reg) {
    uint32_t value = mbse.readHregAcc32(mb, remote, reg);
    printChar(name, value);
}

void printFloat32(ModbusIP &mb, IPAddress &remote, const char *name, uint16_t reg) {
    float value = mbse.readHregFloat32(mb, remote, reg);
    printChar(name, value);
}

void printUint32(ModbusIP &mb, IPAddress &remote, const char *name, uint16_t reg) {
    uint32_t value = mbse.readHregUInt32(mb, remote, reg);
    printChar(name, value);
}

void printUint16(ModbusIP &mb, IPAddress &remote, const char *name, uint16_t reg) {
    uint16_t value = mbse.readHregUInt(mb, remote, reg);
    printChar(name, value);
}

void printInt16(ModbusIP &mb, IPAddress &remote, const char *name, uint16_t reg) {
    int16_t value = mbse.readHregInt(mb, remote, reg);
    printChar(name, value);
}

void setup() {
    Serial.begin(115200);  // Start the Serial communication to send messages to the computer
    delay(10);
    Serial.println('\n');

    WiFi.begin(ssid, password);  // Connect to the network
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print(++i);
        Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());  // Send the IP address of the ESP8266 to the computer

    mb.client();
}

void loop() {
    if (!mb.isConnected(remote)) {
        mb.connect(remote, port);
    }

    Serial.println("inverter common values");
    printUint32(mb, remote, "C_SUNSPEC_ID", C_SUNSPEC_ID);
    printUint16(mb, remote, "C_SUNSPEC_DID", C_SUNSPEC_DID);
    printUint16(mb, remote, "C_SUNSPEC_LENGTH", C_SUNSPEC_LENGTH);
    printString(mb, remote, "C_MANUFACTURER", C_MANUFACTURER, C_MANUFACTURER_SIZE);
    printString(mb, remote, "C_MODEL", C_MODEL, C_MODEL_SIZE);
    printString(mb, remote, "C_VERSION", C_VERSION, C_VERSION_SIZE);
    printString(mb, remote, "C_SERIALNUMBER", C_SERIALNUMBER, C_SERIALNUMBER_SIZE);
    printUint16(mb, remote, "C_DEVICEADDRESS", C_DEVICEADDRESS);
    Serial.println("");

    Serial.println("inverter values");
    printUint16(mb, remote, "I_SUNSPEC_DID", I_SUNSPEC_DID);
    printUint16(mb, remote, "I_SUNSPEC_LENGTH", I_SUNSPEC_LENGTH);
    printUint16(mb, remote, "I_AC_CURRENT", I_AC_CURRENT);
    printUint16(mb, remote, "I_AC_CURRENT_A", I_AC_CURRENT_A);
    printUint16(mb, remote, "I_AC_CURRENT_B", I_AC_CURRENT_B);
    printUint16(mb, remote, "I_AC_CURRENT_C", I_AC_CURRENT_C);
    printInt16(mb, remote, "I_AC_CURRENT_SF", I_AC_CURRENT_SF);
    printUint16(mb, remote, "I_AC_VOLTAGEAB", I_AC_VOLTAGEAB);
    printUint16(mb, remote, "I_AC_VOLTAGEBC", I_AC_VOLTAGEBC);
    printUint16(mb, remote, "I_AC_VOLTAGECA", I_AC_VOLTAGECA);
    printUint16(mb, remote, "I_AC_VOLTAGEAN", I_AC_VOLTAGEAN);
    printUint16(mb, remote, "I_AC_VOLTAGEBN", I_AC_VOLTAGEBN);
    printUint16(mb, remote, "I_AC_VOLTAGECN", I_AC_VOLTAGECN);
    printInt16(mb, remote, "I_AC_VOLTAGE_SF", I_AC_VOLTAGE_SF);
    printInt16(mb, remote, "I_AC_POWER", I_AC_POWER);
    printInt16(mb, remote, "I_AC_POWER_SF", I_AC_POWER_SF);
    printUint16(mb, remote, "I_AC_FREQUENCY", I_AC_FREQUENCY);
    printInt16(mb, remote, "I_AC_FREQUENCY_SF", I_AC_FREQUENCY_SF);
    printInt16(mb, remote, "I_AC_VA", I_AC_VA);
    printInt16(mb, remote, "I_AC_VA_SF", I_AC_VA_SF);
    printInt16(mb, remote, "I_AC_VAR", I_AC_VAR);
    printInt16(mb, remote, "I_AC_VAR_SF", I_AC_VAR_SF);
    printInt16(mb, remote, "I_AC_PF", I_AC_PF);
    printInt16(mb, remote, "I_AC_PF_SF", I_AC_PF_SF);
    printAcc32(mb, remote, "I_AC_ENERGY_WH", I_AC_ENERGY_WH);
    printInt16(mb, remote, "I_AC_ENERGY_WH_SF", I_AC_ENERGY_WH_SF);

    printUint16(mb, remote, "I_DC_CURRENT", I_DC_CURRENT);
    printInt16(mb, remote, "I_DC_CURRENT_SF", I_DC_CURRENT_SF);
    printUint16(mb, remote, "I_DC_VOLTAGE", I_DC_VOLTAGE);
    printInt16(mb, remote, "I_DC_VOLTAGE_SF", I_DC_VOLTAGE_SF);
    printInt16(mb, remote, "I_DC_POWER", I_DC_POWER);
    printInt16(mb, remote, "I_DC_POWER_SF", I_DC_POWER_SF);
    printInt16(mb, remote, "I_TEMP_SINK", I_TEMP_SINK);
    printInt16(mb, remote, "I_TEMP_SF", I_TEMP_SF);

    int16_t i_status = mbse.readHregInt(mb, remote, I_STATUS);
    printChar("I_STATUS", i_status);
    printChar("I_STATUS as text", mbse.I_STATUS_VALUES[i_status]);

    printUint16(mb, remote, "I_STATUS_VENDOR", I_STATUS_VENDOR);
    Serial.println("");

    Serial.println("meter 1 common values");
    printString(mb, remote, "M1_C_MANUFACTURER", M1_C_MANUFACTURER, M1_C_MANUFACTURER_SIZE);
    printString(mb, remote, "M1_C_MODEL", M1_C_MODEL, M1_C_MODEL_SIZE);
    printString(mb, remote, "M1_C_OPTION", M1_C_OPTION, M1_C_OPTION_SIZE);
    printString(mb, remote, "M1_C_VERSION", M1_C_VERSION, M1_C_VERSION_SIZE);
    printString(mb, remote, "M1_C_SERIALNUMBER", M1_C_SERIALNUMBER, M1_C_SERIALNUMBER_SIZE);
    Serial.println("");

    Serial.println("meter 1 values");
    printInt16(mb, remote, "M1_AC_POWER", M1_AC_POWER);
    printInt16(mb, remote, "M1_AC_POWER_SF", M1_AC_POWER_SF);
    printAcc32(mb, remote, "M1_EXPORTED", M1_EXPORTED);  // reading as acc32 does not match the specifications from the PDF but works for me
    printAcc32(mb, remote, "M1_IMPORTED", M1_IMPORTED);  // reading as acc32 does not match the specifications from the PDF but works for me
    Serial.println("");

    Serial.println("battery 1 common values");
    printString(mb, remote, "B1_MANUFACTURER_NAME", B1_MANUFACTURER_NAME, B1_MANUFACTURER_NAME_SIZE);
    printString(mb, remote, "B1_MODEL", B1_MODEL, M1_C_MODEL_SIZE);
    printString(mb, remote, "M1_C_OPTION", M1_C_OPTION, B1_MODEL_SIZE);
    printString(mb, remote, "B1_FIRMWARE_VERSION", B1_FIRMWARE_VERSION, B1_FIRMWARE_VERSION_SIZE);
    printString(mb, remote, "B1_SERIAL_NUMBER", B1_SERIAL_NUMBER, B1_SERIAL_NUMBER_SIZE);
    Serial.println("");

    Serial.println("battery 1 values");
    printFloat32(mb, remote, "B1_INSTANTANEOUS_POWER", B1_INSTANTANEOUS_POWER);
    printFloat32(mb, remote, "B1_STATE_OF_HEALTH_SOH", B1_STATE_OF_HEALTH_SOH);
    printFloat32(mb, remote, "B1_STATE_OF_ENERGY_SOE", B1_STATE_OF_ENERGY_SOE);

    uint32_t b1_status = mbse.readHregUInt32(mb, remote, B1_STATUS);
    printChar("B1_STATUS", b1_status);
    printChar("B1_STATUS as text", mbse.B_STATUS_VALUES[b1_status]);
    Serial.println("");

    // Try calculate values like the SolarEdge app

    // ##################################################################
    //
    //                    SUN
    //                     | (A)
    //                     v
    //   HOUSE <-(B)-  INVERTER  <-(C)-> GRID
    //                     ^
    //                     | (D)
    //                     v
    //                  BATTERY
    //
    // (A) see calculate_sun_power
    // (B) see calculate_house_usage
    // (C) use m1_m_ac_power_norm
    // (D) use b1_b_instantaneous_power
    //
    // ##################################################################

    int16_t i_ac_power = mbse.readHregInt(mb, remote, I_AC_POWER);
    int16_t i_ac_power_sf = mbse.readHregInt(mb, remote, I_AC_POWER_SF);
    int16_t i_ac_power_norm = mbse.norm(i_ac_power, i_ac_power_sf);

    int16_t m1_m_ac_power = mbse.readHregInt(mb, remote, M1_AC_POWER);
    int16_t m1_m_ac_power_sf = mbse.readHregInt(mb, remote, M1_AC_POWER_SF);
    int16_t m1_m_ac_power_norm = mbse.norm(m1_m_ac_power, m1_m_ac_power_sf);

    float b1_b_instantaneous_power = mbse.readHregFloat32(mb, remote, B1_INSTANTANEOUS_POWER);

    // (A) calculate sun power
    int a_sun_power = mbse.calculate_sun_power(i_ac_power_norm, b1_b_instantaneous_power);

    // (B) calculate power used by house
    int b_house_usage = mbse.calculate_house_usage(i_ac_power_norm, m1_m_ac_power_norm);

    // (C) grid input/consumption
    int c_meter_power = m1_m_ac_power_norm;

    // (D) battery charge/discharge
    int d_battery_power = b1_b_instantaneous_power;

    // battery level in percent
    float b1_b_state_of_energy = mbse.readHregFloat32(mb, remote, B1_STATE_OF_ENERGY_SOE);

    Serial.println("system overview");
    char log[320];
    sprintf(log, "                    SUN\n                     | (A) %dW\n                     v\n   HOUSE <-(B) %dW - INVERTER  <-(C) %dW -> GRID\n                     ^\n                     | (D) %dW/%fPCT\n                     v\n                  BATTERY (%s)\n", a_sun_power, b_house_usage, c_meter_power, d_battery_power, b1_b_state_of_energy, mbse.B_STATUS_VALUES[b1_status]);
    Serial.println(log);

    delay(30000);
}
