# Quickstart

1. Download the [Microchip ATtiny Series Device Support](packs.download.microchip.com) and unzip the .tar folder somewhere on your computer.
2. Set the environment variable `ATTINY_DFP_PATH` to the path of the unzipped tar. The `/gcc` and `/include` folders must be immediately under this variable (check using `ls $ATTINY_DFP_PATH` and confirm you see the `/gcc` and `/include` folders.
3. Set the jtag2udpi device port (the port of the arduino running jtag2updi most likely) in the `ARDUINO_COM_PORT` environment variable
4. run `make`
5. run `make flash`

