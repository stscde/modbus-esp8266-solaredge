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

const int C_SUNSPEC_DID = 40002;     // uint16, size 1, Sunspec Common Model Block identification
const int C_SUNSPEC_LENGTH = 40003;  // uint16, size 1, number of 16-bit registers, 65

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

const int I_SUNSPEC_DID = 40069;      // uint16, size 1, phases, 101 = single, 102 = split, 103 = three
const int I_SUNSPEC_LENGTH = 40070;   // uint16, size 1, model block length, 50
const int I_AC_CURRENT = 40071;       // uint16, size 1, Amps, AC total current value
const int I_AC_CURRENT_A = 40072;     // uint16, size 1, Amps, AC phase A current value
const int I_AC_CURRENT_B = 40073;     // uint16, size 1, Amps, AC phase B current value
const int I_AC_CURRENT_C = 40074;     // uint16, size 1, Amps, AC phase C current value
const int I_AC_CURRENT_SF = 40075;    // int16, size 1, AC current scale factor
const int I_AC_VOLTAGEAB = 40076;     // uint16, size 1, Volts, AC Voltage phase AB value
const int I_AC_VOLTAGEBC = 40077;     // uint16, size 1, Volts, AC Voltage phase BC value
const int I_AC_VOLTAGECA = 40078;     // uint16, size 1, Volts, AC Voltage phase CA value
const int I_AC_VOLTAGEAN = 40079;     // uint16, size 1, Volts, AC Voltage phase A to N value
const int I_AC_VOLTAGEBN = 40080;     // uint16, size 1, Volts, AC Voltage phase B to N value
const int I_AC_VOLTAGECN = 40081;     // uint16, size 1, Volts, AC Voltage phase C to N value
const int I_AC_VOLTAGE_SF = 40082;    // int16, size 1, Volts, AC Voltage scale factor
const int I_AC_POWER = 40083;         // int16, size 1, Watts, AC power value
const int I_AC_POWER_SF = 40084;      // int16, size 1, AC power scale factor
const int I_AC_FREQUENCY = 40085;     // uint16, size 1, Hertz, AC frequency
const int I_AC_FREQUENCY_SF = 40086;  // int16, size 1, AC frequency scale factor
const int I_AC_VA = 40087;            // int16, size 1, VA, apparent power (Scheinleistung)
const int I_AC_VA_SF = 40088;         // int16, size 1, scale factor
const int I_AC_VAR = 40089;           // int16, size 1, VAR, reactive power
const int I_AC_VAR_SF = 40090;        // int16, size 1, VAR, reactive power scale factor
const int I_AC_PF = 40091;            // int16, size 1, %, power factor
const int I_AC_PF_SF = 40092;         // int16, size 1, power factor scale factor
const int I_AC_ENERGY_WH = 40093;     // acc32, size 2, WattHours, AC lifetime energy production
const int I_AC_ENERGY_WH_SF = 40095;  // uint16, size 1, Volts, AC lifetime energy production scale factor
const int I_DC_CURRENT = 40096;       // uint16, size 1, Amps, DC current value
const int I_DC_CURRENT_SF = 40097;    // int16, size 1, DC current scale factor
const int I_DC_VOLTAGE = 40098;       // uint16, size 1, Volts, DC voltage value
const int I_DC_VOLTAGE_SF = 40099;    // int16, size 1, DC voltage scale factor
const int I_DC_POWER = 40100;         // int16, size 1, Watts, DC power value
const int I_DC_POWER_SF = 40101;      // int16, size 1, DC power scale factor
const int I_TEMP_SINK = 40103;        // int16, size 1, degrees Celsius, Heat sink temperature
const int I_TEMP_SF = 40106;          // int16, size 1, Heat sink temperature scale factor
const int I_STATUS = 40107;           // uint16, size 1, Operating State
const int I_STATUS_VENDOR = 40108;    // uint16, Vendor defined operating state. See SolarEdge install guide.

// ##################################################################
// MODBUS Mapping Meter 1
// see "sunspec-implementation-technical-note.pdf"
// ##################################################################

const int M1_C_SUNSPEC_DID = 40121;        // uint16, size 1, id for this SunSpec common model block
const int M1_C_SUNSPEC_LENGTH = 40122;     // uint16, size 1, length of block in registers, should be 65
const int M1_C_MANUFACTURER = 40123;       // String(32), size 16, meter manufacturer
const int M1_C_MANUFACTURER_SIZE = 16;     // manufacturer name register count
const int M1_C_MODEL = 40139;              // String(32), size 16, meter model
const int M1_C_MODEL_SIZE = 16;            // model name register count
const int M1_C_OPTION = 40155;             // String(16), size 8, export + import, production, consumption
const int M1_C_OPTION_SIZE = 8;            // options register count
const int M1_C_VERSION = 40163;            // String(16), size 8, meter version
const int M1_C_VERSION_SIZE = 8;           // meter version register count
const int M1_C_SERIALNUMBER = 40171;       // String(32), size 16, meter serial number
const int M1_C_SERIALNUMBER_SIZE = 16;     // meter serial number register count
const int M1_C_DEVICEADDRESS = 40187;      // uint16, size 1, inverter Modbus ID
const int M1_ID_C_SUNSPEC_DID = 40188;     // uint16, size 1, See pdf for details.
const int M1_ID_C_SUNSPEC_LENGTH = 40189;  // uint16, size 1, registers, length of meter model block
const int M1_M_AC_CURRENT = 40190;         // int16, size 1, Amps, AC current (sum of active phases)
const int M1_AC_CURRENT_A = 40191;         // int16, size 1, Amps, phase A AC current
const int M1_AC_CURRENT_B = 40192;         // int16, size 1, Amps, phase B AC current
const int M1_AC_CURRENT_C = 40193;         // int16, size 1, Amps, phase C AC current
const int M1_AC_CURRENT_SF = 40194;        // int16, size 1, AC current scale factor
const int M1_AC_VOLTAGE_LN = 40195;        // int16, size 1, Volts, line to neutral ac voltage (average of active phases)
const int M1_AC_VOLTAGE_AN = 40196;        // int16, size 1, Volts, phase A to neutral ac voltage
const int M1_AC_VOLTAGE_BN = 40197;        // int16, size 1, Volts, phase B to neutral ac voltage
const int M1_AC_VOLTAGE_CN = 40198;        // int16, size 1, Volts, phase c to neutral ac voltage
const int M1_AC_VOLTAGE_LL = 40199;        // int16, size 1, Volts, line to line AC voltage (avererage of active phases)
const int M1_AC_VOLTAGE_AB = 40200;        // int16, size 1, Volts, phase A to phase B AC voltage
const int M1_AC_VOLTAGE_BC = 40201;        // int16, size 1, Volts, phase B to phase C AC voltage
const int M1_AC_VOLTAGE_CA = 40202;        // int16, size 1, Volts, phase C to phase A AC voltage
const int M1_AC_VOLTAGE_SF = 40203;        // int16, size 1, AC voltage scale factor
const int M1_AC_FREQ = 40204;              // int16, size 1, Herts, AC voltage frequency
const int M1_AC_FREQ_SF = 40205;           // int16, size 1, AC frequency scale factor
const int M1_AC_POWER = 40206;             // int16, size 1, Watts, total real power (sum of active phases)
const int M1_AC_POWER_A = 40207;           // int16, size 1, Watts, phase A AC real power
const int M1_AC_POWER_B = 40208;           // int16, size 1, Watts, phase B AC real power
const int M1_AC_POWER_C = 40209;           // int16, size 1, Watts, phase C AC real power
const int M1_AC_POWER_SF = 40210;          // int16, size 1, SF, AC real power scale factor
const int M1_AC_VA = 40211;                // int16, size 1, Volt-Amps, total AC apparent power (sum of active phases)
const int M1_AC_VA_A = 40212;              // int16, size 1, Volt-Amps, phase A AC apparent power
const int M1_AC_VA_B = 40213;              // int16, size 1, Volt-Amps, phase B AC apparent power
const int M1_AC_VA_C = 40214;              // int16, size 1, Volt-Amps, phase C AC apparent power
const int M1_AC_VA_SF = 40215;             // int16, size 1, SF, AC apparent power scale factor
const int M1_AC_VAR = 40216;               // int16, size 1, VAR, total AC reactive power (sum of active phases)
const int M1_AC_VAR_A = 40217;             // int16, size 1, VAR, phase A AC reactive power
const int M1_AC_VAR_B = 40218;             // int16, size 1, VAR, phase B AC reactive power
const int M1_AC_VAR_C = 40219;             // int16, size 1, VAR, phase C AC reactive power
const int M1_AC_VAR_SF = 40220;            // int16, size 1, SF, AC reactive power scale factor
const int M1_AC_PF = 40221;                // int16, size 1, %, Average power factor (average of active phases)
const int M1_AC_PF_A = 40222;              // int16, size 1, %, phase A power factor
const int M1_AC_PF_B = 40223;              // int16, size 1, %, phase B power factor
const int M1_AC_PF_C = 40224;              // int16, size 1, %, phase C power factor
const int M1_AC_PF_SF = 40225;             // int16, size 1, SF, AC power factor scale factor
const int M1_EXPORTED = 40226;             // uint32, size 2, Watt-hours, total exported real energy
const int M1_EXPORTED_A = 40228;           // uint32, size 2, Watt-hours, phase A exported real energy
const int M1_EXPORTED_B = 40230;           // uint32, size 2, Watt-hours, phase B exported real energy
const int M1_EXPORTED_C = 40232;           // uint32, size 2, Watt-hours, phase C exported real energy
const int M1_IMPORTED = 40234;             // uint32, size 2, Watt-hours, total imported real energy
const int M1_IMPORTED_A = 40236;           // uint32, size 2, Watt-hours, phase A imported real energy
const int M1_IMPORTED_B = 40238;           // uint32, size 2, Watt-hours, phase B imported real energy
const int M1_IMPORTED_C = 40240;           // uint32, size 2, Watt-hours, phase C imported real energy
const int M1_ENERGY_W_SF = 40242;          // int16, size 1, SF, real energy scale factor
const int M1_EXPORTED_VA = 40243;          // uint32, size 2, VA-hours, total exported apparent energy
const int M1_EXPORTED_VA_A = 40245;        // uint32, size 2, VA-hours, phase A exported apparent energy
const int M1_EXPORTED_VA_B = 40247;        // uint32, size 2, VA-hours, phase B exported apparent energy
const int M1_EXPORTED_VA_C = 40249;        // uint32, size 2, VA-hours, phase C exported apparent energy
const int M1_IMPORTED_VA = 40251;          // uint32, size 2, VA-hours, total imported apparent energy
const int M1_IMPORTED_VA_A = 40253;        // uint32, size 2, VA-hours, phase A imported apparent energy
const int M1_IMPORTED_VA_B = 40255;        // uint32, size 2, VA-hours, phase B imported apparent energy
const int M1_IMPORTED_VA_C = 40257;        // uint32, size 2, VA-hours, phase C imported apparent energy
const int M1_ENERGY_VA_SF = 40259;         // int16, size 1, SF, apparent energy scale factor
const int M1_IMPORT_VARH_Q1 = 40260;       // uint32, size 2, VAR-hours, quadrant 1: total imported reactive energy
const int M1_IMPORT_VARH_Q1A = 40262;      // uint32, size 2, VAR-hours, phase A-quadrant 1: imported reactive energy
const int M1_IMPORT_VARH_Q1B = 40264;      // uint32, size 2, VAR-hours, phase B-quadrant 1: imported reactive energy
const int M1_IMPORT_VARH_Q1C = 40266;      // uint32, size 2, VAR-hours, phase C-quadrant 1: imported reactive energy
const int M1_IMPORT_VARH_Q2 = 40268;       // uint32, size 2, VAR-hours, quadrant 2: total imported reactive energy
const int M1_IMPORT_VARH_Q2A = 40270;      // uint32, size 2, VAR-hours, phase A-quadrant 2: imported reactive energy
const int M1_IMPORT_VARH_Q2B = 40272;      // uint32, size 2, VAR-hours, phase B-quadrant 2: imported reactive energy
const int M1_IMPORT_VARH_Q2C = 40274;      // uint32, size 2, VAR-hours, phase C-quadrant 2: imported reactive energy
const int M1_EXPORT_VARH_Q3 = 40276;       // uint32, size 2, VAR-hours, quadrant 3: total exported reactive energy
const int M1_EXPORT_VARH_Q3A = 40278;      // uint32, size 2, VAR-hours, phase A-quadrant 3: exported reactive energy
const int M1_EXPORT_VARH_Q3B = 40280;      // uint32, size 2, VAR-hours, phase B-quadrant 3: exported reactive energy
const int M1_EXPORT_VARH_Q3C = 40282;      // uint32, size 2, VAR-hours, phase C-quadrant 3: exported reactive energy
const int M1_EXPORT_VARH_Q4 = 40284;       // uint32, size 2, VAR-hours, quadrant 4: total exported reactive energy
const int M1_EXPORT_VARH_Q4A = 40286;      // uint32, size 2, VAR-hours, phase A-quadrant 4: exported reactive energy
const int M1_EXPORT_VARH_Q4B = 40288;      // uint32, size 2, VAR-hours, phase B-quadrant 4: exported reactive energy
const int M1_EXPORT_VARH_Q4C = 40290;      // uint32, size 2, VAR-hours, phase C-quadrant 4: exported reactive energy
const int M1_ENERGY_VAR_SF = 40292;        // int16, size 1, SF, reactive energy scale factor
const int M1_EVENTS = 40293;               // uint32, size 2, Flags, See M_EVENT_ flags. 0 = nts.

// ##################################################################
// MODBUS Mapping Battery 1
// see "Power Control Open Protocol for SolarEdge Inverters.pdf" (page 19)
// ##################################################################

const int B1_MANUFACTURER_NAME = 57600;               // String(32), size 16
const int B1_MANUFACTURER_NAME_SIZE = 16;             // String(32), size 16
const int B1_MODEL = 57616;                           // String(32), size 16
const int B1_MODEL_SIZE = 16;                         // model number register count
const int B1_FIRMWARE_VERSION = 57632;                // String(32), size 16
const int B1_FIRMWARE_VERSION_SIZE = 16;              // String(32), size 16
const int B1_SERIAL_NUMBER = 57648;                   // String(32), size 16
const int B1_SERIAL_NUMBER_SIZE = 16;                 // serial number register count
const int B1_DEVICE_ID = 57664;                       // uint16, size 1
const int B1_RATED_ENERGY = 57666;                    // float32, size 2, Watt-hours
const int B1_MAX_CHARGE_CONTINUES_POWER = 57668;      // float32, size 2, Watts
const int B1_MAX_DISCHARGE_CONTINUES_POWER = 57670;   // float32, size 2, Watts
const int B1_MAX_CHARGE_PEAK_POWER = 57672;           // float32, size 2, Watts
const int B1_MAX_DISCHARGE_PEAK_POWER = 57674;        // float32, size 2, Watts
const int B1_AVERAGE_TEMPERATURE = 57708;             // float32, size 2, degrees C
const int B1_MAX_TEMPERATURE = 57710;                 // float32, size 2, degrees C
const int B1_INSTANTANEOUS_VOLTAGE = 57712;           // float32, size 2, Volts
const int B1_INSTANTANEOUS_CURRENT = 57714;           // float32, size 2, Amps
const int B1_INSTANTANEOUS_POWER = 57716;             // float32, size 2, Watt
const int B1_LIFETIME_EXPORT_ENERGY_COUNTER = 57718;  // uint64, size 4, Watt-hours
const int B1_LIFETIME_IMPORT_ENERGY_COUNTER = 57722;  // uint64, size 4, Watt-hours
const int B1_MAX_ENERGY = 57726;                      // float32, size 2, Watt-hours
const int B1_AVAILABLE_ENERGY = 57728;                // float32, size 2, Watt-hours
const int B1_STATE_OF_HEALTH_SOH = 57730;             // float32, size 2, N/A
const int B1_STATE_OF_ENERGY_SOE = 57732;             // float32, size 2, N/A
const int B1_STATUS = 57734;                          // uint32, size 2, 0-7
const int B1_STATUS_INTERNAL = 57736;                 // uint32, size 2, vendor-defined status codes
const int B1_EVENTS_LOG = 57738;                      // uint16[8], size 8, Battery vendors last fault ID
const int B1_EVENTS_LOG_INTERNAL = 57746;             // uint16[8], size 8

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

    /** Values to translater battery status to text */
    static const char *B_STATUS_VALUES[];

    /** Values to translate inverter status to text */
    static const char *I_STATUS_VALUES[];
};