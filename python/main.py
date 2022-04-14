from cProfile import run
from multiprocessing.connection import wait
from nis import cat
import serial
import os

import mysql.connector
import paho.mqtt.client as paho

# Moet nog geïnstalleerd worden -> pip3 install pusher
import pusher

# Pusher api keys
pusher_client = pusher.Pusher(
  app_id=u'1384821',
  key=u'45da88aa7f5d38d338c4',
  secret=u'aedd886b667484cba54f',
  cluster=u'eu'
)

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
                
                # Refreshed het dashboard bij alle clients
                # pusher_client.trigger(u'my-channel', u'dashboard-update', [])
                
            except:
                print(roomID + 'bestaat al')
            rcv = ""

        if "+1" in rcv:
            roomID = rcv.split()[0]
            try:
                mycursor.execute("UPDATE rooms SET people = people +1 WHERE id = '" + roomID + "';")
                mydb.commit()
                # Refreshed het dashboard bij alle clients
                # pusher_client.trigger(u'my-channel', u'dashboard-update', [])

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
                # Refreshed het dashboard bij alle clients
                # pusher_client.trigger(u'my-channel', u'dashboard-update', [])

                if check_people(roomID):
                    os.system("python mqtt.py True " + roomID)
                else:
                    os.system("python mqtt.py False " + roomID)
            except:
                print(roomID + "bestaat niet")
            rcv = ""

    mydb.close()


