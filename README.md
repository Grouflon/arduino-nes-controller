arduino-nes-controller
======================

Transform your Arduino Uno and NES controller into a USB keyboard
![arduino-nes-controller](http://dev.uselessworks.com/images/arduino-nes.jpg)

Setup
======================

For making this work you need :
- An Arduino (so far it has only been tested with the Arduino Uno R3, feel free to give me feedback about other models).
- A NES controller that you are ready to sacrifice to this cause.


Wiring
----------------------

Pull the wires out of the controller's connector and plug them into the Arduino like this :

	White	-> 5V
	Brown	-> Ground
	Orange	-> Digital 2
	Red		-> Digital 3
	Yellow	-> Digital 4

Usage
----------------------

At the very top of the nes.ino script, you will find is a list of constants
.

	const int AKey = 27;         // X
	const int BKey = 6;          // C
	const int SELECTKey = 40;    // ENTER
	const int STARTKey = 40;     // ENTER
	const int UPKey = 82;        // UP ARROW
	const int DOWNKey = 81;      // DOWN ARROW
	const int LEFTKey = 80;      // LEFT ARROW
	const int RIGHTKey = 79;     // RIGHT ARROW

This is where you should define what keys will be triggered by the buttons of the NES controller.
You can find the list of the different keycodes corresponding to each key on [this document](http://www.usb.org/developers/devclass_docs/Hut1_11.pdf), page 53


Updating firmware
----------------------

>It seems that not all Arduino Unos can be updated natively, some will require to solder a 10k resistor at the back of the board, refer to the documentation if you have any doubt on your model.

The two firmwares you need for this operation are in the firmwares/ folder.

For making the Arduino act as a keyboard you will need to change its firmware, don't worry, the process is easy, reversible entirely documented [on the Arduino documentation](http://arduino.cc/en/Hacking/DFUProgramming8U2#.UytV5_l5MWs).



Depending on what you want to do, you will have to switch between the two firmwares, you cannot use the arduino as a keyboard while the serial firmware is loaded, and cannot upload your script to the arduino while the HID keyboard firmware is loaded.
Here is the process to upload a new firmware :
- Plug your Arduino on your computer as usual.
- Reset the 8u2 (Bridge the reset pins as described in the Arduino doc).
- Upload your firmware using the technique correponding to your OS (see Arduino doc).
- Unplug and plug the Arduino again to leave reset mode and activate the new firmware.

Once you are comfortable with this operation, the process is very simple :
- Put the serial firmware on your Arduino if it's not already done.
- Upload src/nes.ino to your Arduino.
- Switch to the HID Keyboard firmware.
- Profit !



Feel free to use, share, or modify this code !  
Feel also free to give me feedback and propose improvements.


References, help and documentation
======================
- [Arduino UNO Keyboard HID version 0.3 by darran](http://hunt.net.nz/users/darran/weblog/b3029/Arduino_UNO_Keyboard_HID_version_03.html)
- [Arduino USB HID Keyboard](http://mitchtech.net/arduino-usb-hid-keyboard/)
- [The NES Controller Handler](http://www.mit.edu/~tarvizo/nes-controller.html)
- [Nintendo Controller / NES Controller for Arduino](http://forum.arduino.cc/index.php/topic,8481.0.html)
