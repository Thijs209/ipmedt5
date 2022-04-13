from cProfile import run
from multiprocessing.connection import wait
from nis import cat
import serial
import os

import mysql.connector
import paho.mqtt.client as paho

mydb = mysql.connector.connect(
    host = "localhost",
    user="thijs",
    passwd="",
    database="light_control"
)

def check_people(roomID):
    mycursor.execute("SELECT people FROM rooms WHERE id = '" + roomID + "'")
    people = mycursor.fetchone()
    print(people[0])
    if people[0] < 0:
        mycursor.execute("UPDATE rooms SET people = 0 WHERE id = '" + roomID + "';")
        mydb.commit()

    if people[0] == 0:
        return False
    else:
        return True

if __name__ == '__main__':
    mycursor = mydb.cursor(buffered = True)

    port = serial.Serial("/dev/ttyUSB1", baudrate="115200", timeout=3.0)

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
            rcv = ""

        if "+1" in rcv:
            roomID = rcv.split()[0]
            try:
                mycursor.execute("UPDATE rooms SET people = people +1 WHERE id = '" + roomID + "';")
                mydb.commit()

                if check_people(roomID):
                    os.system("python mqtt.py True " + roomID)
                else:
                    os.system("python mqtt.py False " + roomID)
            except:
                print(roomID + " bestaat niet")

            rcv = ""
                
        if '-1' in rcv:
            roomID = rcv.split()[0]
            try:
                mycursor.execute("UPDATE rooms SET people = people -1 WHERE id = '" + roomID + "';")
                mydb.commit()

                if check_people(roomID):
                    os.system("python mqtt.py True " + roomID)
                else:
                    os.system("python mqtt.py False " + roomID)
            except:
                print(roomID + "bestaat niet")
            rcv = ""

    mydb.close()


