#!/usr/bin/python
# This was developed with the SIM900 chip
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
GsmSetCRC = "AT+CRC=1" 
GsmIncomingCall = "+CRING" 
GsmSetCallerID = "AT+CLIP=1"
GsmSetAlert = "AT+CALS=1"
smsDeleteMemoryBlock="AT+CMGD="
smsReceived = "+CMTI: \"SM\"" 
smsRead = "AT+CMGR="
smsUnreadMessage = "+CMGR: \"REC UNREAD\""

def GsmModemSendCommand(GsmCommand):
    ser.write(GsmCommand + "\r")
    time.sleep(0.25) 

def GsmModem_init ():
     print("Sending modem init sequence")
     GsmModemSendCommand(GsmAT)
     GsmModemSendCommand(GsmSetFunc)
     GsmModemSendCommand(GsmSetCRC)
     GsmModemSendCommand(GsmSetCallerID)
     GsmModemSendCommand(GsmSetAlert)

def GsmDeleteSMS(blockID):
    # dont fill up SMS blocks
    GsmModemSendCommand(blockID)
    

def SmsGetFromMemory(blockID):
    smsDict = {}
    GsmModemSendCommand(smsRead + blockID)   
    smsModemCommand = ser.readline()
    smsHeader = ser.readline()
    smsMessage = ser.readline()
    smsMessage = smsMessage.strip("\r\n")
    smsHeaderParse = smsHeader.split(',')
    smsSender = smsHeaderParse[1]
    smsSender = smsSender.strip('"')
    smsDict = {smsSender:smsMessage}
    print smsDict

GsmModem_init()

while True:
    data = ser.readline()
    if len(data) > 0:
        if smsReceived in data:
            data = data.strip('\r\n')
            data = data.strip('\r')
            data = data.strip('\n')
            data = data.split(',',1)
            blockID = data[1]
            SmsGetFromMemory(blockID)
            GsmDeleteSMS(blockID)
     
        if GsmIncomingCall in data:
            GsmCaller = ser.readline()     
            print GsmCaller 
   
    
