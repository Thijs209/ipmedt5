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
    port = serial.Serial("/dev/ttyUSB0", baudrate="115200", timeout=3.0)
    on = False

    while True:
        mydb = mysql.connector.connect(
            host = "localhost",
            user="thijs",
            passwd="",
            database="light_control"
        )

        mycursor = mydb.cursor(buffered = True)

        mycursor.execute("SELECT id FROM rooms")
        roomIDs = mycursor.fetchall()

        rcv = port.readline().decode('utf-8').rstrip()
        print(rcv)
        if "add" in rcv:
            roomID = rcv.split()[1]
            try:
                mycursor.execute("INSERT INTO rooms (id) VALUES ('" + roomID + "')")
                mydb.commit()
                
                # Refreshed het dashboard bij alle clients
                pusher_client.trigger(u'my-channel', u'dashboard-update', [])
                
            except:
                print(roomID + 'bestaat al')
            rcv = ""

        if "+1" in rcv:
            roomID = rcv.split()[0]
            try:
                mycursor.execute("UPDATE rooms SET people = people +1 WHERE id = '" + roomID + "';")
                mydb.commit()
                # Refreshed het dashboard bij alle clients
                pusher_client.trigger(u'my-channel', u'dashboard-update', [])
            except:
                print(roomID + " bestaat niet")

            rcv = ""
                
        if '-1' in rcv:
            roomID = rcv.split()[0]
            try:
                mycursor.execute("UPDATE rooms SET people = people -1 WHERE id = '" + roomID + "';")
                mydb.commit()
                # Refreshed het dashboard bij alle clients
                pusher_client.trigger(u'my-channel', u'dashboard-update', [])
            except:
                print(roomID + "bestaat niet")
            rcv = ""

        for roomID in roomIDs:
            mycursor.execute("SELECT people FROM rooms WHERE id = '" + roomID[0] + "'")
            people = mycursor.fetchone()

            mycursor.execute("SELECT domoticz_idx FROM rooms WHERE id = '" + roomID[0] + "'")
            index = mycursor.fetchone()

            mycursor.execute("SELECT light_status FROM rooms WHERE id = '" + roomID[0] + "'")
            light_status = mycursor.fetchone()
            
            if light_status[0] == 0:
                if check_people(roomID[0]):
                    os.system("python mqtt.py True " + str(index[0]))
                    on = True
                else:
                    os.system("python mqtt.py False " + str(index[0]))
                    on = False

    mydb.close()


