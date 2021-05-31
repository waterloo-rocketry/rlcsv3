# RLCS

RLCS is our Remote Launch Control System. It's purpose is to fill our rocket 
with nitrous oxide and then ignite the ignition spacer inside the rocket, all 
from a distance of 3000' away at launch control. To do so, it has control over 
2 valves at the rocket (a valve for filling, and another valve for venting the 
fill lines), a linear actuator to disconnect the fill arm from the rocket, and 
2 ignition coils inside the ignition spacer (all of these details are subject 
to change in future revisions of the rocket e.g. adding nitrogen super-
pressurization would require more valves to load the nitrogen).
It also features some basic data acquisition so we know how the fill is going 
(mass sensor underneath the rocket and a pressure transducer on the fill line)

This repository is the main working site for the second version of RLCS, which 
should feature the following improvements over version 1:

* Actuator feedback through limit switches and more sensors at the tower

* All components integrated into 2 central boxes (one at tower and one at 
launch control), to avoid the issues with cables.
* Improved extensibility and ease of adding upgrades

* Data logging of all daq sensors and actuator times. This information will
be invaluable for post launch analysis.

* PCBs for all circuits instead of vero board contraptions, for more
reliability

* More unit and integration testing on all arduino code (v1 arduino code
worked fine, but it can't hurt)

With all these changes in place, we should have a much more safe and reliable
launch control system, that should serve our team well for (hopefully) the next
5-10 years.


# Repository Layout

All code is in `/arduino_programs`

All PCB layouts and electrical schematics are in `/schematics`

All gerber files (sent to fabs) are in `/gerbers` (these are the files PCB
makers need to make PCBs).

