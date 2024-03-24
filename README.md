# NUMicro-8051-prog

This derived from Gregory McGarry's work here: https://github.com/gmcgarry/nuvoprog

This currently only supports the N76E003, but it could be extended to other Nuvoton 8051 chips, like the MS51FB9AE ([see here](https://github.com/vladimir-dudnik/MS51FB9AE-pgm-rpi)).

This provides the following packages:

- nuvoicp: N76E003 ICP library
- nuvoicpy: Python bindings and command-line tool for nuvoicp (for Raspberry Pi Only)
- nuvoispy: Python library and command-line tool for ISP programming
- bootloader: Custom ISP LDROM bootloader with extended ISP commands


### build requirements:
- sdcc
- makebin (usually included with sdcc)
- packihx (usually included with sdcc)
- make
- gcc
- pigpio
- libgpiod
- python3
- python3-pip
- Arduino IDE (if building nuvoicp for Arduino)

On Debian and Ubuntu systems, these can all be installed by running:
```
sudo apt install sdcc build-essential pigpio libgpiod-dev python3 python3-pip arduino
```

### Raspberry Pi 5 note

If you plan to use the ICP programmer with the Pi 5, ensure that `pcie_aspm=off` is added to `/boot/firmware/cmdline.txt`. This will increase power consumption if you are using an NVME drive, but this will ensure that there are no random delays added to GPIO ops which will result in a failed flash write.

## nuvoicp

C Library for programming Nuvoton 8051 chips with the ICP protocol.

This is designed for both the Raspberry Pi and Arduino targets.

This could possibly be repurposed for other SBCs with the appropriate GPIO, but this requires implementing a device file for the GPIO (look at `n51_pgm.h` for what you would have to implement, and `rpi.c`, `rpi-pigpio.c`, and `arduino.cpp` for reference implementations). 

The Raspberry Pi version can be compiled linked with either pigpio or libgpiod.
pigpio was added primarily because it has around 10x lower latency than libgpiod, which is useful for glitching attacks.
Note: pigpio only supports Pi 4 and lower, Pi 5 can only be used with libgpiod.

The Arduino version provides a sketch that implements the Nuvoton ISP protocol and acts like an ISP-to-ICP bridge. This way, you can take advantage of the programming functionality only provided by ICP (mass-erase, read flash, LDROM programming, etc.) while still using standard ISP tools. It can be used with either standard Nuvoton ISP programming tools, or it can be used with `nuvoispy` to take advantage of the extended commands (e.g. programming the LDROM, mass erase).

### Build

#### Raspberry Pi:

For libgpiod:
```bash
make -f Makefile.rpi
```

For pigpio:
```bash
USE_PIGPIO=1 make -f Makefile.rpi
```

For Arduino, use the Arduino IDE and open the `nuvoicp.ino` file, then upload to your Arduino.
By default, it uses GPIO pins 11 (DAT), 12 (CLK), and 13 (RESET) for the ICP interface, but this can be changed in the `arduino.cpp` file.

### Usage

When using a Raspberry Pi, it is recommended to use the nuvoicpy CLI (see below); the C `nuvoicp` CLI is deprecated and is only kept around as an example of how to use the library in C/C++.

When using an Arduino, use `nuvoispy`, see below.

## nuvoicpy

These are python bindings for the Raspberry Pi compiled versions of nuvoicp. It also provides a command-line ICP programmer.

This is compatible with both pigpio and libgpiod, and can be changed at runtime by passing the library name in to the NuvoICP constructor.

NOTE: If you want to run nuvoprogpy with pigpio, you have to either run python as root, or set the following on your python binary:
```bash
sudo chgrp kmem $non_syslink_python_binary_path
sudo setcap cap_sys_rawio,cap_dac_override+eip $non_syslink_python_binary_path
```
and make sure that you are in the `kmem` group.

### Build:

Just run `pip install -e .` in the root directory of this repository. This will also automatically build both versions of `nuvoicp` library for the Raspberry Pi and install them.

### Usage:

When using the command-line tool, run `python -m nuvoprogpy.nuvoicpy <commands>`:
```
nuvoicpy, a RPi ICP flasher for the Nuvoton N76E003
written by Nikita Lita

Usage:
        [-h, --help:                       print this help]
        [-u, --status:                     print the connected device info and configuration and exit
                If -c is specified, it will also write it to the specified config file.]
        [-r, --read=<filename>             read entire flash to file]
        [-w, --write=<filename>            write file to APROM/entire flash (if LDROM is disabled)]
        [-l, --ldrom=<filename>            write file to LDROM]
        [-k, --lock                        lock the chip after writing]
        [-c, --config <filename>           use config file for writing (overrides -b and -k)]
        [-s, --silent                      silence all output except for errors]
Pinout:

                           40-pin header J8
 connect 3.3V of MCU ->    3V3  (1) (2)  5V
                                 [...]
                               (35) (36) GPIO16 <- connect TRIGGER (optional)
        connect CLK ->  GPIO26 (37) (38) GPIO20 <- connect DAT
        connect GND ->     GND (39) (40) GPIO21 <- connect RST

                            ________
                           |   USB  |
                           |  PORTS |
                           |________|

Please refer to the 'pinout' command on your RPi
```

When using the Python library directly, use the `NuvoICP` class in the `nuvoprogpy.nuvoicpy` module.

### nuvoispy

This is a python library and command-line tool for programming the APROM with the ISP protocol.

This is compatible with the official N76E003 ISP ROM, and is ALSO compatible with the Arduino-built versions of `nuvoicp`, which implement the ISP protocol.

NOTE: Right now, the two Python packages are joined together in the `nuvoprogpy` package because they share functionality; this currently requires having both libgpiod and pigpiod installed regardless of whether or not you are going to use `nuvoicpy`. If anyone has ideas on how to seperate these elegantly, let me know.

#### Build:

Just run `pip -e install .`

#### Usage:

When using the command-line tool, run `python -m nuvoprogpy.nuvoispy <commands>`:
```
nuvoispy, an ISP flasher for the Nuvoton N76E003
written by Steve Markgraf <steve@steve-m.de>

Usage:
        -h, --help:                       print this help
        -p, --port=<port>                 serial port to use (default: /dev/ttyACM0 on *nix, COM1 on windows)
        -b, --baud=<baudrate>             baudrate to use (default: 115200)
        -u, --status:                     print the connected device info and configuration and exit.
        -r, --read=<filename>             read entire flash to file
        -w, --write=<filename>            write file to APROM
        -l, --ldrom=<filename>            write file to LDROM (Supported only when using Arduino ISP-to-ICP bridge)
        -n, --no-ldrom                    Overwrite LDROM space with full-size APROM (Supported only when using Arduino ISP-to-ICP bridge)
        -k, --lock                        lock the chip after programming (default: False)
        -c, --config <filename>           use config file for writing (overrides --lock)
        -s, --silent                      silence all output except for errors
```

## bootloader

This bootloader behaves like the standard Nuvoton ISP LDROM with extended functionality. It can be used with either the standard Nuvoton ISP tools, or with `nuvoispy` to take advantage of the extended commands (e.g. reading the flash contents and additional device read commands).

### Build:
Just run `make` in the bootloader directory

### Usage:
Program it as an LDROM with the icp tools below. Then, you can use either the standard Nuvoton ISP tools or nuvoispy to program the APROM.
