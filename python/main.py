from cProfile import run
from multiprocessing.connection import wait
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
    print('1')
    port = serial.Serial("/dev/ttyUSB0", baudrate="115200", timeout=3.0)

    mycursor = mydb.cursor()

    # rcv = port.readline().decode('utf-8').rstrip()
    # print(rcv)

    while True:
        rcv = port.readline().decode('utf-8').rstrip()
        print(rcv)
        if(rcv == "hoi2"):
            print("detected2")
            mycursor.execute("UPDATE rooms SET people = people +1;")
            mydb.commit()
            os.system("python mqtt+1.py")
            rcv = 0
            
    
        if(rcv == "hoi1"):
            print("detected1")
            mycursor.execute("UPDATE detect SET people = people -1;")
            os.system("/python/python mqtt.py")
            mydb.commit()
            rcv = 0

            # if(wait_until(rcv, 5000, "gate1")):
            #     mycursor.execute("UPDATE rooms SET people = amount -1;")
            #     mydb.commit()
            #     change_lights()   

    mydb.close()
