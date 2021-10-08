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
        mb.connect(remote, 1502);
    }

    // common values
    printUint32(mb, remote, "C_SUNSPEC_ID", C_SUNSPEC_ID);
    printUint16(mb, remote, "C_SUNSPEC_DID", C_SUNSPEC_DID);
    printUint16(mb, remote, "C_SUNSPEC_LENGTH", C_SUNSPEC_LENGTH);
    printString(mb, remote, "C_MANUFACTURER", C_MANUFACTURER, C_MANUFACTURER_SIZE);
    printString(mb, remote, "C_MODEL", C_MODEL, C_MODEL_SIZE);
    printString(mb, remote, "C_VERSION", C_VERSION, C_VERSION_SIZE);
    printString(mb, remote, "C_SERIALNUMBER", C_SERIALNUMBER, C_SERIALNUMBER_SIZE);
    printUint16(mb, remote, "C_DEVICEADDRESS", C_DEVICEADDRESS);
    Serial.println("");

    // inverter values
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
    printAcc32(mb,remote, "I_AC_ENERGY_WH", I_AC_ENERGY_WH);
    printInt16(mb, remote, "I_AC_ENERGY_WH_SF", I_AC_ENERGY_WH_SF);

    delay(30000);
}
