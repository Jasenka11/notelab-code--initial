import requests
import json


#def send_message_to_rabbitm(channel, exchange, routing_key, msg):
 #   channel.basic_publish(exchange=exchange, routing_key=routing_key, body=msg)


def send_message_to_elasticsearch(url, msg):
    headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}
    r = requests.post(url, data=json.dumps(msg), headers=headers)
    print("Status code: ", r.status_code)
    print("Printing Entire Post Request")
    print(r.json())

if __name__ == "__main__":
    # parameters
   url = 'http://192.168.1.7:9200/index/'
   message = {'id': 'microcontrollerX', 'temperature': 22.8, 'humidity': 23}

   
   
   #headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}
   send_message_to_elasticsearch(url, message)
   print("Message sent to ElasticSearch: " + json.dumps(message))
   # user = "user"
   # passw = "password"
   # queue = "notelab"

   # exchange = "amq.topic"
   # routing_key = "logstash"

 #   message = "test_messasge"
#
  #  channel = connect_to_rabbitmq(ip, port, user, passw, queue)
   # send_message_to_rabbitmq(channel, exchange, routing_key, message)
   # print("Message sent to RabbitMQ server: " + message)
