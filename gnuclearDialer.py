#!/usr/bin/python
import serial, time, sys

ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=19200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)
GsmAT = "AT"
GsmSetFunc = "AT+CFUN=1"
GsmVoiceDialCommand = "ATDT+"
GsmHangUp = "ATH"

number = sys.argv[1]
ser.isOpen()

def GsmModemSendCommand(GsmCommand):
    ser.write(GsmCommand + "\r")
    time.sleep(0.25) 
 
def GsmModem_init ():
     GsmModemSendCommand(GsmAT)
     GsmModemSendCommand(GsmSetFunc)
   
def GsmVoiceDial(number):
    GsmModemSendCommand(GsmVoiceDialCommand + number + ";")


if sys.argv[1] == "--hangup" or sys.argv[1] == "-h":
    GsmModemSendCommand(GsmHangUp)
    exit(0)

GsmModem_init()
GsmVoiceDial(sys.argv[1])
