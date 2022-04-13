from cProfile import run
from multiprocessing.connection import wait
from nis import cat
import serial
import os

import time
import mysql.connector

mydb = mysql.connector.connect(
    host = "localhost",
    user="thijs",
    passwd="",
    database="light_control"
)

def wait_until(rcv, timeout, condition, period=0.25):
  mustend = time.time() + timeout
  while time.time() < mustend:
    if (rcv == condition): 
        return True
    time.sleep(period)
  return False

def change_lights():
    if(mycursor.execute("SELECT people FROM rooms") <= 0):
        print("lights out")
    else:
        print("lights on")

if __name__ == '__main__':
    port = serial.Serial("/dev/ttyUSB0", baudrate="115200", timeout=3.0)

    mycursor = mydb.cursor()

    while True:
        rcv = port.readline().decode('utf-8').rstrip()
        print(rcv)
        if "add" in rcv:
            roomID = rcv.split()[1]
            try:
                mycursor.execute("INSERT INTO rooms (roomID) VALUES ('" + roomID + "')")
                mydb.commit()
            except:
                print(roomID + 'bestaat al')

        if "+1" in rcv:
            print("detected2")
            roomID = rcv.split()[0]
            try:
                mycursor.execute("UPDATE rooms SET people = people +1 WHERE roomID =" + roomID + ";")
                mydb.commit()
                os.system("python mqtt+1.py")
            except:
                print(roomID + "bestaat niet")
            rcv = 0
                
        if '-1' in rcv:
            print("detected1")
            roomID = rcv.split()[0]
            try:
                mycursor.execute("UPDATE rooms SET people = people -1 WHERE roomID =" + roomID + ";")
                mydb.commit()
                os.system("/python/python mqtt.py")
            except:
                print(roomID + "bestaat niet")
            rcv = 0

    mydb.close()
