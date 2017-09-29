#!/bin/bash

# this script starts the prometheus server at port 9090
# the configure is specified in sensor-server.yml file
# the high number of storage.local.num-fingerprint-mutexes is to avoid fingerprint collison
# in case of crash, add --storage.local.dirty to restart

<path_to_prometheus>/prometheus --config.file=sensor-server.yml --web.listen-address ":9090" --storage.local.num-fingerprint-mutexes=81920

