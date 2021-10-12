# SolarEdge Modbus Library for ESP8266

This library is a wrapper for querying data from SolarEdge inverters.
It was created to hide some of the complexity of Modbus queries and 
to reduce the amount of code needed to display SolarEdge values in other projects.

This liberary uses [emelianov/modbus-esp8266](https://github.com/emelianov/modbus-esp8266). Thanks to [Alexander Emelianov](https://github.com/emelianov) for his great work.

Example output which shows an overview of the PV system. See [Example](Example) section for more details.

```
                      SUN
                       | (A) 315W
                       v
HOUSE <-(B) 285W - INVERTER  <-(C) -10W -> GRID
                       ^
                       | (D) 40W/11.0PCT
                       v
                    BATTERY (Charge)
```


## Features

* Provides constants for SolarEdge inverter common block values (like serial)
* Provides constants for SolarEdge inverter values (like current inverter output)
* Provides constants for meter 1 common block values (like serial)
* Provides constants for meter 1 values (like current power)
* Provides constants for battery 1 common block values (like serial)
* Provides constants for battery 1 values (like current power)
* Provides methods for reading String, uint16, int16, acc32, uint32, float32 values from the inverter
* Provides methods for calculating current sun power and house usage

## Environment

* Tested with ESP8266 on NodeMCU 1.0 and Wemos D1 mini
* Tested with SolarEdge SE7K inverter with BYD battery box
* Tested with Modbus over TCP

## Example

Here is an output of the example in "examples\ReadAllValues\ReadAllValuesExample.cpp".

```
Connecting to SSID ...
1 2 3 4

Connection established!     
IP address:     192.168.0.1
inverter common values
C_SUNSPEC_ID: 1850954613
C_SUNSPEC_DID: 1
C_SUNSPEC_LENGTH: 65
C_MANUFACTURER: SolarEdge 
C_MODEL: SE7K
C_VERSION: nnnn.nnnn.nnnn
C_SERIALNUMBER: nnnnnnn
C_DEVICEADDRESS: 1

inverter values
I_SUNSPEC_DID: 103
I_SUNSPEC_LENGTH: 50
I_AC_CURRENT: 265
I_AC_CURRENT_A: 88
I_AC_CURRENT_B: 90
I_AC_CURRENT_C: 86
I_AC_CURRENT_SF: -2
I_AC_VOLTAGEAB: 4122
I_AC_VOLTAGEBC: 4107
I_AC_VOLTAGECA: 4110
I_AC_VOLTAGEAN: 2381
I_AC_VOLTAGEBN: 2367
I_AC_VOLTAGECN: 2377
I_AC_VOLTAGE_SF: -1
I_AC_POWER: 27700
I_AC_POWER_SF: -2
I_AC_FREQUENCY: 5001
I_AC_FREQUENCY_SF: -2
I_AC_VA: 6301
I_AC_VA_SF: -1
I_AC_VAR: -5660
I_AC_VAR_SF: -1
I_AC_PF: 4379
I_AC_PF_SF: -2
I_AC_ENERGY_WH: 599907
I_AC_ENERGY_WH_SF: 0
I_DC_CURRENT: 3422
I_DC_CURRENT_SF: -4
I_DC_VOLTAGE: 8157
I_DC_VOLTAGE_SF: -1
I_DC_POWER: 27918
I_DC_POWER_SF: -2
I_TEMP_SINK: 3700
I_TEMP_SF: -2
I_STATUS: 4
I_STATUS as text: I_STATUS_THROTTLED
I_STATUS_VENDOR: 0

meter 1 common values
M1_C_MANUFACTURER: SolarEdge
M1_C_MODEL: SE-MTR-3Y-400V-A
M1_C_OPTION: Export+Import
M1_C_VERSION: 74
M1_C_SERIALNUMBER: nnnnnnnn

meter 1 values
M1_AC_POWER: -8
M1_AC_POWER_SF: 0
M1_EXPORTED: 301644
M1_IMPORTED: 184733

battery 1 common values
B1_MANUFACTURER_NAME: 48V_BYD
B1_MODEL: BYD Premium LVS 8.0
M1_C_OPTION: Export+Import
B1_FIRMWARE_VERSION: 48V DCDC n.n.nn BMS 0.0.0
B1_SERIAL_NUMBER: nnnnnnn

battery 1 values
B1_INSTANTANEOUS_POWER: 40
B1_STATE_OF_HEALTH_SOH: 100
B1_STATE_OF_ENERGY_SOE: 11
B1_STATUS: 3
B1_STATUS as text: Charge

system overview
                    SUN
                     | (A) 315W
                     v
   HOUSE <-(B) 285W - INVERTER  <-(C) -10W -> GRID
                     ^
                     | (D) 40W/11.000000PCT
                     v
                  BATTERY (Charge)

```

## Building

This library was created using [PlatformIO](https://platformio.org/) for [Visual Studio Code](https://code.visualstudio.com/).

To build the example with PlatformIO use the following steps:

* clone the repository from GitHub to your workspace
* move ReadAllValueExamples.cpp from /examples/ReadAllValues to /src
* modify ReadAllValueExamples.cpp; change the variables ssid, password, remote and port to match your environment
* compile and upload


## Last Changes

* first release pending, still work in progress

## License

The code in this repo is licensed under the BSD New License. See LICENSE.txt for more info.