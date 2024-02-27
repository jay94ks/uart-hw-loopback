## UART hardware loopback.
This hardware causes `UART` to loop back at the hardware level.
Developed based on the `STM32F042` and `CH340` chips, 
it taps the serial communication of the target software 
using the `baud-rate` auto-negotiation function of `VCP`.

In addition, since the pins of the 'SL2.1A' chip are left, 
so I added the USB hub function to utilize them.
and 'PD (Power Delivery)' input in case the current is insufficient.

### Hardware:
![Hardware](https://github.com/jay94ks/uart-hw-loopback/blob/main/hardware/UARTmonitor-SMT.jpg)

### Schematic:
![Schematic](https://github.com/jay94ks/uart-hw-loopback/blob/main/hardware/UARTmonitor.png)

## How to connect:
### Requirements:
1. UART hardware loopback board with `USB Type-C` cable.
2. Target hardware and software.
3. This tapping software.

### Steps to configure the hardware:
1. Connect the data cable, `USB Type-C` to your PC,
2. Attach a `COM` port of `F042VCP` to target software.
3. Then, attach a `COM` port of `CH340` to this tapping software.
4. And, configure this tapping software to communicate with the target hardware.

## Flashing the firmware:
~~This board's `SL2.1A` USB hub chip seems like that disable the SWD pins.
(This seems to be a problem that occurs when the DP/DM pins wired on the board activate DFU mode or probe-like something)~~
So, you can flash the `F042F6P6` chip like:

### Set-up pull resistor to `BOOT0`.
This enables `ST-Link` SWD pins. if `BOOT0` pin is floating, the chip will never enable `DFU` or `SWD` pins.
* `BOOT0` -> pull down: enables `SWD`.
* `BOOT0` -> pull up: enables `DFU`.

### Using development board prototype.
Solder the `F042F6P6` chip to development board or use non-solder programming tools, and flash your chip, then re-solder it to this board. 

### `USB DFU` mode.
Initially, the `F042F6P6` chip will be booted in DFU mode.

1. download `DfuSe` tool from ST microelectronics website:
    https://www.st.com/content/my_st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-stm32080.license=1635064983409.product=STSW-STM32080.version=3.0.6.html#get-software

2. install it and goto `[System drive]:\Program Files (x86)\STMicroelectronics\Software\DfuSe v3.0.6\Bin` using explorer.

3. double click `DfuFileMgr.exe`
4. check first option, `I want to GENERATE a DFU file from S19, HEX or BIN files` then click `next`.
5. put `DF11` to `Product ID` field.
6. click `S19 or Hex...` button then, select your built `HEX` file, and click `Generate`.
7. close `DFU File Manager` tool, and double click `DfuSeDemo.exe` file.
8. select `STM device in DFU mode` from `Available DFU Devices` combo box.
9. click `Choose...` button on `Upgrade or Verify Action` panel.
10. select `DFU` file that generated at 6th process, then click `Upgrade`.
11. finally, click `Leave DFU mode` on `Available DFU Devices` panel.
12. unplug your board and re-plug it.
13. done.