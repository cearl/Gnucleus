#!/usr/bin/python
import serial, time, sys

line = []
ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=19200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

GsmAT = "AT"
GsmSetFunc = "AT+CFUN=1"

def GsmModemSendCommand(GsmCommand):
    ser.write(GsmCommand + "\r")
    time.sleep(0.25) 

def GsmModem_init ():
     GsmModemSendCommand(GsmAT)
     GsmModemSendCommand(GsmSetFunc)

GsmModem_init()

while True:
    data = ser.readline()
    if len(data) > 0:
        if "+CMTI: \"SM\"" in data:
            print("Incoming SMS")    
        if "RING" in data:
            print("Incoming Call")
            
    time.sleep(0.5)
    
