#!/usr/bin/python

import re
import json
import os

"""
Very simple HTTP server in python.
Usage::
    specify prom_public_dns and prom_port_num
    ./prometheus_targets.py [target_json.json] [port number for this server]
"""
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer

# append data to a json file
# inputs: file_name - name of json file
#         producer_address - URL (not including port number) of sensor http server
#         port - port number of sensor http server
#         sensor_id - ID of sensor
# outputs: target sensor information appended to the json file
def append_data_json(file_name, producer_address, port, sensor_id):
    # open file
    with open(file_name) as json_data:
        data = json.load(json_data)

    # append data to file
    target_name = producer_address + ":" + str(port)
    data.append({"targets": [target_name], "labels": {"job": sensor_id}})

    with open(file_name, 'w') as json_data:
        json_data.write(json.dumps(data))

    json_data.close()

# create a json file and add data to it
# inputs: file_name - name of json file
#         producer_address - URL (not including port number) of sensor http server
#         port - port number of sensor http server
#         sensor_id - ID of sensor
# outputs: a json file containing target sensor information
def add_data_json(file_name, producer_address, port, sensor_id):
  # make a new file if not
  open(file_name, 'w')
    target_name = producer_address + ":" + str(port)
    data = [{"targets": [target_name], "labels": {"job": sensor_id}}]
    
    with open(file_name, 'w') as json_data:
      json_data.write(json.dumps(data))
    
    json_data.close()

# a class that handles http post
class S(BaseHTTPRequestHandler):
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        self._set_headers()
        self.wfile.write("<html><body><h1>Ready to receive data ... </h1></body></html>")

    def do_HEAD(self):
        self._set_headers()
    
    # get a POST, parse it, and write informatin to the json file
    def do_POST(self):
        self._set_headers()
        # get the post data
        conten_len = int(self.headers.getheader('content-length',0))
        post_body = self.rfile.read(conten_len)
        
        # parse the post data, obtain producer_address, port number, sensor id
        post_body_info = re.split(r'&+|=', post_body)
        producer_address = post_body_info[1]
        port_number = post_body_info[3]
        sensor_id = post_body_info[5]
        #print("producer_address", producer_address)
        #print("sensor_id", sensor_id)
        print("port_number", port_number)
        
       # write targets into json file
       input_file = argv[1]
       if not os.path.exists(input_file):
           # create an input file and write data to it
           add_data_json(input_file, producer_address, port_number, sensor_id)
      else:
           # append data to the json file
           append_data_json(input_file, producer_address, port_number, sensor_id)


def run(server_class=HTTPServer, handler_class=S, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print 'Starting httpd...'
    httpd.serve_forever()

if __name__ == "__main__":
    from sys import argv

    if len(argv) == 3:
        run(port=int(argv[2]))
    else:
        run()
