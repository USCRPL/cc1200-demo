# CC1200 Demo Project
This project does some basic radio sending and receiving using the [CC1200 driver](https://github.com/mbed-ce/cc1200-driver) and Mbed OS Community Edition.  Use it as an example or a starting place for your own projects!

Two demos are included with this project: 
- CC1200Demo shows how to configure the radios and send data between them.  This demo uses several sets of configuration settings (symbol rate, filter bandwidth, etc) taken from TI's SmartRF application, since these combinations are known to work well.
- CC1200MorseDemo shows how to use the CC1200 to send Morse code.  The driver's advanced capabilities are used to reconfigure the CC1200 for operation in on-off-mode at an extremely low binary symbol rate.

## What you need:
- Two CC1200 radios, either the [dev kit daughterboards](https://www.ti.com/tool/CC1200EMK-868-930#order-start-development) or a custom PCB.
  - Note: Make sure to get a radio board matching the frequency you want to use!  e.g. if you are in Europe you may want the 430MHz version for license free operation.
  - However, this demo is only set for 900MHz operation, so you'll have to change the settings yourself to match the hardware.
- Any Mbed board with SPI support

## How to run this demo:

1. Clone it to your machine.  Don't forget to use `--recursive` to clone the submodules: `git clone --recursive https://github.com/mbed-ce/cc1200-demo.git`
2. Set up the GNU ARM toolchain (and other programs) on your machine using [the toolchain setup guide](https://github.com/mbed-ce/mbed-os/wiki/Toolchain-Setup-Guide).
3. Set up the CMake project for editing.  We have three ways to do this:
    - On the [command line](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-Command-Line)
    - Using the [CLion IDE](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-CLion)
    - Using the [VS Code IDE](https://github.com/mbed-ce/mbed-os/wiki/Project-Setup:-VS-Code)
4. Connect the two radios to the Mbed board.
5. Update CC1200DemoPins.h to fill in the pins you are using in your setup.  Then, comment the warning at the top.
6. Build the `flash-CC1200Demo` or `flash-CC1200MorseDemo` targets to upload the code to a connected device.
7. Open a serial monitor and use the menus to test your radio

## RF Warning
License free transmission on the 900MHz band is only legal in Region 2 countries (North and South America).  If you are not in a Region 2 country, you must change the demo to run on a legal frequency band before running it!  As always, make sure to follow all local regulations covering radio transmissions.