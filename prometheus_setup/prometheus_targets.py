#!/usr/bin/python

import re
import json
import os

"""
Very simple HTTP server in python.
Usage::
    specify prom_public_dns and prom_port_num
    ./prometheus_targets.py [<port>]
"""
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer

# specify prometheus server public dns
prom_public_dns = "<prometheus server public dns>"
# specify prometheus server port number
prom_port_num = 9090
# specify file name for storing targets
input_file = "targets.json"

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

def add_prometheus_json(file_name, prometheus_url, port):
    # make a new file if not
    open(file_name, 'w')
    target_name_prometheus = prometheus_url + ":" + str(port)
    job_name_prometheus = "prometheus"
    data = [{"targets": [target_name_prometheus], "labels": {"job": job_name_prometheus}}]

    with open(file_name, 'w') as json_data:
        json_data.write(json.dumps(data))

    json_data.close()

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
        
    def do_POST(self):
        self._set_headers()
        # get the post data
        conten_len = int(self.headers.getheader('content-length',0))
        post_body = self.rfile.read(conten_len)
        
        # parse the post data, obtain producer_address and port number
        post_body_info = re.split(r'&+|=', post_body)
        producer_address = post_body_info[1]
        port_number = post_body_info[3]
        sensor_id = post_body_info[5]
        #print("producer_address", producer_address)
        print("port_number", port_number)
        #print("sensor_id", sensor_id)

        # write targets into json file
        if not os.path.exists(input_file):
            add_prometheus_json(input_file, prom_public_dns, prom_port_num)

        append_data_json(input_file, producer_address, port_number, sensor_id)



def run(server_class=HTTPServer, handler_class=S, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print 'Starting httpd...'
    httpd.serve_forever()

if __name__ == "__main__":
    from sys import argv

    if len(argv) == 2:
        run(port=int(argv[1]))
    else:
        run()
