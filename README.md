# Chiisho [Pocket Dictionary]
The Chiisho is a portable, pocket dictionary programmed on the Sony SPRESENSE board. It's capabilities include word lookup [in progress], sentence translation [in progress], and [to be decided]. It's input method is [to be decided, technical difficulties have changed our design intent]. 

https://github.com/LandenParke/PocketDictionary

## Installation
To use the application first install the Sony SPRESENSE SDK for CLI. The following step by step can help.
https://developer.spresense.sony-semicon.com/development-guides/?page=sdk_set_up&lang=en#
Once the source code is installed run the following command to create the *nuttx.spk* and then use the following to flash to the board and to open the uart terminal.
```console
tools/flash.sh -c /dev/ttyUSB0 -b 500000 nuttx.spk
tools/flash.sh -c /dev/ttyUSB0 -b 500000 nuttx.spk
```
Once flashed run the command [To be decided] in the terminal to start the program.
