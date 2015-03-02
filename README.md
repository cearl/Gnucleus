# Gnucleus
backend for Gnuclear a Free and Open Source GSM Telephony stack

Project:
=======
I wanted a phone with 100% open source code. After many months of searching, there is NO SUCH THING. Other than maybe 
the Motorola C118,C125 etc (anything supported by Osmocom-bb) which is apparently impossible to buy from a seller in the
US that also looks reputible. With that in mind I can at least know exactly what my phone is doing and control it with any
Linux based computer. So I built a phone around the SIM900 using an Arduino and this code is the result...

=-Long live the dumb-phone=- 


Gnucleus:
=========
This is the daemon which controlls whatever serial GSM modem you may have. It handles initialization of the modem and 
in the future will handle passing messages over a bus to other applications for event handling

GnuclearDialer:
==============
This is a CLI voice dialer. The daemon will eventually handle recieving calls.

GnuclearSMS:
============
This sends SMS messages. The daemon will eventually handle recieving SMS.
