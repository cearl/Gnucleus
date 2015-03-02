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
GsmSetSMSMode = "AT+CMGF=1"
GsmSMSCommand = "AT+CMGS="

number = sys.argv[1]
message = sys.argv[2]
ser.isOpen()

def GsmModemSendCommand(GsmCommand):
    ser.write(GsmCommand + "\r")
    time.sleep(0.25) 
 
def GsmModem_init ():
     GsmModemSendCommand(GsmAT)
     GsmModemSendCommand(GsmSetFunc)
     GsmModemSendCommand(GsmSetSMSMode)
   
def GsmSendSMS(number, message):
    GsmModemSendCommand(GsmSMSCommand + "\"" + number + "\"")
    GsmModemSendCommand(message)
    GsmModemSendCommand(chr(26)) 

GsmModem_init()
GsmSendSMS(sys.argv[1],sys.argv[2])
