#include "ModbusSolarEdge.h"

/**
 * Calculate available sun power
 * @param i_ac_power_norm Inverter output normalized in W
 * @param b1_b_instantaneous_power Power from the battery in W
 */
int ModbusSolarEdge::calculate_sun_power(int16_t i_ac_power_norm, float b1_b_instantaneous_power) {
    // if we have no inverter output sun is not shining bright enough
    if (i_ac_power_norm <= 0) {
        return 0;
    }

    // NOTE: when the battery is loading "b1_b_instantaneous_power" is positive when unloading it is negative
    // NOTE 2: "i_ac_power_morm" contains the power used by the house + the power send to the grid but NOT the power sent to the battery BUT the power coming from the battery when unloading

    // when exporting: as the inverter output "i_ac_power_morm" already contains the power send to the grid we do not have to deal with it here
    // when importing: import from battery has to be removed from inverter output "i_ac_power_morm" as we want to have the sun power not the battery power
    i_ac_power_norm += b1_b_instantaneous_power;

    // import from battery may result in values lower 0 because of conversion losses DC > AC
    return i_ac_power_norm > 0 ? i_ac_power_norm : 0;
}

/**
 * Calculate power used by house
 * @param i_ac_power_norm Inverter output normalized in W
 * @param m1_m_ac_power Power going through the meter in W
 */
int ModbusSolarEdge::calculate_house_usage(int16_t i_ac_power_norm, int16_t m1_m_ac_power) {
    // NOTE: if we import power from the grid the meter value is negative

    // when exporting: remove the exported power from the inverters output to get the house usage
    // when importing: we have to add the imported power to the inverters output
    return i_ac_power_norm + (m1_m_ac_power * -1);
}

/**
 * Normalize value with scale factor
 * @param value value
 * @param scale factor
 */
int16_t ModbusSolarEdge::norm(int16_t value, int16_t scale_factor) {
    return value * pow(10, scale_factor);
}

/**
 * Wait for end of Modbus transaction
 * @param mb ModbusIP object reference
 * @param transaction transaction number
 */
void waitForTransaction(ModbusIP &mb, uint16_t transaction) {
    // wait exactly till got the response
    while (mb.isTransaction(transaction)) {
        mb.task();
        delay(10);
    }
}

/** Values to translate inverter status to text */
const char *ModbusSolarEdge::I_STATUS_VALUES[] = {"I_STATUS_OFF", "I_STATUS_SLEEPING", "I_STATUS_STARTING", "I_STATUS_MPPT", "I_STATUS_THROTTLED", "I_STATUS_SHUTTING_DOWN",
                                                  "I_STATUS_FAULT", "I_STATUS_STANDBY"};

/** Values to translater battery status to text */
const char *ModbusSolarEdge::B_STATUS_VALUES[] = {"Off", "Standby", "Init", "Charge", "Discharge", "Fault", "Idle"};

/**
 * Read hreg string value into a char array
 * @param mb ModbusIP object reference
 * @param remote IP address of the inverter object reference
 * @param regStart First register containing the first character(s)
 * @param length Numbers of registers to read
 * @param string Character array the string will be stored in. Must be twice the length of "length" as each 16-bit register contains 2 8-bit characters.
 */
void ModbusSolarEdge::readHregString(ModbusIP &mb, IPAddress &remote, const int regStart, const int length, char string[]) {
    uint16_t resx[length + 1];
    uint16_t transaction = mb.readHreg(remote, regStart, resx, length, nullptr, 1);
    waitForTransaction(mb, transaction);

    // convert "oSalErgd e" => "SolarEdge"
    int charPos = 0;
    for (int i = 0; i < length; i++) {
        string[charPos] = resx[i] >> 8;
        charPos++;
        string[charPos] = (resx[i] << 8) >> 8;
        charPos++;
    }
}

/**
 * Read hreg uint16 value of length 1
 *
 * @param mb ModbusIP object reference
 * @param remote IP address of the inverter object reference
 * @param regStart Register
 * @return uint value
 */
uint16_t ModbusSolarEdge::readHregUInt(ModbusIP &mb, IPAddress &remote, const int regStart) {
    uint16_t res;
    uint16_t transaction = mb.readHreg(remote, regStart, &res, 1, nullptr, 1);
    waitForTransaction(mb, transaction);
    return res;
}

/**
 * Read hreg int16 value of length 1
 *
 * @param mb ModbusIP object reference
 * @param remote IP address of the inverter object reference
 * @param regStart Register
 * @return int value
 */
int16_t ModbusSolarEdge::readHregInt(ModbusIP &mb, IPAddress &remote, const int regStart) {
    return (int16_t)readHregUInt(mb, remote, regStart);
}

/**
 * Read hreg acc32 value of length 2
 *
 * @param mb ModbusIP object reference
 * @param remote IP address of the inverter object reference
 * @param regStart Register
 * @return acc32 value
 */
uint32_t ModbusSolarEdge::readHregAcc32(ModbusIP &mb, IPAddress &remote, const int regStart) {
    uint16_t resx[2];
    uint16_t transaction = mb.readHreg(remote, regStart, resx, 2, nullptr, 1);
    waitForTransaction(mb, transaction);

    uint32_t hl = resx[0];
    uint32_t t = (hl << 16) | resx[1];
    return t;
}

/**
 * Read hreg uint32 value of length 2
 *
 * @param mb ModbusIP object reference
 * @param remote IP address of the inverter object reference
 * @param regStart Register
 * @return acc32 value
 */
uint32_t ModbusSolarEdge::readHregUInt32(ModbusIP &mb, IPAddress &remote, const int regStart) {
    uint16_t resx[2];
    uint16_t transaction = mb.readHreg(remote, regStart, resx, 2, nullptr, 1);
    waitForTransaction(mb, transaction);

    uint32_t hl = resx[1];
    uint32_t t = (hl << 16) | resx[0];
    return t;
}

/**
 * Read hreg float32 value of length 2
 *
 * @param mb ModbusIP object reference
 * @param remote IP address of the inverter object reference
 * @param regStart Register
 * @return float32 value
 */
float ModbusSolarEdge::readHregFloat32(ModbusIP &mb, IPAddress &remote, const int regStart) {
    uint16_t resx[2];
    uint16_t transaction = mb.readHreg(remote, regStart, resx, 2, nullptr, 1);
    waitForTransaction(mb, transaction);

    union f_2uint {
        float f;
        uint16_t i[2];
    };

    union f_2uint f_number;
    f_number.i[0] = resx[0];
    f_number.i[1] = resx[1];

    return f_number.f;
}

/**
 * Create a float value of 2 unsigned integers
 * credentials go to: https://industruino.com/blog/our-news-1/post/modbus-tips-for-industruino-26#blog_content
 */
float f_2uint_float_x(uint16_t uint1, uint16_t uint2) {  // reconstruct the float from 2 unsigned integers

    union f_2uint {
        float f;
        uint16_t i[2];
    };

    union f_2uint f_number;
    f_number.i[0] = uint1;
    f_number.i[1] = uint2;

    return f_number.f;
}
