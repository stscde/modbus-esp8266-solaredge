#pragma once
#if !defined(ESP8266) && !defined(ESP32)
#error Unsupported architecture
#endif

#include <ModbusIP_ESP8266.h>

// ##################################################################
// Common Model MODBUS Register Mappings
// see "sunspec-implementation-technical-note.pdf"
// https://www.solaredge.com/sites/default/files/sunspec-implementation-technical-note.pdf
// ##################################################################

const int C_SUNSPEC_ID = 40000;  // uint32, size 2, Id of this Modbus map, should be "SunS" (0x53756e53)

const int C_SUNSPEC_DID = 40002; // uint16, size 1, Sunspec Common Model Block identification

const int C_SUNSPEC_LENGTH = 40003; // uint16, size 1, number of 16-bit registers, 65

const int C_MANUFACTURER = 40004;    // Manufacturer should be "SolarEdge"
const int C_MANUFACTURER_SIZE = 16;  // String(32)

const int C_MODEL = 40020;
const int C_MODEL_SIZE = 16;  // String(32)

const int C_VERSION = 40044;
const int C_VERSION_SIZE = 8;  // String(16)

const int C_SERIALNUMBER = 40052;
const int C_SERIALNUMBER_SIZE = 16;  // String(32)

const int C_DEVICEADDRESS = 40068;  // unit16, size 1, MODBUS Unit ID

// ##################################################################
// Inverter Model MODBUS Register Mappings
// see "sunspec-implementation-technical-note.pdf"
// https://www.solaredge.com/sites/default/files/sunspec-implementation-technical-note.pdf
// ##################################################################

const int I_SUNSPEC_DID = 40069; // uint16, size 1, phases, 101 = single, 102 = split, 103 = three
const int I_SUNSPEC_LENGTH = 40070; // uint16, size 1, model block length, 50
const int I_AC_CURRENT = 40071; // uint16, size 1, Amps, AC Total Current Value
const int I_AC_CURRENT_A = 40072; // uint16, size 1, Amps, AC Phase A Current value
const int I_AC_CURRENT_B = 40073; // uint16, size 1, Amps, AC Phase B Current value
const int I_AC_CURRENT_C = 40074; // uint16, size 1, Amps, AC Phase C Current value
const int I_AC_CURRENT_SF = 40075; // int16, size 1, AC Current scale factor
const int I_AC_VOLTAGEAB = 40076; // uint16, size 1, Volts, AC Voltage Phase AB value
const int I_AC_VOLTAGEBC = 40077; // uint16, size 1, Volts, AC Voltage Phase BC value
const int I_AC_VOLTAGECA = 40078; // uint16, size 1, Volts, AC Voltage Phase CA value
const int I_AC_VOLTAGEAN = 40079; // uint16, size 1, Volts, AC Voltage Phase A to N value
const int I_AC_VOLTAGEBN = 40080; // uint16, size 1, Volts, AC Voltage Phase B to N value
const int I_AC_VOLTAGECN = 40081; // uint16, size 1, Volts, AC Voltage Phase C to N value
const int I_AC_VOLTAGE_SF = 40082; // int16, size 1, Volts, AC Voltage scale factor
const int I_AC_POWER = 40083; // int16, size 1, Watts, AC Power value
const int I_AC_POWER_SF = 40084; // int16, size 1, AC Power scale factor
const int I_AC_FREQUENCY = 40085; // uint16, size 1, Hertz, AC frequency
const int I_AC_FREQUENCY_SF = 40086; // int16, size 1, AC frequency scale factor
const int I_AC_VA = 40087; // int16, size 1, VA, Apparent Power (Scheinleistung)
const int I_AC_VA_SF = 40088; // int16, size 1, Scale Factor
const int I_AC_VAR = 40089; // int16, size 1, VAR, reactive power
const int I_AC_VAR_SF = 40090; // int16, size 1, VAR, reactive power scale factor
const int I_AC_PF = 40091; // int16, size 1, %, power factor
const int I_AC_PF_SF = 40092; // int16, size 1, power factor scale factor
const int I_AC_ENERGY_WH = 40093;  // acc32, size 2, WattHours, AC lifetime energy production
const int I_AC_ENERGY_WH_SF = 40095; // uint16, size 1, Volts, AC lifetime energy production scale factor

const int I_DC_POWER = 40100;     // int16, size 1, Watts, DC Power value
const int I_DC_POWER_SF = 40101;  // int16, size 1, DC Power scale factor
const int I_STATUS = 40107;  // uint16, size 1, Operating State
//static const char *I_STATUS_VALUES[] = {"I_STATUS_OFF", "I_STATUS_SLEEPING", "I_STATUS_STARTING", "I_STATUS_MPPT", "I_STATUS_THROTTLED", "I_STATUS_SHUTTING_DOWN",
//                                        "I_STATUS_FAULT", "I_STATUS_STANDBY"};

// ##################################################################
// MODBUS Mapping Meter 1
// see "sunspec-implementation-technical-note.pdf"
// ##################################################################

const int M1_C_MANUFACTURER = 40123;
const int M1_C_MANUFACTURER_SIZE = 16;  // String(32), size 16, Meter manufacturer

const int M1_C_MODEL = 40139;
const int M1_C_MODEL_SIZE = 16;  // String(32), size 16, Meter model

const int M1_C_OPTION = 40155;
const int M1_C_OPTION_SIZE = 8;  // String(16), size 8, Export + Import, Production, consumption

const int M1_C_VERSION = 40163;
const int M1_C_VERSION_SIZE = 8;  // String(16), size 8, Meter version

const int M1_C_SERIALNUMBER = 40171;
const int M1_C_SERIALNUMBER_SIZE = 16;  // String(32), size 16, Meter SN

const int M1_C_DEVICEADDRESS = 40187;  // uint16, size 1, Inverter Modbus ID

const int M1_M_AC_POWER = 40206;  // int16, size 1, Watts, Total Real Power (sum of active phases)

const int M1_M_AC_POWER_SF = 40210;  // int16, size 1, SF, AC Real Power Scale Factor

// ##################################################################
// MODBUS Mapping Battery 1
// see "Power Control Open Protocol for SolarEdge Inverters.pdf" (page 19)
// ##################################################################

const int B1_B_INSTANTANEOUS_POWER = 57716;  // Float32, size 2, W, Battery 1 Instantaneous Power

const int B1_B_STATE_OF_HEALTH = 57730;  // Float32, size 2, Battery 1 State of Health (SOH)

const int B1_B_STATE_OF_ENERGY = 57732;  // Float32, size 2, Battery 1 State of Energy (SOE)

const int B1_B_STATE = 57734;  // Uint32, size 2, Battery 1 Status
//static const char *B_STATUS_VALUES[] = {"Off", "Standby", "Init", "Charge", "Discharge", "Fault", "Idle"};

class ModbusSolarEdge {
   public:
    /**
     * Read hreg string value into a char array
     * @param mb ModbusIP object reference
     * @param remote IP address of the inverter object reference
     * @param regStart First register containing the first character(s)
     * @param length Numbers of registers to read
     * @param string Character array the string will be stored in. Must be twice the length of "length" as each 16-bit register contains 2 8-bit characters.
     */
    void readHregString(ModbusIP &mb, IPAddress &remote, const int regStart, const int length, char string[]);

    /**
     * Read hreg uint16 value of length 1
     *
     * @param mb ModbusIP object reference
     * @param remote IP address of the inverter object reference
     * @param regStart Register
     * @return uint value
     */
    uint16_t readHregUInt(ModbusIP &mb, IPAddress &remote, const int regStart);

    /**
     * Read hreg int16 value of length 1
     *
     * @param mb ModbusIP object reference
     * @param remote IP address of the inverter object reference
     * @param regStart Register
     * @return int value
     */
    int16_t readHregInt(ModbusIP &mb, IPAddress &remote, const int regStart);

    /**
     * Read hreg acc32 value of length 2
     *
     * @param mb ModbusIP object reference
     * @param remote IP address of the inverter object reference
     * @param regStart Register
     * @return acc32 value
     */
    uint32_t readHregAcc32(ModbusIP &mb, IPAddress &remote, const int regStart);

    /**
     * Read hreg uint32 value of length 2
     *
     * @param mb ModbusIP object reference
     * @param remote IP address of the inverter object reference
     * @param regStart Register
     * @return acc32 value
     */
    uint32_t readHregUInt32(ModbusIP &mb, IPAddress &remote, const int regStart);

    /**
     * Read hreg float32 value of length 2
     *
     * @param mb ModbusIP object reference
     * @param remote IP address of the inverter object reference
     * @param regStart Register
     * @return float32 value
     */
    float readHregFloat32(ModbusIP &mb, IPAddress &remote, const int regStart);
};