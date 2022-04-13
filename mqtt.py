import sys
import paho.mqtt.client as paho
import json


def change_lights(aan, roomID):
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
    temp = '0'
    print(aan)
    if aan == 'True':
        temp = '100'
    else:
        temp = '1'
        
    client.publish("encyclopedia/temperature", payload="cold", qos=1)
    client.publish("domoticz/in", json.dumps({'idx' : 1, 'nvalue' : 0, 'svalue' : temp}), qos=1)
    sys.exit('sent')

if __name__ == '__main__':
    change_lights(sys.argv[1], sys.argv[2])