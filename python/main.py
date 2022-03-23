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
    port = serial.Serial("/dev/ttyUSB1", baudrate="115200", timeout=3.0)

    mycursor = mydb.cursor()

    # rcv = port.readline().decode('utf-8').rstrip()
    # print(rcv)

    while True:
        rcv = port.readline().decode('utf-8').rstrip()
        if(rcv == "gate1"):
            print("detected")
            mycursor.execute("UPDATE rooms SET people = people +1;")
            mydb.commit()
            rcv = 0
            
    
        if(rcv == "gate2"):
            print("detected")
            mycursor.execute("UPDATE detect SET gate_2 = true;")
            rcv = 0

            # if(wait_until(rcv, 5000, "gate1")):
            #     mycursor.execute("UPDATE rooms SET people = amount -1;")
            #     mydb.commit()
            #     change_lights()   

    mydb.close()
