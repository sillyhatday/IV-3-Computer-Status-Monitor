INSERT DECENT PHOTO

## Preface

This project is long overdue an update. I avoided doing anything with it due to me not being happy with it. That was due to lack of experience in electronics and coding. I've archived the original readme as I find it interesting how my ideas and troubleshooting has changed in that time. There is a lot of wrong information in it. I do not doubt that this will also contain errors. I just hope there will be less of them.

# IV-3 VFD Status Monitor

A computer status monitor using vacuum tube displays from the Soviet Union. Small IV-3 tubes.

<img width="100" height="161" alt="IV-3" src="https://github.com/user-attachments/assets/f9184b12-17df-46d5-9dc5-7c579cb3c8fe" />

This was originally designed as a CPU usage monitor, it has been used by me for 6 years as such. It relied on someone else's Windows based software to provide a data stream to the Arduino. Since then, with the development of AI, I've been able to get GPU usage to be transferred over serial also. I've picked up AVR programming again determined to get a handle on C/C++. I'll get to making my own computer side software in time.

This works by taking data over serial from a PC and bit banging it out into two shift registers. These registers then control a high side switching driver IC, to control the 28v required by the VFD segments.

The VFD displays require two voltages to operate, while the logic requires just 5v. I wanted only one supply that could power everything, so a boost circuit was used. The chip at the time I chose was a MC34063 due to its availability and helpful information online.

The 5v logic supply would come directly from the USB port supply. The 28v for the VFD anode voltage would come from the boost converter. The remaining 1v come from a simple resistor dropper. This is one aspect I'm unhappy with. A dedicated buck supply would be much better for display stability. This is one of the issues I'm unhappy with that is compounded by other things. I'll get to that later on.

The driver IC was the trickiest part to find. Any such devices now are surface mounted and at the time I was trying to stick with THT parts. The UDN2981A is still available used/NOS as of this update. If parts dry up, I might update the project with a ULN2803 and the extra transistor needed as these are available new.

The use of two shift registers was me thinking it would be better than using 14 outputs to drive the displays. In hind sight, that would have been easier for me then. I learned about shift registers though, so maybe it was worth it.

## Computer Software

At the time of doing this project, I relied on having someone else to do the computer side of things. I didn't get someone to do it, just had to make do with what could be found online.

Since the time of this project, I've moved to Linux from Windows. I don't want to use the AI privacy mess of Windows 11. I can't complain about AI too much as that was the solution to coming up with different PC side software. After moving to Linux, the software I was using, wouldn't work.

There is now a shell and Python script. The idea being that the Python script could be used in Windows, or tweaked to be. Windows uses a different way to get status data than Linux. I'll see if I can modify it myself to work. I'd like to be able to code these things myself, so I got to learn.

There is no limit to what you can display on it, if it can be viewed on a two digit display. I'd like to see about having it cycle through different data with some sort of indicator in between. CU = CPU%, GU = GPU%, Cc = CPU Celsius, Gc = GPU Celsius, etc.

For now the scripts provided here work only on Linux, they are for CPU and GPU usage %. They are the two I find most useful.

The original software for Windows can be found here: https://github.com/Maciekbac/Arduino-LED-CPU-Monitor

## Issues

* There is a diode on the Arduino Nano that is to stop external voltages being fed back through the USB connector. I didn't even realise until recently. That poor thing has to deal with large current spikes. It's been years of use and it hasn't failed, so it must be fine. The issue is the voltage drop across it. The boost supply was designed for 5v input, not 4.5v. As a result the output voltage of the boost supply isn't stable (one of the reasons for this anyway). 

* The Arduino used has a USB micro connector. Touching it changes the display brightness. A more modern Arduino with a USB C connector would provide a better connection.

* The major reason for the supply output wondering up and down with load, is due to the original design not having any supply filtering. Using my small scope, you can see the voltage at the USB port dropping to 3v each time the boost converter switches. I forget the switching frequency now, I think it was 80KHz. After some testing, a 470uF capacitor on the Arduino supply pins ironed out those 3v dips, keeping the voltage close to 4.5v. This needs adding to the design.

* Major reason number two. The inductor for the boost supply was tiny. I'd noticed this right away and botched on a larger inductor. This helped a lot. It was still undersized. More recently I swapped for a much larger inductor that nearly fits perfectly. Originally I'd not taken into account the saturation current of the inductor.

* The boost supply didn't have enough output filtering. Unsure as to why I got it wrong. 100uF works well.

* Yet another reason for the display brightness issues, the basic resistor dropper used for the cathodes. Any variation in the supply voltage would vary the cathode voltage, not even counting for the fact it was designed for 5v not 4.5v. As mentioned, there are many issues with supply voltage. Both anode and cathode voltages changing causes larger brightness changes than only one changing. A proper onboard buck supply would solve this.

* On the software side of things. The Windows program I used sent data so fast you could bearly read the display. That was solved by using 5 data points and averaging them in the Arduino. The data stream needs to be fast else the Arduino will sample a zero and the display hops between 0, x value, 0, y value. Need to add code to tell the Arduino to not sample no data from the serial connection.

## Future Ideas

* Having made this using only 3 IO pins plus 2 for the serial connection. Can a version of the ATtiny be used? ATtiny85, ATtiny44, ATtiny45, Attiny2313 with FTDI chip?

* At the time I made a choice to drive both displays all of the time, rather than a multiplexed display. This was due to me never programming anything before in my life, except for ladder logic in college. I was able to get a multiplex function working but it would freeze every update. Future me knows now this was due to the delay() used, blocking anything else running. It is not in fact that the Arduino isn't powerful enough. Sounds dumb looking back.

* Multiplexing would be nice as is would reduce the current on the USB port.
