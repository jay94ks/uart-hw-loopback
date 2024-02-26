## UART hardware loopback.
This hardware causes `UART` to loop back at the hardware level.
Developed based on the `STM32F042` and `CH340` chips, 
it taps the serial communication of the target software 
using the `baud-rate` auto-negotiation function of `VCP`.

In addition, since the pins of the 'SL2.1A' chip are left, 
so I added the USB hub function to utilize them.
and 'PD (Power Delivery)' input in case the current is insufficient.

## How to connect:
Note that, currently, 
firmware for `STM32F042` and `tapping software` are work in progress yet,
these will be available after few days.

### Requirements:
1. UART hardware loopback board with `USB Type-C` cable.
2. Target hardware and software.
3. This tapping software.

### Steps to configure the hardware:
1. Connect the data cable, `USB Type-C` to your PC,
2. Attach a `COM` port of `F042VCP` to target software.
3. Then, attach a `COM` port of `CH340` to this tapping software.
4. And, configure this tapping software to communicate with the target hardware.