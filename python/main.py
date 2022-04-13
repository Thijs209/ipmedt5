from cProfile import run
from multiprocessing.connection import wait
from nis import cat
import serial
import os

import time
import mysql.connector
import paho.mqtt.client as paho
from paho import mqtt
import json

mydb = mysql.connector.connect(
    host = "localhost",
    user="thijs",
    passwd="123",
    database="light_control"
)

def change_lights():
    if(mycursor.execute("SELECT people FROM rooms") <= 0):
        print("lights out")
    else:
        print("lights on")

def check_people(roomID):
    mycursor.execute("SELECT people FROM rooms WHERE id = '" + roomID + "'")
    people = mycursor.fetchone()
    print(people)
    if people == 0:
        return False
    else:
        return True

if __name__ == '__main__':
    mycursor = mydb.cursor()
    peoples = mycursor.fetchall()

    port = serial.Serial("/dev/ttyUSB0", baudrate="115200", timeout=3.0)


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
                mycursor.execute("UPDATE rooms SET people = people +1 WHERE id =" + roomID + ";")
                mydb.commit()

                if check_people(roomID):
                    change_lights(True, roomID)
                else:
                    change_lights(False, roomID)

                # os.system("python mqtt+1.py")

            except:
                print(roomID + "bestaat niet")
            rcv = 0
                
        if '-1' in rcv:
            print("detected1")
            roomID = rcv.split()[0]
            try:
                mycursor.execute("UPDATE rooms SET people = people -1 WHERE id =" + roomID + ";")
                mydb.commit()

                if check_people(roomID):
                    change_lights(True, roomID)
                else:
                    change_lights(False, roomID)


                # os.system("/python/python mqtt.py")
            except:
                print(roomID + "bestaat niet")
            rcv = 0



    mydb.close()


def light_change(aan, roomID):
    # setting callbacks for different events to see if it works, print the message etc.
    def on_connect(client, userdata, flags, rc, properties=None):
        print("CONNACK received with code %s." % rc)

    # with this callback you can see if your publish was successful
    def on_publish(client, userdata, mid, properties=None):
        print("mid: " + str(mid))

    # print which topic was subscribed to
    def on_subscribe(client, userdata, mid, granted_qos, properties=None):
        print("Subscribed: " + str(mid) + " " + str(granted_qos))

    # print message, useful for checking if it was successful
    def on_message(client, userdata, msg):
        print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    
    client = paho.Client(client_id="", userdata=None, protocol=paho.MQTTv5)
    # client = mqtt.Client(transport="websockets")
    client.on_connect = on_connect

    # enable TLS for secure connection
    #client.tls_set(tls_version=mqtt.client.ssl.PROTOCOL_TLS)
    #client.tls_insecure_set(True)
    # set username and password
    # client.username_pw_set("", "")
    # connect to HiveMQ Cloud on port 8883 (default for MQTT)
    client.connect("localhost", 1883)

    # setting callbacks, use separate functions like above for better visibility
    client.on_subscribe = on_subscribe
    client.on_message = on_message
    client.on_publish = on_publish

    # subscribe to all topics of encyclopedia by using the wildcard "#"
    client.subscribe("encyclopedia/#", qos=1)
    client.subscribe("domoticz/in", qos=1)

    # a single publish, this can also be done in loops, etc.
    client.publish("encyclopedia/temperature", payload="cold", qos=1)
    temp = 0
    if aan:
        temp = 100
    else:
        temp = 1
        
    client.publish("domoticz/in", json.dumps({'idx' : 1, 'nvalue' : 0, 'svalue' : temp }), qos=1)

    client.publish("{ 'idx' : 1, 'nvalue' : 0, 'svalue' : " + temp + "}", "domoticz/in")

    # loop_forever for simplicity, here you need to stop the loop manually
    # you can also use loop_start and loop_stop
    client.loop_forever()