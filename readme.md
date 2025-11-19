# Env setup

1. Install library from origional factory repo https://github.com/Xinyuan-LilyGO/T-Dongle-ESP32S2/tree/main
2. Install ESP32 board, V2.0.17. Don't install the latest.

# Image converter

https://notisrac.github.io/FileToCArray/

1. Palette mod 16 bit RRRRRGGGGGGBBBBB(2byte/px)
2. Data type uint16_t
3. Resize 240 x 135

# Before flashing

Remove plastic cover, hold boot, press reset once to enter download mode.
In Tools menu of Arduino IDE, Enable USB CDC On Boot to use Serial print function.